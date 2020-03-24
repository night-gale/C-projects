/*** sorting and Linked list
 * by reversedly removing element from sorted Linked list

*/
#include <stdio.h>

struct Node{
    long long data;
    int next;
    int former;
};

void merge(int start, int end);

const int _MAX_NODES_ = 2000001;
Node* links;
int n;
long long array[2][_MAX_NODES_];
long long left[_MAX_NODES_];
long long left_i[_MAX_NODES_];
long long right[_MAX_NODES_];
long long right_i[_MAX_NODES_];
long long sum;

int main(void) {
    scanf("%d", &n);
    sum = 0;

    links = new Node[n];
    for(int i = 0; i < n; i++) {
        scanf("%lld", &array[0][i]);
        array[1][i] = i;
        links[i].data = array[0][i];
        links[i].next = -1;
        links[i].former = -1;
    }
    sum += array[0][0];
    merge(0, n-1);
    for(int i = 0; i < n; i++) {
        if(i != 0) {
            links[array[1][i]].former = array[1][i-1];
            links[array[1][i-1]].next = array[1][i];
        }
        if(i != n - 1) {
            links[array[1][i]].next = array[1][i+1];
            links[array[1][i+1]].former = array[1][i];
        }
    }
    
    long long _left;
    long long _right;
    for(int i = (n - 1); i >= 1; i--) {
        _left = __INT32_MAX__;
        _right = __INT32_MAX__;
        if(links[i].next != -1) {
            _right = (links[i].data - links[links[i].next].data);
            _right = _right>0?_right:-_right;
            links[links[i].next].former = links[i].former;
        }
        if(links[i].former != -1) {
            _left = (links[i].data - links[links[i].former].data);
            _left = _left>0?_left:-_left;
            links[links[i].former].next = links[i].next;
        }
        
        sum += (_left>_right)?(_right):(_left);
    }

    printf("%lld", sum);
}

void merge(int start, int end) {
    if(start >= end) {
        return;
    }

    int mid = (end + start) / 2;
    merge(start, mid);
    merge(mid + 1, end);
    int leftSize = mid -start + 1;
    int rightSize = end - mid;
    
    for(int i = 0; i < leftSize; i++) {
        left[i] = array[0][start + i];
        left_i[i] = array[1][start + i];
    }
    for(int j = 0; j < rightSize; j++) {
        right[j] = array[0][mid + j + 1];
        right_i[j] = array[1][mid + j + 1];
    }
    int leftCounter = 0;
    int rightCounter = 0;

    for(int i = start; i <= end; i++) {
        if((leftCounter != leftSize) && ((rightCounter == rightSize || ((left[leftCounter]) < (right[rightCounter]))))) {
            array[1][i] = left_i[leftCounter];
            array[0][i] = left[leftCounter++];
        }else{
            array[1][i] = right_i[rightCounter];
            array[0][i] = right[rightCounter++];
        }
    }
}
