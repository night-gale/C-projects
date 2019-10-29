#include <stdio.h>

int T;
long long N, K;

int main(void) {
    scanf("%lld", &T);

    for(int i = 0; i < T; i++) {
        scanf("%d %d", &N, &K);
        long long temp = (K - 1) * N + 1;
        int h = 0;
        long long _pow = 1;
        while(temp >= K) {
            temp /= K;
            h++;
            _pow *= K;
        }
        long long sum = (_pow - 1) / (K - 1);
        long long rest;
        long long answer;
        long long leave;
        if(sum > N) {
            _pow /= K;
            sum -= _pow;
        }
        rest = N - sum;
        leave = (rest % K == 0? 0: 1) + rest / K;
        leave = _pow / K - leave;
        leave += rest;
        // printf("%d", _log);
        printf("%lld\n", leave);
    }
}