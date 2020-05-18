#include <stdio.h>
#include <cmath>
// #include <chrono>

long long n, u, v;

long long count(long long size, bool isLeft);
long long myPow(long long base, long long exp);

int main(void) {
    scanf("%d", &n);
    // printf("%lld", __INT64_MAX__);
    for(int i = 0; i < n; i++) {
        scanf("%lld%lld", &u, &v);

        printf("%lld\n", count(v, 1)-count(u-1, 1));
    }
}

long long count(long long size, bool isLeft) {
    if(size == 1) {
        return 1;
    }else if(size <= 0) {
        return 0;
    }
    long long left = myPow(2, floor(log2(size+1))) - 1;
    long long right = size - left - 1;
    if(left < size) {
        return ((left/2)?(left/2 + 1):1) + isLeft + count(size-left-1, (right>(left/2))?0:1); 
    }else {
        return (left/2)?(left/2 + 1):1;
    }
    // return left/2?(left/2):(1) + isLeft + count(size-left-1, !isLeft);
}

long long myPow(long long base, long long exp) {
    long long result = 1;
    for(int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}