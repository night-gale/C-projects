#include <stdio.h>
#include <windows.h>

int main(void) {
    int n, m;
    long long result = 1;
    scanf("%d %d", &n, &m);
    if(n >= 4) {
        printf("0\n");
    }else if(n < 3) {
        printf("%d\n", (n? n % m: (1 % m)));
    }else {
        if(m <= 720) {
            printf("0\n");
        }else {
            for(int i = 1; i <= 720; i++) {
                result *= i;
                result %= m;
            }
            printf("%lld\n", result);
        }
    }
    system("pause");
}