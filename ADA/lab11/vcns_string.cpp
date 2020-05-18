#include <stdio.h>
#include <cmath>

long long n, u, v;
long long list[65][3];
long long result[3];
void count(long long size, int flag);
long long myPow(long long base, long long exp);


int main(void) {
    scanf("%lld", &n);
    list[0][0] = 1;
    list[0][1] = 0;
    list[0][2] = 0;
    for(int i = 1; i < 64; i++) {
        // 0:V 1:C 2:N
        for(int j = 0; j < 3; j++) {
            // printf("%d", (j+2)%3);
            list[i][j] = list[i-1][j] + list[i-1][(j+2)%3];
        }
    }

    for(int i = 0; i < n; i++) {
        scanf("%lld", &u);
        for(int j = 0; j < 3; j++) {
            result[j] = 0;
        }
        count(u, 0);
        for(int j = 0; j < 3; j++) {
            printf("%lld ", result[j]);
        }
        printf("\n");
    }    
}

void count(long long size, int flag) {
    if(size <= 0) {
        return;
    }
    long long left = floor(log2(size));
    for(int i = 0; i < 3; i++) {
        result[i] += list[left][(i+flag)%3];
    }
    count(size - myPow(2, left), (flag+2)%3);
}

long long myPow(long long base, long long exp) {
    long long result = 1;
    for(int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}