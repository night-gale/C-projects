/*
definition:
An AVL(Balanced) tree:

*/
#include <stdio.h>

class Node {
    public:
    int depth;
    long long data;
    Node* left;
    Node* right;
    Node* parent;

    Node() {
        Node(0, 0);
    }
    Node(long long data, int depth) {
        this->data = data;
        this->depth = depth;
        left = 0;
        right = 0;
        parent = 0;
    }
};

class AVLtree {
    public:
    Node* root;
    Node* stack[100001];
    int top;

    AVLtree() {
        root = NULL;
        top = -1;
    }

    void insert(long long data) {
        if(!root) {
            root = new Node(data, 0);
        }else {
            Node* current = find(data);
            if(!current) {
                Node* child = new Node(data, 0);
                Node* par = stack[top--];
                if(par->data < data) {
                    par->right = child;
                }else {
                    par->left = child;
                }
                child->parent = par;
                par->depth = par->depth > (child->depth + 1)? par->depth: child->depth + 1;
                while(top != -1) {
                    child = par;
                    par = stack[top--];
                    par->depth = par->depth > (child->depth + 1)? par->depth: child->depth + 1;
                    int status = isBalanced(par);
                    if(status == -2) {
                        status = isBalanced(par->right);
                        if(status == -1) {
                            //RR
                            LRotate(par);
                        }else if(status == 1) {
                            //RL
                        }
                    }else if(status == 2) {
                        status = isBalanced(par->left);
                        if(status == -1) {
                            //LR
                        }else if(status == 1) {
                            //LL
                            RRotate(par);
                        }
                    }
                }
            }
        }
    }

    Node* find(long long key) {
        Node* current = root;
        while(current) {
            stack[++top] = current;
            if(current->data < key) {
                current = current->right;
            }else if(current->data > key) {
                current = current->left;
            }else {
                break;
            }
        }
        return current;
    }

    int isBalanced(Node* subroot) {
        int ld = -1, rd = -1;
        if(subroot->left) {
            ld = subroot->left->depth;
        }
        if(subroot->right) {
            rd = subroot->right->depth;
        }
        return ld - rd;
    }

    void LRotate(Node* subroot) {
        Node* right = subroot->right;
        Node* rleft = subroot->right->left;
        right->parent = subroot->parent;
        right->left = subroot;
        if(rleft) rleft->parent = subroot;
        subroot->right = rleft;
        if(subroot->parent) {
            if(subroot->parent->left == subroot) {
                subroot->parent->left = right;
            }else {
                subroot->parent->right = right;
            }
            getDepth(subroot->parent);
        }else {
            this->root = right;
        }
        getDepth(right);
        getDepth(root);

    }

    void getDepth(Node* subroot) {
        int ld = -1, rd = -1;
        if(subroot->left->depth) {
            ld = subroot->left->depth;
        }
        if(subroot->right->depth) {
            rd = subroot->right->depth;
        }
        subroot->depth = ((ld > rd)? ld: rd) + 1;
    }

    void RRotate(Node* subroot) {
        Node* left = subroot->left;
        Node* lright = subroot->left->right;
        left->parent = subroot->parent;
        left->right = subroot;
        if(lright) lright->parent = subroot;
        subroot->left = lright;
        if(subroot->parent) {
            if(subroot->parent->left == subroot) {
                subroot->parent->left = left;
            }else {
                subroot->parent->right = left;
            }
            getDepth(subroot->parent);
        }else {
            this->root = left;
        }
        getDepth(left);
        getDepth(root);
    }
};

int main(void) {
    int n;
    scanf("%d", &n);
    AVLtree atree;

    for(int i = 0; i < n; i++) {
        long long data;
        scanf("%d", &data);
        atree.insert(data);
    }
    atree;
}