#include <stdio.h>
#include <windows.h>

void binarySearch(long long aim, int start, int end);

int LENGTH;
long long target;
int array[1000000];
long long counter;

int main(void) {
    scanf("%d", &LENGTH);
    scanf("%lld", &target);
    for(int i = 0; i < LENGTH; i++) {
        scanf("%d", &array[i]);
    }
    for(int j = 0; j < LENGTH - 1; j++) {
        if(array[j] == 0 && target != 0) {
            continue;
        }
        if((j > 0) && (array[j - 1] == array[j])) {
            continue;
        }
        long long aim;
        if(target == 0) {
            aim = 0;
            if(array[j] == 0) {
                binarySearch(aim, j + 1, LENGTH -1);
            }else{
                binarySearch(aim, 0, LENGTH - 1);
            }
        }else {
            aim = target / (long long) array[j];
            if((target % (long long) array[j]) == 0) {
                binarySearch(aim, j + 1, LENGTH - 1);
            }
        }  
    }
    if(target == 0 && array[LENGTH - 1] != 0) {
        binarySearch(0, 0, LENGTH - 1);
    }
    printf("%lld\n", counter);
    system("pause");
}

void binarySearch(long long aim, int start, int end) {
    while(true) {
        int mid = (start + end) / 2;

        if( start >= (end - 1)) {
            if(array[start] == aim || array[end] == aim) counter++;
            return;
        }

        if(array[mid] == aim) {
            counter++;
            return;
        }else if(aim > array[mid]) {
            start = mid;
        }else if(aim < array[mid]) {
            end = mid;
        }
    }
}