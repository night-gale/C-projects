#include <stdio.h>
inline int max(int a, int b) {
    if(a > b) return a;
    return b;
}

const int k_size = 1e6 + 10;
int n, m, dp1;
int mj[k_size], dp[k_size][3][3];

int main(void) {
    int tmp;
    scanf("%d%d", &n, &m);

    // extends two entries to prevent overflow
    for(int i = 1; i <= m+2; i++) {
        mj[i] = 0;
    }

    // store input into buckets
    for(int i = 1; i <= n; i++) {
        scanf("%d", &tmp);
        mj[tmp]++;
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            dp[0][i][j] = 0;
        }
    }
    bool c1, c2, c3;

    for(int i = 1; i <= m; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                for(int x = 0; x < 3; x++) {
                    c1 = j > mj[i+2];
                    c2 = j + k > mj[i+1];
                    c3 = j + k + x > mj[i];
                    if(c1 || c2 || c3) continue;
                    // borrow j+k from mj[i+1] and j from mj[i+2]
                    dp1 = dp[i-1][k][x] + j + (mj[i]-j-k-x)/3;
                    dp[i][j][k] = max(dp[i][j][k], dp1);
                }
            }
        }
    }

    printf("%d\n", dp[m][0][0]);
}