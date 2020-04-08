#include <stdio.h>

struct Vertex {
    int log_dis;
};

class Heap {
    public:
    Vertex* arr[100002];
    int size;
    public:
    Heap() {
        size = 0;
    }

    void insert(Vertex* a) {
        arr[++size] = a;
        int k = size;
        int n = k>>1;
        while(n != 0) {
            if(cmp(arr[k], arr[n])) {
                Vertex* tmp = arr[k];
                arr[k] = arr[n];
                arr[n] = tmp;
                k = n;
                n = k>>1;
            }else {
                break;
            }
        }
    }

    Vertex* pop() {
        Vertex* tmp = arr[1];
        arr[1] = arr[size];
        arr[size] = tmp;
        int k = 1;
        int u = k<<1; //2k
        int v = u+1;  //2k+1
        int sml;
        while(k < size-1) {
            if(v < size && cmp(arr[v],arr[u])) {
                sml = v;
            }else if(u < size) sml = u;
            else break;
            if(cmp(arr[sml], arr[k])) {
                tmp = arr[k];
                arr[k] = arr[sml];
                arr[sml] = tmp;
                k = sml;
                u = k<<1;
                v = u + 1;
            }else {
                break;
            }
        }
        return arr[size--];
    }

    bool cmp(Vertex* a, Vertex* b) {
        return a->log_dis < b->log_dis;
    }
};

int n;
Vertex* vert[100002];
Heap heap;

int main(void) {
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        vert[i] = new Vertex();
        scanf("%d", &vert[i]->log_dis); 
        heap.insert(vert[i]);
    }

    for(int i = 0; i < n; i++) {
        printf("%d ", heap.pop()->log_dis);
    }
    // printf("%d", heap.size);
    printf("\n");
}