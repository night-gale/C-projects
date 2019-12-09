#include <stdio.h>

char input[2000 - 5 + 2][2001];
int N, M;
char ans[2001];

int main(void) {
    scanf("%d %d", &N, &M);

    for(int i = 0; i < N - M + 1; i++) {
        scanf("%s", &input[i]);
    }

    for(int i = 0; i < N; i++) {
        char likely = 0;
        int maxCnt = 0;
        int asc[256] = {0};
        for(int j = 0; j < N - M + 1; j++) {
            asc[input[j][i]]++;
            if(asc[input[j][i]] > maxCnt) {
                likely = input[j][i];
                maxCnt = asc[input[j][i]];
            }
        }
        ans[i] = likely;
    }
    printf("%s", ans);
}