#include <stdio.h>
#include <vector>

using namespace std;

enum COLOR{WHITE=0, YELLOW=1, RED=2};

class Node {
    public:
    long long data;
    Node* left;
    Node* right;
    Node* parent;

    Node() {
        Node(0);
    }
    Node(long long data) {
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

    void insert(long long data) {
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

    long long delete_MAX() {
        if(size == 1) {
            long long _data = root->data;
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
        long long _data = current->data;
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
                next = temp->left->data > temp->right->data? temp->left: temp->right;
            }else if(temp->left) {
                next = temp->left;
            }else if(temp->right) {
                next = temp->right;
            }else {
                next = NULL;
            }
            if(next && next->data > temp->data) {
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
        long long temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    void heapfy(Node* current) {
        while(current->parent && current->data > current->parent->data) {
            swap(current, current->parent);
            current = current->parent;
        }
    }

};

class gNode{
    public:
    int data;
    vector<gNode*> ad;
    int in_degree;
    COLOR color;
    gNode(int data) {
        this->data = data;
        in_degree = 0;
    }
};

struct Block{
    gNode* root;
    int smallest = __INT32_MAX__;
    vector<gNode*> topoList;
};

int main(void) {
    int n;
    scanf("%d", &n);
    P_Queue pq;
    for(int i = 0; i < n; i++) {
        int temp;
        scanf("%d", &temp);
        pq.insert(temp);
    }
    for(int i = 0; i < n; i++) {
        printf("%d ", pq.delete_MAX());
    }
}