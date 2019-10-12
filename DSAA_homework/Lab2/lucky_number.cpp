#include <stdio.h>
#include <windows.h>

int array[1000000];
int n, k;
int* mergeSort(int, int);

int main(void) {
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    int* sorted = mergeSort(0, n - 1);
    
    printf("%d\n", sorted[k - 1]);
    system("pause");
}

int* mergeSort(int start, int end) {
    if(start == end) {
        return new int[1]{array[start]};
    }else if((start + 1) == end) {
        int* temp = new int[2]{array[start], array[end]};
        if(temp[0] > temp[1]) {
            int t = temp[0];
            temp[0] = temp[1];
            temp[1] = t;
        }
        return temp;
    }
    
    int size = end - start + 1;
    int mid = start / 2 + end / 2;
    int* left = mergeSort(start, mid);
    int* right = mergeSort(mid + 1, end);
    int* sorted = new int[size];
    int leftCounter = 0; 
    int rightCounter = 0;
    
    for(int i = 0; i < size; i++) {
        if((leftCounter != (mid - start + 1)) && ((rightCounter == (end - mid)) || (left[leftCounter] < right[rightCounter]))) {
            sorted[i] = left[leftCounter++];
        }else{
            sorted[i] = right[rightCounter++];
        }
    }
    delete[] left, right;
    return sorted;
}
