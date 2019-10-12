#include <stdio.h>

int T, n, heights[50001];
int queue[2][50003] = {{0}, {0}};
int partner[2][50001] = {{0}, {0}};

int main(void) {
    scanf("%d", &T);
    
    for(int i = 0; i < T; i++) {
        scanf("%d", &n);
        for(int j = 0; j < n; j++) {
            scanf("%d", &heights[j]);
        }

        for(int left = 0; left < 2; left++) {
            int top = -1;
            if(left == 0) {
                for(int j = 0; j <= n; j++) {
                    int temp[2] = {-1, -1};
                    while((top != -1) && ((j == n) || (heights[j] > queue[0][top]))) {
                        if(temp[0] == -1) {
                            temp[0] = queue[0][top];
                            temp[1] = queue[1][top--];
                            partner[left][temp[1]] = 0;
                        }else {
                            partner[left][queue[1][top]] = temp[1];
                            temp[0] = queue[0][top];
                            temp[1] = queue[1][top--];
                        }
                    }
                    if(j != n) {
                        queue[0][++top] = heights[j];
                        queue[1][top] = j + 1;
                    }
                }
            }else {
                for(int j = n - 1; j >= -1; j--) {
                    int temp[2] = {-1, -1};
                    while((top != -1) && ((j == -1) || (heights[j] > queue[0][top]))) {
                        if(temp[0] == -1) {
                            temp[0] = queue[0][top];
                            temp[1] = queue[1][top--];
                            partner[left][temp[1]] = 0;
                        }else {
                            partner[left][queue[1][top]] = temp[1];
                            temp[0] = queue[0][top];
                            temp[1] = queue[1][top--];
                        }
                    }
                    if(j != -1) {
                        queue[0][++top] = heights[j];
                        queue[1][top] = j + 1;
                    }
                }
            }
        }
        printf("Case %d:\n", i + 1);
        for(int j = 1; j <= n; j++) {
            printf("%d %d\n", partner[1][j], partner[0][j]);
        }
    }
}
