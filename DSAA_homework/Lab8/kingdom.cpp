#include <stdio.h>

int am[1001][1001];
int T, n, m;

int main(void) {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        int u, v;
        scanf("%d %d", &n, &m);
        for(int x = 1; x <= n; x++) {
            for(int y = 1; y <= n; y++) {
                am[x][y] = 0;
            }
        }
        for(int j = 0; j < m; j++) {
            scanf("%d %d", &u, &v);
            am[u][v]++;
        }
        for(int x = 1; x <= n; x++) {
            for(int y = 1; y <= n; y++) {
                printf("%d ", am[x][y]);
            }
            printf("\n");
        }
    }
}