#include <stdio.h>
#include <algorithm>

struct Score{
    int a;
    int b;
    int index;
};

const int SIZE = 5e5+1;
Score scores[SIZE];
int n;

bool cmp(Score a, Score b) {
    return a.a == b.a? a.b > b.b: a.a > b.a;
}
long long MergeSort(int start, int end);

int main(void) {
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d%d", &scores[i].a, &scores[i].b);
        scores[i].index = i;
    }

    std::sort(scores, scores+n, cmp);
    long long total = ((long long) n)*(n-1)/2;
    printf("%d", total - MergeSort(0, n-1));
}

long long MergeSort(int start, int end) {
    if(start >= end) {
        return 0;
    }
    long long x = 0;

    int mid = (start + end) / 2;
    x += MergeSort(start, mid);
    x += MergeSort(mid + 1, end);
    int ls = mid-start+1;
    int rs = end-mid;
    int lc=0, rc=0;
    Score* left = new Score[ls];
    Score* right = new Score[rs];
    for(int i = 0; i < ls; i++) {
        left[i] = scores[start+i];
    }
    for(int j = 0; j < rs; j++) {
        right[j] = scores[mid+1+j];
    }

    for(int i = start; i <= end; i++) {
        if((lc!=ls) && ((rc==rs || ((left[lc].b >= right[rc].b))))) {
            scores[i] = left[lc++];
        }else {
            x += ls-lc;
            scores[i] = right[rc++];
        }
    }
    delete [] left;
    delete [] right;
    return x;
}