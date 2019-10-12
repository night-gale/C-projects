#include <stdio.h>

long prizes[1000000];
long moneyS[1000000];
long T;
long N;

long binarySearch(long money, long start, long end);

int main(void) {
    scanf("%ld", &T);
    scanf("%ld", &N);
    for(long i = 0; i < T; i++) {
        scanf("%ld", &moneyS[i]);
    }
    for(long j = 0; j < N; j++) {
        scanf("%ld", &prizes[j]);
    }
    for(long i = 0; i < T; i++) {
        long target = prizes[binarySearch(moneyS[i], 0, N - 1)];
        if(target == moneyS[i]) {
            printf("Meow\n");
        }else {
            printf("%lld\n", ((moneyS[i] > target)? (moneyS[i] - target): moneyS[i]));
        }
    }
}

long binarySearch(long money, long start, long end) {
    while(true) {
        long mid = (start + end) / 2;
        if(money < prizes[start]) {
            return start;
        }
        if(money > prizes[end]) {
            return end;
        }
        if(((start + 1) == end) || (start == end)) {
            if(prizes[start] == money) {
                return start;
            }else if(prizes[end] == money) {
                return end;
            }

            if(prizes[start] > money) {
                return start;
            }else if(prizes[end] < money) {
                return end;
            }else if(prizes[start] < money && prizes[end] > money) {
                return start;
            }
        }

        if(prizes[mid] == money) {
            return mid;
        }else if(prizes[mid] < money) {
            start = mid;
        }else if(prizes[mid] > money) {
            end = mid;
        }
    }
}