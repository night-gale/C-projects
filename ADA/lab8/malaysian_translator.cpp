#include <stdio.h>
#include <algorithm>

using namespace std;

int map[256];
int n;
char str[100002];
int heap[30];
int size, cnt;
int u, v;
int cost;

bool cmp(int a, int b) {
    return a > b;
}

int main(void) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        size = 0;
        cnt = 0;
        cost = 0;
        for(int j = 0; j < 256; j++) {
            map[j] = 0;
        }
        scanf("%s", &str);
        
        while(str[cnt] != '\0') {
            map[str[cnt]]++;
            cnt++;
        }

        for(int j = 0; j < 256; j++) {
            if(map[j]) {
                heap[size++] = map[j];
            }
        }

        if(size == 1) {
            printf("%d\n", heap[0]);
            continue;
        }

        make_heap(heap, heap+size, cmp);

        while(size != 1) {
            u = heap[0];
            pop_heap(heap, heap+size, cmp);
            size--;
            v = heap[0];
            pop_heap(heap, heap+size, cmp);
            size--;
            heap[size] = u+v;
            cost += heap[size];
            push_heap(heap, heap+size, cmp);
            size++;
        }

        printf("%d\n", cost);
    }
}