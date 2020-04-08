#include <stdio.h>
#include <unordered_map>
#include <chrono>
#include <algorithm>

const int SIZE = 11;
const int A_MAX = 100;
int results[5][2] = {{3,0},{2,1},{1,2},{0,3},{1,1}};
int N;
int scores[SIZE];
long long DFS(int x, int y, int th, int tw);
const long long modulo = 998244353;
std::unordered_map<long long, long long> map;
long long hash(int x);
int th,tw;
int tscores[11];



int main(void) {
    long long tsum = 0;
    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
        tsum += scores[i];
    }
    // auto begin = std::chrono::high_resolution_clock::now();
    th = tsum - N*(N-1);
    tw = N*(N-1)/2*3-tsum;
    std::sort(scores, scores+N);

    long long result = DFS(0, 0, 0, 0);

    printf("%lld\n", result);
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed_time = end - begin;
    // printf("%f", elapsed_time.count());
}

long long DFS(int x, int y, int tht, int twt) {
    long long cnt = 0;
    long long sum = 0;
    long long h1;


    // for(int i = x; i < N; i++) {
    //     sum += scores[i];
    // }

    // if(sum > ((N-x)*(N-x-1)/2 - (y-x)) * 3 || sum < ((N-x)*(N-x-1)/2 - (y-x))*2) {
    //     return 0;
    // }

    // if(tht == th) {
    //     if(scores[x] != (N-y-1)) return 0;
    //     for(int i = x + 1; i < N; i++) {
    //         if(i <= y) {
    //             if(scores[i] != (N-x-2)) return 0;
    //         }else {
    //             if(scores[i] != (N-x-1)) return 0;
    //         }
    //     }
    //     return 1;
    // }
    
    if(x==y) {
        // std::sort(scores, scores + N);
        h1 = hash(x);
        if(map.find(h1) != map.end()) {
            return map[h1];
        }
    }
    // if(x == y) {
    //     for(int i = x; i < N; i++) {
    //         if(scores[i] > 3 * (N-x-1)) {
    //             map[h1] = 0;
    //             return 0;
    //         }
    //     }
    // }

    if(y >= N - 1 && x < N - 1) {
        if(scores[x] != 0) {
            return 0;
        }else {
            return DFS(x + 1, x + 1, tht, twt);
        }
    }else if(x >= N - 1) {
        if(scores[N-1] != 0) {
            return 0;
        }else {
            return 1;
        }
    }
    
    if(scores[x] > 3*(N-y-1)) {
        return 0;
    }
    for(int i = 0; i < 5; i++) {
        if(tht >= th && i < 4) continue;
        scores[x] -= results[i][0];
        scores[y + 1] -= results[i][1];
        if(scores[x] >= 0 && scores[y + 1] >= 0) {
            if(i < 4 ) {
                if(tht < th)
                cnt = (cnt + DFS(x, y + 1, tht+1, twt) % modulo) % modulo;
            }else {
                if(twt < tw)
                cnt = (cnt + DFS(x, y + 1, tht, twt+1) % modulo) % modulo;
            }
        }
        scores[x] += results[i][0];
        scores[y + 1] += results[i][1];
    }

    if(x == y) {
        map[h1] = cnt;
    }
    return cnt;
}


long long hash(int x) {
    long long sum = 0;
    // int* tscores = new int[N];
    for(int i = x; i < N; i++) {
        tscores[i-x] = scores[i];
    }

    for(int i = 0; i < N-x; i++) {
        for(int j = i + 1; j < N-x; j++) {
            if(tscores[i] < tscores[j]) {
                int temp = tscores[i];
                tscores[i] = tscores[j];
                tscores[j] = temp;
            }
        }
    }

    for(int i = 0; i < N-x; i++) {
        sum = sum * 31 + tscores[i];
    }
    // sum = sum * 10 + x;
    // sum = sum * 10 + y;
    // delete [] tscores;
    return sum;
}