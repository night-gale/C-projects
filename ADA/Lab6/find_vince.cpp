#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

enum COLOR{YELLOW, WHITE};

class Edge {
    public:
    int u;
    int v;
    long long weight;
};

class Vertex {
    public:
    int index;
    int a;
    int b;
    COLOR c;
    long long cost;
    std::vector<Edge*> aj;
};


class Heap {
    Vertex* arr[100001];
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
        return a->cost < b->cost;
    }
};

const int k_N_SIZE = 10001;
const int k_M_SIZE = 100001;
int N, M, u, v, w, cnt, ai, bi;
Vertex* vert[k_N_SIZE];
Edge* edges[k_M_SIZE];
Vertex *curr, *nex;
long long cost, ttw;
// std::priority_queue<Vertex*, std::vector<Vertex*>, Cmp> heap;
Heap h;
const long long _Max_ = 1000000000000000000;

int main(void) {
    cnt = 0;
    scanf("%d%d", &N, &M);

    for(int i = 1; i <= N; i++) {
        vert[i] = new Vertex();
        vert[i]->index = i;
        vert[i]->c = WHITE;
        vert[i]->cost = _Max_;
    }

    for(int i = 1; i <= M; i++) {
        edges[i] = new Edge();
        scanf("%d%d%d", &edges[i]->u, &edges[i]->v, &edges[i]->weight);
        vert[edges[i]->u]->aj.push_back(edges[i]);
    }

    for(int i = 1; i <= N; i++) {
        scanf("%d%d", &vert[i]->a, &vert[i]->b);
    }

    vert[1]->cost = 0;
    // pq.insert(new Data(1, 0));
    // heap.push(vert[1]);
    h.insert(vert[1]);
    while(true) {
        // data = pq.delete_MIN();
        curr = h.pop();
        if(curr->index == N) break;
        // heap.pop();
        // delete data;
        if(curr->c != WHITE) continue;
        curr->c = YELLOW;
        if(curr->b == 0) continue;
        for(int i = 0; i < curr->aj.size(); i++) {
            nex = vert[curr->aj[i]->v];
            if(nex->c != WHITE || nex->b == 0) continue;
            ttw = (curr->cost + curr->aj[i]->weight)%(nex->a+nex->b);
            if(ttw >= nex->a) {
                ttw = 0;
            }else {
                ttw = nex->a-ttw;
            }
            cost = curr->aj[i]->weight + curr->cost + ttw;
            if(cost < nex->cost && nex->b != 0) {
                nex->cost = cost;
                // pq.insert(new Data(nex->index, nex->cost));
                h.insert(nex);
            }
        }
    }

    printf("%lld\n", vert[N]->cost);
    // printf("%f\n", std::log10(__INT64_MAX__));
    // printf("%lld\n", __INT64_MAX__*10);
}
