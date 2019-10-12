#include <stdio.h>

int T, n, m, array[10000];

int recurse(int n);

int main() {
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        scanf("%d %d", &n, &m);
        for(int j = 0; j < n; j++) {
            scanf("%d", &array[j]);
        }
        printf("%d\n", recurse(n) + 1);
    }
}

int recurse(int n) {
    if(n == 1) {
        return 0;
    }

    return (recurse(n - 1) + m + array[n]) % n;
}