#include <stdio.h>
#include <algorithm>

struct Trick{
    int start;
    int end;
};
int N;
const int SIZE = 5001;
Trick tricks[SIZE];
bool tryTime(int n);
bool time_axis[10001];
int binarySearch(int start, int end);

bool cmp(Trick a, Trick b) {
    return a.end < b.end;
}

int main(void) {
    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        scanf("%d%d", &tricks[i].start, &tricks[i].end);
    }

    std::sort(tricks, tricks+N, cmp);

    printf("%d\n", binarySearch(0, 10001));
}

int binarySearch(int start, int end) {
    int mid;
    while(start < end - 1) {
        mid = (start + end) / 2;

        if(tryTime(mid)) {
            start = mid;
        }else {
            end = mid;
        }
    }
    return start;
}

bool tryTime(int n) {
    int last = 0;
    for(int i = 1; i <= 10000; i++) {
        time_axis[i] = false;
    }
    for(int i = 0; i < N; i++) {
        int cnt = 0;
        for(int j = tricks[i].start; j <= tricks[i].end; j++) {
            if(!time_axis[j]) {
                time_axis[j]=true;
                cnt++;
            }
            if(cnt >= n) {
                break;
            }
        }
        if(cnt < n) {
            return false;
        }
    }
    return true;
}

