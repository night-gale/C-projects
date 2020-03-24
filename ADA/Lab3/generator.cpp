#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned)time(0));

    int n = 10001;
    printf("%d\n", n);
    for(int i = 0; i < n; i++) {
        int temp = ((double)(rand()/double(RAND_MAX))) * (1e9-1);
        printf("%d ", temp);
    }
    printf("\n");
}