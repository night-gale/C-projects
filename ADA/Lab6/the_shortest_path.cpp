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

class P_Queue {
    public:
    Node* root;
    int size;
    int stack[100];
    int top;
    P_Queue() {
        root = 0;
        size = 0;
        top = -1;
    }

    void insert(Data* data) {
        Node* newNode = new Node(data);
        size++;
        if(!root) {
            root = newNode;
            return;
        }else {
            Node* current = find(size);
            if(stack[top--]) {
                current->right = newNode;
            }else {
                current->left = newNode;
            }
            newNode->parent = current;
            current = newNode;
            heapfy(current);
        }
    }

    Data* delete_MIN() {
        if(size == 1) {
            Data* _data = root->data;
            delete root;
            root = NULL;
            size = 0;
            return _data;
        }
        Node* current = find(size);
        current = stack[top]? current->right: current->left;
        swap(current, root);
        size--;
        Node* temp = root;
        Node* next;
        Data* _data = current->data;
        current = current->parent;
        
        if(stack[top--]) {
            delete current->right;
            current->right = NULL;
        }else {
            delete current->left;
            current->left = NULL;
        }
        while(temp) {
            if(temp->left && temp->right) {
                next = comparator(temp->left, temp->right)? temp->right: temp->left;
            }else if(temp->left) {
                next = temp->left;
            }else if(temp->right) {
                next = temp->right;
            }else {
                next = NULL;
            }
            if(next && comparator(temp, next)) {
                swap(next, temp);
                temp = next;
            }else {
                break;
            }
        }

        return _data;
    }

    private:
    Node* find(int _size) {
        int temp = _size;
        Node* current = root;
        while(temp != 1) {
            stack[++top] = temp & 1;
            temp = temp >> 1;
        }
        while(top >= 1) {
            if(stack[top--]) {
                current = current->right;
            }else {
                current = current->left;
            }
        }
        return current;
    }

    void swap(Node* a, Node* b) {
        Data* temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    void heapfy(Node* current) {
        while(current->parent && comparator(current->parent, current)) {
            swap(current, current->parent);
            current = current->parent;
        }
    }

    bool comparator(Node* a, Node* b) {
        return a->data->log_dis > b->data->log_dis;
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
P_Queue pQueue;
std::priority_queue<Vertex*, std::vector<Vertex*>, Cmp> heap;
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

    pQueue.insert(new Data(1, 0));
    vert[1]->log_dis = 0;
    dis[1] = 1;

    int cnt = 0;
    while(cnt < N-1) {
        data = pQueue.delete_MIN();
        curr = vert[data->index];
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
                pQueue.insert(new Data(nex->index, nex->log_dis));
            }
        }
    }    
    printf("%lld\n", dis[vert[N]->index]);
}