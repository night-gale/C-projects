#include <stdio.h>
#include <unordered_map>
#include <chrono>

const int SIZE = 11;
const int A_MAX = 100;
int results[5][2] = {{3,0},{2,1},{1,1},{1,2},{0,3}};
int N;
int scores[SIZE];
long long DFS(int x, int y, int* scores);
const long long modulo = 998244353;
std::unordered_map<long long, long long> map;
long long hash(int x, int y);
int th,tw;

int main(void) {
    long long tsum = 0;
    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
        tsum += scores[i];
    }
    auto begin = std::chrono::high_resolution_clock::now();
    th = tsum - N*(N-1);
    tw = N*(N-1)/2*3-tsum;

    long long result = DFS(0, 0, scores);

    printf("%lld\n", result);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end - begin;
    printf("%f", elapsed_time.count());
}

long long DFS(int x, int y, int* scores) {
    long long cnt = 0;
    long long sum = 0;
    long long h1;

    if(x == y) {
        for(int i = x; i < N; i++) {
            if(scores[i] > 3 * (N-x-1)) {
                return 0;
            }
        }
    }

    for(int i = x; i < N; i++) {
        sum += scores[i];
    }

    if(sum > ((N-x)*(N-x-1)/2 - (y-x)) * 3 || sum < ((N-x)*(N-x-1)/2 - (y-x))*2) {
        return 0;
    }
    
    h1 = hash(x, y);
    if(map.find(h1) != map.end()) {
        return map[h1];
    }

    if(y >= N - 1 && x < N - 1) {
        if(scores[x] != 0) {
            return 0;
        }else {
            return DFS(x + 1, x + 1, scores);
        }
    }else if(x >= N - 1) {
        if(scores[N-1] != 0) {
            return 0;
        }else {
            return 1;
        }
    }
    
    for(int i = 0; i < 5; i++) {
        scores[x] -= results[i][0];
        scores[y + 1] -= results[i][1];
        if(scores[x] >= 0 && scores[y + 1] >= 0) {
            cnt = (cnt % modulo + DFS(x, y + 1, scores) % modulo) % modulo;
        }
        scores[x] += results[i][0];
        scores[y + 1] += results[i][1];
    }

    // if(x == y) {
        map[hash(x,y)] = cnt;
    // }
    return cnt;
}

long long hash(int x, int y) {
    long long sum = 0;
    for(int i = 0; i < N; i++) {
        sum = sum * 31 + scores[i];
    }
    sum = sum * 10 + x;
    sum = sum * 10 + y;
    return sum;
}