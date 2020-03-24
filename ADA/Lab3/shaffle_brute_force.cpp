#include <stdio.h>
#include <cmath>

const int MAX_CASES = 400001;
int n;
long long list[MAX_CASES];
long long modulo = 998244353;
long long result;

void shuffle(long long, long long);

int main(void) {
    result = 0;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%lld", &list[i]);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            shuffle(list[i],list[j]);
        }
    }
    printf("%lld", result);
}


void shuffle(long long a, long long b) {
    long long toMult = 1;
    long long toDiv = 1;
    int l1 = log10(a) + 1;
    int l2 = log10(b) + 1;
    if(a > b) {
        for(int k = 0; k < l2; k++) {
            int d1 = a / toDiv % 10;
            int d2 = b / toDiv % 10;
            result = (result + ((d1 * 10 + d2) * (toMult % modulo)) % modulo) % modulo;
            toMult *= 100;
            toDiv *= 10;
        }
        for(int k = l2; k < l1; k++) {
            int d1 = a / toDiv % 10;
            int d2 = b / toDiv % 10;
            result = (result + ((d1) * (toMult % modulo)) % modulo);
            toDiv *= 10;
            toMult *= 10;
        }
    }
    else {
        for(int k = 0; k < l1; k++) {
            int d1 = a / toDiv % 10;
            int d2 = b / toDiv % 10;
            result = (result + ((d1 * 10 + d2) * (toMult % modulo)) % modulo) % modulo;
            toMult *= 100;
            toDiv *= 10;
        }
        for(int k = l1; k < l2; k++) {
            int d1 = a / toDiv % 10;
            int d2 = b / toDiv % 10;
            result = (result + ((d2) * (toMult % modulo)) % modulo);
            toDiv *= 10;
            toMult *= 10;
        }
    }
}