#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int length = 100000;
int array[length];
int sorted[length];
int n;
int Partition(int low, int high);
void quicksort(int low, int high);

int main(void) {
    srand((unsigned) time(0));
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    quicksort(0, n - 1);

    for(int i = 0; i < n; i++) {
        printf("%d ", sorted[i]);
    }
}

int Partition(int low, int high) {
    int p = rand() % (high - low + 1) + low;
    int pivot = array[p];
    int left = low;
    int right = high;
    for(int i = low; i <= high; i++) {
        if(array[i] < pivot) sorted[left++] = array[i];
        else sorted[right--] = array[i];
    }
    for(int i = low; i <= high; i++) {
        array[i] = sorted[i];
    }
    return left; //left at pivot index
}

void quicksort(int low, int high) {
    if(low >= high) {
        return;
    }
    int p = Partition(low, high);
    quicksort(low, p - 1);
    quicksort(p + 1, high);
}

