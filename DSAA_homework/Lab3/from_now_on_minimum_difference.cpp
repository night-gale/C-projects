#include <stdio.h>

class Link{
    public:
    int data;
    Link* previous;
    Link* next;

    Link(int data) {
        Link::data = data;
        //initialize the pointers
        previous = 0;
        next = 0;
    }
    ~Link() {
        if(next != 0) {
            delete next;
        }
    }
};

#define MAX_LENGTH 2000000

int n;
int array[MAX_LENGTH];
Link* links[MAX_LENGTH];
int sorted[MAX_LENGTH];
Link* sortedLinks[MAX_LENGTH];
void merge(int start, int end);
int min(int a, int b) {
    if(a > b) {
        return b;
    }
    return a;
}

int abs(int a) {
    if(a < 0) {
        return -a;
    }
    return a;
}

int main(void) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
        sorted[i] = array[i];
        links[i] = new Link(array[i]);
        sortedLinks[i] = links[i];
    }
    merge(0, n - 1);

    Link* head = sortedLinks[0];
    Link* tail = head;
    for(int i = 1; i < n; i++) {
        (*tail).next = sortedLinks[i];
        (*sortedLinks[i]).previous = tail;
        tail = (*tail).next;
    }

    for(int i = 0; i < n - 1; i++) {
        int minDiff = 0;
        int left = 0;
        int right = 0;
        if(head != links[i]){
            left = (*(*links[i]).previous).data;
            (*(*links[i]).previous).next = (*links[i]).next;
        }else {
            head = (*links[i]).next;
        }
        if(tail != links[i]) {
            right = (*(*links[i]).next).data;
            (*(*links[i]).next).previous = (*links[i]).previous;
        }else {
            tail = (*links[i]).previous;
        }
        if(left == 0) {
            minDiff = abs(right - array[i]);
        }else if(right == 0) {
            minDiff = abs(left - array[i]);
        }else{
            minDiff = min(abs(left - array[i]), abs(right - array[i]));
        }
        printf("%d ", minDiff);
        (*links[i]).next = 0;
        delete links[i];
    }
    printf("\n");
}

void merge(int start, int end) {
    if(start >= end) {
        return;
    }
    int mid = (start + end) / 2;
    merge(start, mid);
    merge(mid + 1, end);
    int leftSize = mid - start + 1;
    int rightSize = end - mid;
    int left[leftSize];
    Link* leftLinks[leftSize];
    int right[rightSize];
    Link* rightLinks[rightSize];
    int leftCounter = 0;
    int rightCounter = 0;

    for(int i = 0; i < leftSize; i++) {
        left[i] = sorted[start + i];
        leftLinks[i] = sortedLinks[start + i];
    }
    for(int i = 0; i < rightSize; i++) {
        right[i] = sorted[mid + i + 1];
        rightLinks[i] = sortedLinks[mid + i + 1];
    }

    for(int i = start; i <= end; i++) {
        if((leftCounter != leftSize) && (rightCounter == rightSize || (left[leftCounter] > right[rightCounter]))) {
            sorted[i] = left[leftCounter];
            sortedLinks[i] = leftLinks[leftCounter++];
        }else {
            sorted[i] = right[rightCounter];
            sortedLinks[i] = rightLinks[rightCounter++];
        }
    }
}