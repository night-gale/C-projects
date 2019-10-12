#include <stdio.h>
#include <windows.h>

int T;
int n;
int array[100];

int main(void) {
    scanf("%d\n", &T);
    for(int i = 0; i < T; i++) {
        scanf("%d\n", &n);
        for(int j = 0; j < n; j++) {
            scanf("%d", &array[j]);
        }

        for(int x = 0; x < n; x++) {
            for(int y = 0; y < n - x - 1; y++) {
                if(array[y] < array[y + 1]) {
                    int temp = array[y];
                    array[y] = array[y + 1];
                    array[y + 1] = temp;
                }
            }
        }

        if((array[2] == array[1]) || ((n > 3 && array[2] == array[3]))) {
            printf("wa\n");
        }else {
            printf("%d\n", array[2]);
        }
    }
    system("pause");
}