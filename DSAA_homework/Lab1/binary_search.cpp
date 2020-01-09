#include <stdio.h>


int n;
int A[100001];
int key;

int main(void) {
    int start, end, mid;
    scanf("%d", &n);
    start = 0;
    end = n;
    for(int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    scanf("%d", &key);

    while(start + 1 < end) {
        mid = (start + end) / 2;

        if(A[mid] <= key) {
            start = mid;
        }else {
            end = mid;
        }
    }

    printf("%d", start);
}