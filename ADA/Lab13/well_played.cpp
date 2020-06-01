#include <stdio.h>

inline int max(int a, int b) {
    if(a > b) return a;
    return b;
}

int dp[101][1001];
int cards[2][101][101];
int n, k, C;
int u, v, w;
int result;

int main(void) {
    result = -1;
    scanf("%d%d%d", &n, &k, &C);
    for(int i = 0; i < C; i++) {
        dp[0][i] = 0;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            scanf("%d%d%d", &u, &v, &w);
            cards[0][i][j] = u;
            cards[1][i][j] = w + v;
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = C; j >= 0; j--) {
            for(int a = 1; a <= k; a++) {
                if(cards[0][i][a] + j > C) {
                    dp[i][j] = max(dp[i-1][j], dp[i][j]);
                    continue;
                }
                dp[i][j] = max(max(dp[i-1][j], dp[i][j]), dp[i-1][j+cards[0][i][a]] + cards[1][i][a]);
            }
        }
    }

    for(int i = 0; i <= C; i++) {
        if(result < dp[n][i]) result = dp[n][i];
    }
    printf("%d\n", result);
}