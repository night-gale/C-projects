#include <stdio.h>

char boy1[100002], boy2[100002];
int size1, size2;
int binarySearch(long long *array, int start, int end, long long key);
bool hashAndSearch(int size);
void mergeSort(long long *array, int *_index, int start, int end);
bool match(int start1, int start2, int size);

int main(void) {
    scanf("%s", &boy1);
    scanf("%s", &boy2);
    size1 = -1;
    size2 = -1;
    while(boy1[++size1] != '\0');
    while(boy2[++size2] != '\0');
    
    int max = size1 > size2? size2: size1;
    int start = 0;
    int end = max;
    while(true) {
        if(start == end - 1) {
            if(hashAndSearch(end)) {
                start = end;
            }
            break;
        }
        int mid = (start + end) / 2;

        if(hashAndSearch(mid)) {
            start = mid;
        }else {
            end = mid;
        }
    }
    printf("%d", start);
}

//ascending order
int binarySearch(long long *array, int start, int end, long long key) {
    int mid;
    while(true) {
        if(start > end) {
            return -1;
        }
        mid = (start + end) / 2;
        if(array[mid] == key) {
            return mid;
        }else if(array[mid] < key) {
            start = mid + 1;
        }else if(array[mid] > key) {
            end = mid - 1;
        }
    }
}

bool hashAndSearch(int m) {
    long long hash1[100002] = {0};
    int _index[100002] = {0};
    long long hash2[100002] = {0};
    long long _pow = 1;
    for(int i = 0; i < m - 1; i++) {
        _pow *= 131;
    }

    for(int i = 0; i < m; i++) {
        hash1[0] = hash1[0] * 131 + boy1[i];
        hash2[0] = hash2[0] * 131 + boy2[i];
    }
    _index[0] = 0;
    for(int i = 1; i <= size1 - m; i++) {
        hash1[i] = (hash1[i - 1] - boy1[i - 1] * _pow) * 131 + boy1[i + m - 1];
        _index[i] = i;
    }
    for(int i = 1; i <= size2 - m; i++) {
        hash2[i] = (hash2[i - 1] - boy2[i - 1] * _pow) * 131 + boy2[i + m - 1];
    }
    
    mergeSort(hash1, _index, 0, size1 - m);

    for(int i = 0; i <= size2 - m; i++) {
        int pos = binarySearch(hash1, 0, size1 - m, hash2[i]);
        if(pos == -1) {
            continue;
        }else {
            int left = pos;
            int right = pos;
            if(!match(_index[pos], i, m)) {
                continue;
            }else {
                return true;
            }
            //left check
            while(--left && hash1[left] == hash1[i]) {
                if(match(_index[left], i, m)) {
                    return true;
                }
            }
            while(++right != size2 -m && hash1[right] == hash1[i]){
                if(match(_index[right], i, m)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void mergeSort(long long *array, int *_index, int start, int end) {
    if(start >= end) {
        return;
    }

    int mid = (start + end) / 2;
    int leftSize = mid - start + 1;
    int rightSize = end - mid;
    mergeSort(array, _index, start, mid);
    mergeSort(array, _index, mid + 1, end);

    long long left[leftSize], right[rightSize];
    int lcounter = 0, rcounter = 0, lid[leftSize], rid[rightSize];
    for(int i = 0; i < leftSize; i++) {
        left[i] = array[start + i];
        lid[i] = _index[start + i];
    }
    for(int i = 0; i < rightSize; i++) {
        right[i] = array[mid + 1 + i];
        rid[i] = _index[mid + 1 + i];
    }
    for(int i = start; i <= end; i++) {
        if((lcounter != leftSize) && (rcounter == rightSize || left[lcounter] < right[rcounter])) {
            array[i] = left[lcounter];
            _index[i] = lid[lcounter++];
        }else {
            array[i] = right[rcounter];
            _index[i] = rid[rcounter++];
        }
    }
}

bool match(int start1, int start2, int size) {
    for(int i = 0; i < size; i++) {
        if(boy1[start1 + i] != boy2[start2 + i]) {
            return false;
        }
    }
    return true;
}