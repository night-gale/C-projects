#include <stdio.h>

long long fast, slow, max;
long long T, n, m;
long long limit;
long long getValidDigit(long long number);

int main(void) {
    scanf("%lld", &T);
    
    for(int i = 0; i < T; i++) {
        scanf("%lld %lld", &n, &m);
        limit = 1;
        for(int j = 0; j < n; j++) {
            limit *= 10;
        }//limit = 10 ^ n;
        fast = getValidDigit(m * m);
        slow = m;
        max  = m;
        bool circleFlag = false;

        while(true) {
            fast = getValidDigit(fast * fast);
            fast = getValidDigit(fast * fast);
            slow = getValidDigit(slow * slow);
            if(slow > max) { 
                max = slow;
            }
            if(fast == slow) {
                if(circleFlag) {
                    break;
                }else {
                    circleFlag = true;
                }
            }
        }
        printf("%lld\n", max);
    }
}

long long getValidDigit(long long number) {
    while(number >= limit) {
        number = (number / 10);
    }
    return number;
}