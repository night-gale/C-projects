#include <stdio.h>

int array[2000001];
int n;
void merge(int, int);

int main() {
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    merge(0, n - 1);
    for(int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
}

void merge(int start, int end) {
    if(start == end) {
        return;
    }

    int mid = (end + start) / 2;
    merge(start, mid);
    merge(mid + 1, end);
    int leftSize = mid -start + 1;
    int rightSize = end - mid;
    int* left = new int[leftSize];
    int* right = new int[rightSize];
    
     
    for(int i = 0; i < leftSize; i++) {
        left[i] = array[start + i];
    }
    for(int j = 0; j < rightSize; j++) {
        right[j] = array[mid + j + 1];
    }
    int leftCounter = 0;
    int rightCounter = 0;

    for(int i = start; i <= end; i++) {
        if((leftCounter != leftSize) && ((rightCounter == rightSize || ((left[leftCounter]) < (right[rightCounter]))))) {
            array[i] = left[leftCounter++];
        }else{
            array[i] = right[rightCounter++];
        }
    }
    delete[] left;
    delete[] right;
}
