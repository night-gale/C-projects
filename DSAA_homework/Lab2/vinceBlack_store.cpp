#include <stdio.h>

long long array[2][100000];
int n;
long long (*mergeSort(int start, int end))[2];
long long result = 0;


int main(void) {
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &array[0][i]);
    }

    long long (*sorted)[2] = mergeSort(0, n - 1);
    for(int i = n - 1; i >= 0; i--) {
        result += sorted[i][0] * sorted[i][1];
    }
    printf("%lld", result);
}


long long (*mergeSort(int start, int end))[2] {
    if(start == end) {
        long long (*temp)[2] = new long long[1][2];
        temp[0][0] = array[0][start];
        temp[0][1] = 0;
        return temp;
    }else if((start + 1) == end) {
        long long (*temp)[2] = new long long[2][2];
        temp[0][0] = array[0][start];
        temp[1][0] = array[0][end];
        temp[0][1] = 0;
        temp[1][1] = 0;

        if(temp[0][0] > temp[1][0]) {
            int t = temp[0][0];
            temp[0][0] = temp[1][0];
            temp[1][0] = t;
            temp[0][1]++;
            temp[1][1]++;
        }
        return temp;
    }
    
    int size = end - start + 1;
    int mid = start / 2 + end / 2;
    long long (*left)[2] = mergeSort(start, mid);
    long long (*right)[2] = mergeSort(mid + 1, end);
    long long (*sorted)[2] = new long long[size][2];
    int leftCounter = 0; 
    int rightCounter = 0;
    int insertedRight = 0;
    
    
    for(int i = 0; i < size; i++) {
        if((leftCounter != (mid - start + 1)) && ((rightCounter == (end - mid)) || (left[leftCounter][0] < right[rightCounter][0]))) {
            sorted[i][1] = left[leftCounter][1] + insertedRight;
            sorted[i][0] = left[leftCounter++][0];
        }else{
            insertedRight++;
            right[rightCounter][1] += (mid - start - leftCounter + 1);
            sorted[i][1] = right[rightCounter][1];
            sorted[i][0] = right[rightCounter++][0];
        }
    }
    delete [] left;
    delete [] right;
    return sorted;
}