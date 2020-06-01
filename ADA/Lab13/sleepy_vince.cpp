#include <stdio.h>

inline long long max(long long a, long long b) {
    if(a > b) return a;
    return b;
}

const int k_size = 1e5+1;
long long dp[2][201][3];
long long seq[k_size];
int n, ii;
long long m, sum, sum2;
bool flag;
long long modulo = 998244353;

int main(void) {
    scanf("%d", &n);
    ii = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &seq[i]);
    }
    
    if(seq[1] != -1) {
        dp[!ii][seq[1]][0] = 1;
    }else {
        for(int i = 1; i <= 200; i++) {
            dp[!ii][i][0] = 1;
        }
    }

    for(int i = 2; i <= n; i++) {
        sum = 0; sum2 = 0; ii = !ii;
        for(int j = 1; j <= 200; j++) {
            flag = (seq[i]==-1 || seq[i]==j);
            if(flag) dp[!ii][j][0]=sum;
            else dp[!ii][j][0]=0;
            sum = (sum + dp[ii][j][0] + dp[ii][j][1] + dp[ii][j][2])%modulo;
        }
        for(int j = 1; j <= 200; j++) {
            flag = (seq[i]==-1 || seq[i]==j);
            sum = (dp[ii][j][0] + dp[ii][j][1] + dp[ii][j][2])%modulo;
            if(flag)
                dp[!ii][j][1] = sum;
            else dp[!ii][j][1] = 0;
        }
        for(int j = 200; j >= 1; j--) {
            flag = (seq[i]==-1 || seq[i]==j);
            if(flag) dp[!ii][j][2] = sum2;
            else dp[!ii][j][2] = 0;
            sum2 = (sum2 + dp[ii][j][1] + dp[ii][j][2])%modulo;
        }
    }
    ii = !ii;
    sum = 0;
    for(int i = 1; i <= 200; i++) {
        sum = (sum + dp[ii][i][1] + dp[ii][i][2]) % modulo;
    }
    printf("%lld\n", sum);
}