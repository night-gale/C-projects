#include <stdio.h>

class Node {
    public:
    long long data;
    Node* left;
    Node* right;

    Node() {
        Node(0);
    }
    Node(int data) {
        this->data = data;
        left = 0;
        right = 0;
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
            int temp = size;
            Node* current = root;
            while(temp != 1) {
                stack[++top] = temp & 1;
                temp = temp >> 1;
            }
            while(top != 0) {
                if(stack[top--]) {
                    current = current->right;
                }else {
                    current = current->left;
                }
            }
            if(stack[top--]) {
                current->right = newNode;
            }else {
                current->left = newNode;
            }
        }
    }
};


int main(void) {
    P_Queue a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a;
}