/*
    dijkstra algorithm
    dist[n][k] = min(dist[parents of n with portal][k - 1], 
                     dist[parents of n without portal][k] + edge(u, v))
*/
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;
enum COLOR{WHITE = 0, YELLOW = 1, RED = 2};

class Edge {
    public:
    int index;
    int u, v;
    long long weight;
    Edge(int u, int v,int index, long long weight):
        u(u), v(v),
        index(index),
        weight(weight) {
    }
};

class Vertex {
    public:
    int index;
    vector<Edge*> out_edges;
    COLOR color;
    long long dist[11];
    Vertex(int index, long long dist):index(index){
        this->color = WHITE;
        for(int i = 0; i < 11; i++) {
            this->dist[i] = dist;
        }
    };
};

struct Data {
    int portal_cnt;
    long long dist;
    int index;
    Data(int index, int portal_cnt, long long dist):index(index), portal_cnt(portal_cnt), dist(dist) {};
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
        return a->data->dist > b->data->dist;
    }
};

int n, m, p, k, u, v, w;
int s, t;
Vertex* vertices[50001];
Edge* edges[100001];
P_Queue heap;
vector<Vertex*> list;
int main(void) {
    scanf("%d %d %d %d", &n, &m, &p, &k);
    for(int i = 1; i <= n; i++) {
        vertices[i] = new Vertex(i, __INT64_MAX__/2);
    }

    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        edges[i] = new Edge(u, v, i, w);
        vertices[u]->out_edges.push_back(edges[i]);
    }

    for(int i = 0; i < p; i++) {
        scanf("%d %d", &u, &v);
        edges[m + i] = new Edge(u, v, m + i, 0);
        vertices[u]->out_edges.push_back(edges[m + i]);
    }

    scanf("%d %d", &s, &t);
    vertices[s]->dist[0] = 0;
    heap.insert(new Data(s, 0, vertices[s]->dist[0]));
    Vertex *current, *next;
    Data *curr_data;
    while(heap.size != 0) {
        curr_data = heap.delete_MIN();
        current = vertices[curr_data->index];

        for(int i = 0; i < current->out_edges.size(); i++) {
            next = vertices[current->out_edges[i]->v];
            if(current->out_edges[i]->weight == 0) {
                if(curr_data->portal_cnt == k) continue;
                if(next->dist[curr_data->portal_cnt + 1] > curr_data->dist) {
                    next->dist[curr_data->portal_cnt + 1] = curr_data->dist;
                    heap.insert(new Data(next->index, curr_data->portal_cnt + 1, next->dist[curr_data->portal_cnt + 1]));
                }
            }else {
                if(next->dist[curr_data->portal_cnt] > curr_data->dist + current->out_edges[i]->weight) {
                    next->dist[curr_data->portal_cnt] = curr_data->dist + current->out_edges[i]->weight;
                    heap.insert(new Data(next->index, curr_data->portal_cnt, next->dist[curr_data->portal_cnt]));
                }
            }
        }
    }

    long long cost = __INT64_MAX__;
    for(int i = 0; i <= k; i++) {
        cost = std::min(vertices[t]->dist[i], cost);
    }
    printf("%lld", cost);
}