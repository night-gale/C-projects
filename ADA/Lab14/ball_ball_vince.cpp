#include <stdio.h>
#include <algorithm>

using namespace std;

int A[101], B[101];
int Bp[101];
const int C = 101;
int dp[101][101*101+5];
int N, m, sum, result;

bool cmp(int a, int b) {
    return a > b;
}

inline int max(int a, int b) {
    if(a > b) return a;
    return b;
}

int main(void) {
    m = 0; sum = 0;
    int tmp = 0;
    int cost;
    result = 0;

    scanf("%d", &N);

    for(int i = 1; i <= N; i++) {
        scanf("%d%d", &A[i], &B[i]);
        Bp[i] = B[i];
        sum += A[i];
    }
    tmp = 0;

    sort(Bp+1, Bp+N+1, cmp);
    for(int i = 1; i <= N; i++) {
        if(tmp < sum) {
            m++;
            tmp += Bp[i];
        }
    }
    cost = m*C-sum;
    for(int i = 1; i <= m; ++i) {
        for(int j = 0; j <= cost; ++j) {
            dp[i][j] = -__INT32_MAX__;
        }
    }
    for(int i = 1; i <= N; ++i) {
        for(int j = m; j >= 1; --j) {
            for(int w = cost; w >= 0; --w) {
                if(w < (C-B[i])) continue;
                dp[j][w] = max(dp[j][w], dp[j-1][w-(C-B[i])]+A[i]);
            }
        }
    }
    for(int w = 0; w <= cost; ++w) {
        if(result < dp[m][w]) result = dp[m][w];
    }
    printf("%d", sum-result);
}