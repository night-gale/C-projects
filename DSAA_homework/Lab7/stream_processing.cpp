#include <stdio.h>

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

    long long delete_MIN() {
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
                next = temp->left->data > temp->right->data? temp->right: temp->left;
            }else if(temp->left) {
                next = temp->left;
            }else if(temp->right) {
                next = temp->right;
            }else {
                next = NULL;
            }
            if(next && next->data < temp->data) {
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
        while(current->parent && current->data < current->parent->data) {
            swap(current, current->parent);
            current = current->parent;
        }
    }

};

int t, k, s;
long long findNext(long long current) {
    long long result = current;
    while(current != 0) {
        result += current % 10;
        current /= 10;
    }
    return result;
}

void print_tree(Node* root) {
    printf("%lld ", root->data);
    if(root->left) {
        print_tree(root->left);
    }
    if(root->right) {
        print_tree(root->right);
    }
}

int main(void) {
    scanf("%d %d %d", &t, &k, &s);
    P_Queue p;
    long long current, answer, _min;
    answer = s;
    for(int q = 0; q < t; q++) {
        current = findNext(answer + 1 + q);

        p.insert(current);
        while(p.size > k) {
            p.delete_MIN();
        }
        
        if(q % 100 == 99) {
            answer = p.root->data;
            printf("%lld ", answer);
        }
    }
    printf("\n");
}
