/*
huffman tree¿
*/
#include <stdio.h>

#define _MAX_SIZE 1001
int T, N;
bool isChecked[_MAX_SIZE * 2];
long long lengths[_MAX_SIZE * 2];

int main(void) {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        scanf("%d", &N);
        long long cost = 0;
        // int pend = N;

        for(int j = 0; j < N; j++) {
            //initializing arrays
            isChecked[j] = 0;
            lengths[j] = 0;
        }

        for(int j = 0; j < N; j++) {
            scanf("%d", &lengths[j]);
        }
        for(int k = 0; k < N - 1; k++) {
            long long sma = __INT64_MAX__;
            int sptr = -1;
            long long se_sma = __INT64_MAX__;
            int ssptr = -1;
            for(int j = 0; j < N; j++) {
                if(isChecked[j]) {
                    continue;
                }
                if(sma > lengths[j]) {
                    sma = lengths[j];
                    sptr = j;
                }
            }
            isChecked[sptr] = 1;
            for(int j = 0; j < N; j++) {
                if(isChecked[j]) {
                    continue;
                }
                if(se_sma > lengths[j]) {
                    se_sma = lengths[j];
                    ssptr = j;
                }
            }
            lengths[ssptr] = sma + se_sma;
            cost += sma + se_sma;
        }
        printf("%lld\n", cost);
    }
}