#include <stdio.h>

long long array[3200];
long long n, m;
long long counter = 0;

long long fractorial(long long n);

int main(void) {
    scanf("%lld %lld\n", &n, &m);

    for(int i = 0; i < n; i++) {
        scanf("%lld", &array[i]);
    }
    if(n < 3) {
        printf("0\n");
        return 0;
    }
    
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1; j++) {
            if(array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    
    for(long long i = 0; i < n - 2; i++) {
        long long left   = i + 1;
        long long right  = n - 1;
        long long target = m - array[i];

        while(left < right) {
            if((array[left] + array[right]) == target) {
                
                if(array[left] == array[right]) {
                    long long amount = right - left + 1;
                    counter += (amount * (amount - 1)) / 2;
                    break;
                }else {
                    int leftCounter  = 1;
                    int rightCounter = 1;
                    while((array[left]  == array[left +1])) {
                        left++;
                        leftCounter++;
                    }
                
                    while((array[right] == array[right-1])) {
                        right--;
                        rightCounter++;
                    }
                    
                    counter += leftCounter * rightCounter;
                    left++;
                    right--;
                    
                }
            }else if((array[left] + array[right]) > target) {
                right--;
            }else {
                left++;
            }
        }
    }
    printf("%lld\n", counter);
    return 0;
}


