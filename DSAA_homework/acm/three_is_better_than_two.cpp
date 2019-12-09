#include <stdio.h>
#include <iostream>

int T;
long long s[4], send, c[4];
long long modulo = 2147483231;

int main(void) {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        scanf("%lld %lld %lld %lld", &s[1], &s[2], &s[3], &send);
        for(int j = 1; j <= 3; j++) {
            c[j] = 0;
        }
        long long t[4];
        t[1] = s[1];
        t[2] = s[2];
        t[3] = s[3];
        for(int j = 1; j <= 3; j++) {
            while(t[j] != send) {
                c[j]++;
                t[j] = (t[j] * t[j]) % modulo;
            }
        }

        long long mcnt = std::min(c[1], std::min(c[2], c[3]));
        for(int j = 1; j <= 3; j++) {
            for(long long k = 0; k < c[j] - mcnt; k++) {
                s[j] = (s[j] * s[j]) % modulo;
            }
        }
        for(long long j = 0; j < mcnt; j++) {
            if(s[1] == s[2] && s[2] == s[3]) {
                break;
            }
            for(int j = 1; j <= 3; j++) {
                s[j] = (s[j] * s[j]) % modulo;
            }
        }
        printf("%lld\n", s[1]);
    }
}