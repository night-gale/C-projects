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
    COLOR c;
    double log_dis;
    std::vector<Edge*> aj;
};

struct Cmp{
    bool operator()(Vertex* a, Vertex* b) {
        return a->log_dis > b->log_dis;
    }
};

struct Data{
    int index;
    double log_dis;
    Data(int index, double log_dis) {
        this->index = index;
        this->log_dis = log_dis;
    }
};

class Node {
    public:
    Data* data;
    Node* left;
    Node* right;
    Node* parent;

    Node(Data* data) {
        this->data = data;
        left = 0;
        right = 0;
        parent = 0;
    }
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
            }else if(u < size -1) sml = u;
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

const int k_SIZE = 10001;
const int k_NUM_EDGES = 1000001;
Vertex* vert[k_SIZE];
Edge* edges[k_NUM_EDGES];
int N, M;
long long dis[k_SIZE];
double dis_log[k_SIZE];
int iu, iv, iw;
std::priority_queue<Vertex*, std::vector<Vertex*>, Cmp> heap;
Heap h;
Vertex *curr, *nex;
Data *data;
long long modulo = 19260817;

bool cmp(Vertex* a, Vertex* b) {
    return a->log_dis > a->log_dis;
}

int main(void) {
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++) {
        vert[i] = new Vertex();
        vert[i]->index = i;
        vert[i]->log_dis = __INT32_MAX__;
        vert[i]->c = WHITE;
    }

    for(int i = 1; i <= M; i++) {
        scanf("%d%d%d", &iu, &iv, &iw);
        edges[i] = new Edge();
        edges[i]->u = iu;
        edges[i]->v = iv;
        edges[i]->weight = iw;
        vert[iu]->aj.push_back(edges[i]);
    }

    // pQueue.insert(new Data(1, 0));
    
    vert[1]->log_dis = 0;
    h.insert(vert[1]);
    dis[1] = 1;

    int cnt = 0;
    while(cnt < N-1) {
        curr = h.pop();
        // heap.pop();
        if(curr->c != WHITE) continue;
        curr->c = YELLOW;
        cnt++;
        for(int i = 0; i < curr->aj.size(); i++) {
            nex = vert[curr->aj[i]->v];
            if(nex->c == YELLOW) continue;
            double log_d1 = log(curr->aj[i]->weight) + curr->log_dis;
            if(log_d1 < nex->log_dis) {
                nex->log_dis = log_d1;
                dis[nex->index] = (dis[curr->index] * curr->aj[i]->weight) % modulo;
                h.insert(nex);
            }
        }
    }    
    printf("%lld\n", dis[vert[N]->index]);
}