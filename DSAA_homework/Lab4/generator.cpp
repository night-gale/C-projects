#include <stdio.h>

int main(void) {
    printf("%d\n%d\n", 2, 50000);
    for(int i = 50000; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\n 50000 \n");
    for(int i = 1; i <= 50000; i++) {
        printf("%d ", i);
    }
    printf("\n");
}