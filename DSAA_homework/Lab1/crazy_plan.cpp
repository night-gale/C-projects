#include <stdio.h>

long long turns;
long long n;


int main(void) {
    scanf("%lld", &turns);
    for(int i = 0; i < turns; i++) {
        scanf("%lld", &n);
        printf("%lld\n", (n + 1) * (n * n + 2 * n) / 6);
    }
}