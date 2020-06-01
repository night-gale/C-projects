#include <stdio.h>

inline int max(int a, int b) {
    if( a > b ) {
        return a;
    }else {
        return b;
    }
}

inline int min(int a, int b) {
    if(a > b) {
        return b;
    }
    return a;
}

const int k_size = 1e6+3;
int iwin[5][5];
int dp[5][5];
int mj[k_size];
int n, m, tmp, r1, r2, r3;
int dp1, dp2, m1, m2;
void window(int s) {
    iwin[1][1] = mj[s]/3;
    iwin[1][2] = mj[s]%3;
    iwin[2][3] = iwin[1][2];
    iwin[2][2] = mj[s+1]%3;
    iwin[2][1] = iwin[1][1]+mj[s+1]/3;
    m1 = min(iwin[1][2], min(mj[s+1], mj[s+2]));
    m2 = min(iwin[2][3], min(iwin[2][2], mj[s+2]));
    dp1 = iwin[1][1]+m1+(mj[s+1]-m1)/3 + (mj[s+2]-m1)/3;
    dp2 = iwin[2][1]+m2+(mj[s+2]-m2)/3;
    if(dp1 > dp2) {
        iwin[3][1] = dp1;
        iwin[3][2] = (mj[s+2]-m1)%3;
        iwin[3][3] = (mj[s+1]-m1)%3;
    }else {
        iwin[3][1] = dp2;
        iwin[3][2] = (mj[s+2]-m2)%3;
        iwin[3][3] = (iwin[2][2]-m2);
    }
    return;
}

int main(void) {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m + 3; i++) {
        mj[i] = 0;
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &tmp);
        mj[tmp]++;
    }
    // init
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            iwin[i][j] = 0;
            dp[i][j] = 0;
        }
    }

    dp[1][1] = mj[1] / 3;
    dp[1][2] = mj[1] % 3;
    dp[2][1] = dp[1][1]+mj[2]/3;
    dp[2][3] = dp[1][2];
    dp[2][2] = mj[2] % 3;
    for(int i = 3; i <= m; i++) {
        window(i-2);
        r3 = iwin[3][1] + dp[0][1];
        m1 = min(dp[1][2], min(mj[i-1], mj[i]));
        m2 = min(dp[2][3], min(dp[2][2], mj[i]));
        r1 = dp[1][1]+m1+(mj[i-1]-m1)/3 + (mj[i]-m1)/3;
        r2 = dp[2][1]+m2+(mj[i]-m2)/3;
        tmp = max(r1, max(r2, r3));
        if(tmp == r1) {
            dp[3][1] = r1;
            dp[3][2] = (mj[i]-m1)%3;
            dp[3][3] = (mj[i-1]-m1)%3;
        }else if(tmp == r2) {
            dp[3][1] = r2;
            dp[3][2] = (mj[i]-m2)%3;
            dp[3][3] = (dp[2][2]-m2)%3;
        }else {
            dp[3][1] = r3;
            dp[3][2] = iwin[3][2];
            dp[3][3] = iwin[3][3];
        }
        for(int i = 1; i <=3; i++) {
            for(int j = 1; j <= 3; j++) {
                dp[i-1][j] = dp[i][j];
            }
        }
    }
    printf("%d\n", dp[3][1]);
}