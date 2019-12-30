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
    int w;
    int u;
    int v;
    COLOR color = WHITE;
    Edge(int u, int w, int v, int index):w(w),u(u),v(v),index(index){
        color = WHITE;
    }
};

class Vertex {
    public:
    int index;
    vector<Edge*> edges;
    COLOR color;
    Vertex(int index):index(index){
        this->color = WHITE;
    };
};

struct Data {
    int index;
    int w;
    Data(int index, int w):index(index), w(w) {};
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
        return a->data->w > b->data->w;
    }
};

int n, m, u, v, w;
Vertex* vertices[1001];
Edge* edges[10001];
P_Queue heap;
vector<Vertex*> list;
int main(void) {
    scanf("%d %d", &n, &m);
    int min_edge_index = -1;
    int min_w = __INT32_MAX__;
    int cost = 0;
    Data* current;

    for(int i = 1; i <= n; i++) {
        vertices[i] = new Vertex(i);
    }

    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        edges[i] = new Edge(u, w, v, i);
        if(min_w > w) {
            min_w = w;
            min_edge_index = i;
        }
        vertices[u]->edges.push_back(edges[i]);
        vertices[v]->edges.push_back(edges[i]);
    }

    heap.insert(new Data(min_edge_index, min_w));
    edges[min_edge_index]->color = YELLOW;
    while(list.size() != n) {
        current = heap.delete_MIN();
        Vertex* v1 = vertices[edges[current->index]->u];
        Vertex* v2 = vertices[edges[current->index]->v];

        if(v1->color == WHITE || v2->color == WHITE) cost += edges[current->index]->w;
        if(v1->color == WHITE) {
            list.push_back(v1);
            for(int j = 0; j < v1->edges.size(); j++) {
                if(v1->edges[j]->color == WHITE) {
                    heap.insert(new Data(v1->edges[j]->index, v1->edges[j]->w));
                    v1->edges[j]->color = YELLOW;
                }
            }
        }
        if(v2->color == WHITE) {
            list.push_back(v2);
            for(int j = 0; j < v2->edges.size(); j++) {
                if(v2->edges[j]->color == WHITE) {
                    heap.insert(new Data(v2->edges[j]->index, v2->edges[j]->w));
                    v2->edges[j]->color = YELLOW;
                }
            }
        }
        v1->color = YELLOW;
        v2->color = YELLOW;
    }
    printf("%d\n", cost);
}