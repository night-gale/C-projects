#include <stdio.h>
#include <windows.h>

int T;
long long n;
long long result;

int main(void) {
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        result = 0;
        scanf("%lld", &n);
        while(true) {
            n /= 5;
            result += n;
            if(n < 5) {
                break;
            }
        }
        printf("%lld\n", result);
    }
    system("pause");
}