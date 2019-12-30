#include <stdio.h>

long long N, I, M, K;
long long prizes[100001];
bool isEvening;

long long getGamePrize(long long t) {
    long long sum = 0;
    long long discount = (t - 1) * K;
    for(int i = 0; i < M; i++) {
        if(prizes[i] > discount) sum += prizes[i] - discount;
        else sum += prizes[i] % K?prizes[i] % K: K;
    }
    return sum;
}

long long binarySearch(long long start, long long end) {
    long long mid;
    long long cprize;
    long long moneyM;
    long long moneyE;
    long long ans;
    while(true) {
        if(start > end) break;
        mid = (start + end) / 2;
        cprize = getGamePrize(mid);
        moneyM = N + (mid - 1) * I;
        moneyE = moneyM + I;
        if(cprize > moneyE) {
            start = mid + 1;
        }else {
            end = mid - 1;
        }
    }
    cprize = getGamePrize(start);
    moneyM = N + (start - 1) * I;
    moneyE = moneyM + I;
    if(cprize > moneyM) isEvening = 1;
    else isEvening = 0;
    return start;
}



int main(void) {
    scanf("%lld %lld %lld %lld", &N, &I, &M, &K);
    for(int i = 0; i < M; i++) {
        scanf("%lld", &prizes[i]);
    }
    long long ans = binarySearch(1, 100);
    printf("%lld ", ans);
    if(isEvening) {
        printf("evening\n");
    }else printf("morning\n");
}