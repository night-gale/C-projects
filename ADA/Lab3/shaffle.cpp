#include <stdio.h>
#include <chrono>

const int MAX_CASES = 400001;
int n;
long long list[MAX_CASES];
int computed[MAX_CASES];
long long modulo = 998244353;
long long result, toMod, toMult, toDiv;

int main(void) {
    // auto begin = std::chrono::high_resolution_clock::now();
    toMod = 1;
    toDiv = 1;
    toMult = 1;
    result = 0;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%lld", &list[i]);
        computed[i] = 0;
    }
    int last_cnt = 0;
    for(int i = 0; i < 10; i++) {
        int non_zero_cnt = 0;
        for(int j = 0; j < n; j++) {
            if(list[j] / toMod) non_zero_cnt++;
        }
        toMod *= 10;
        for(int j = 0; j < n; j++) {
            long long upper = list[j] / toDiv;
            long long digit = upper % 10;
            result += (((((non_zero_cnt * 11) % modulo) * (toMult % modulo)) % modulo) * digit) % modulo;
            result = result % modulo;
            result += ((((((n - non_zero_cnt - last_cnt) * 2) % modulo) * upper) % modulo) * (toMult % modulo)) % modulo;
            result = result % modulo;
        }
        toDiv *= 10;
        toMult *= 100;
        last_cnt = n - non_zero_cnt;
    }
    printf("%lld\n", result);
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed_time = end - begin;
    // printf("%f", elapsed_time.count());
}