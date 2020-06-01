#include <stdio.h>

inline int max(int a, int b) {
    if(a >= b){
        return a;
    }else{
        return b;
    }
}

int dp[31][301];
int c, tmp;
int cards[91][2];

int main(void) {
    scanf("%d", &c);

    for(int i = 1; i <= 90; i++) {
        scanf("%d%d%d", &cards[i][0], &cards[i][1], &tmp);
        cards[i][1] += tmp;
    }
    // dp[0][0][c] = 0;
    for(int i = 1; i <= 30; i++) {
        for(int j = 0; j <= c; j++)
            dp[i][j] = -__INT32_MAX__/2;
    }
    for(int j = 0; j <= c; j++) {
        dp[0][j] = 0;
    }


    for(int i = 1; i <= 90; i++) {
        for(int j = 30; j >= 0; j--) {
            for(int w = c; w >= 0; w--) {
                if(cards[i][0] > w || 1 > j) {
                    dp[j][w] = dp[j][w];
                }else{
                    dp[j][w] = max(dp[j][w],
                                      dp[j-1][w-cards[i][0]]+cards[i][1]);
                }
            }
        }
    }
    int max_val = -1;
    for(int j = 0; j <= c; j++) {
        if(max_val < dp[30][j]) {
            max_val = dp[30][j];
        }
    }
    printf("%d", max_val);
    
}