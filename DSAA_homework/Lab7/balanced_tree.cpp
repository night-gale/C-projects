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
            Node* current = find(data, root);
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
                        }else if(status == 1 || status == 0) {
                            //RL
                            RRotate(par->right);
                            LRotate(par);
                        }
                    }else if(status == 2) {
                        status = isBalanced(par->left);
                        if(status == -1 || status == 0) {
                            //LR
                            LRotate(par->left);
                            RRotate(par);
                        }else if(status == 1) {
                            //LL
                            RRotate(par);
                        }
                    }
                }
            }
        }
    }

    void delete_Node(long long key) {
        Node* current = find(key, root);
        Node* par = current->parent;
        if(!current->left && !current->right) {
            //leaf node
            if(!par) {
                delete root;
                root = 0;
            }else {
                if(par->left == current) {
                    delete par->left;
                    par->left = 0;
                }else {
                    delete par->right;
                    par->right = 0;
                }
            }
        }else {
            //eternal node
            Node* relp;;
            if(current->left) {
                //has left node
                relp = current->left;
                while(relp->right) {
                    stack[++top] = relp;
                    relp = relp->right;
                }
                if(relp != current->left) {
                    //current node has a predecessor
                    current->data = relp->data;
                    relp->parent->right = relp->left;
                    if(relp->left) relp->left->parent = relp->parent->left;
                    getDepth(current->left);
                    getDepth(current);
                    if(par) getDepth(par);
                    delete relp;
                }else {
                    //current node does not have a predecessor
                    current->data = relp->data;
                    if(relp->left) relp->left->parent = current;
                    current->left = relp->left;
                    if(current->left) getDepth(current->left);
                    delete relp;
                    getDepth(current);
                    if(par) getDepth(par);
                }
            }else {
                relp = current->right;
                while(relp->left) {
                    stack[++top] =relp;
                    relp = relp->right;
                }
                if(relp != current->right) {
                    //current node has a successor
                    current->data = relp->data;
                    relp->parent->left = relp->right;
                    if(relp->right) relp->right->parent = relp->parent->right;
                    getDepth(current->right);
                    getDepth(current);
                    if(par) getDepth(par);
                    delete relp;
                }else {
                    //current node does not have a successor
                    current->data = relp->data;
                    if(relp->right) relp->right->parent = current;
                    current->right = relp->right;
                    if(current->right) getDepth(current->right);
                    delete relp;
                    getDepth(current);
                    if(par) getDepth(par);
                }
            }
            
            while(top != -1) {
                current = stack[top--];
                int status = isBalanced(current);
                if(status == -2) {
                    //right > left
                    status = isBalanced(current->right);
                    if(status == -1) {
                        //RR inbalance
                        LRotate(current);
                    }else if(status == 1 || status == 0) {
                        //RL inbalance
                        RRotate(current->right);
                        LRotate(current);
                    }else {

                    }
                }else if(status == 2) {
                    //left > right
                    status = isBalanced(current->left);
                    if(status == 1) {
                        //LL inbalance
                        RRotate(current);
                    }else if(status == -1 || status == 0) {
                        //LR inbalance
                        LRotate(current->left);
                        RRotate(current);
                    }
                }
            }
        }
    }

    Node* find(long long key, Node* subroot) {
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
        }else {
            this->root = right;
            right->parent = 0;
        }
        subroot->parent = right;
        getDepth(subroot);
        getDepth(right);
        if(right->parent) getDepth(right->parent);
    }

    void getDepth(Node* subroot) {
        int ld = -1, rd = -1;
        if(subroot->left) {
            ld = subroot->left->depth;
        }
        if(subroot->right) {
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
            
        }else {
            this->root = left;
            left->parent = 0;
        }
        subroot->parent = left;
        getDepth(subroot);
        getDepth(left);
        if(left->parent) getDepth(left->parent);
    }

    void print_tree(Node* subroot) {
        if(subroot->left) {
            print_tree(subroot->left);
        }
        printf("%lld ", subroot->data);
        if(subroot->right) {
            print_tree(subroot->right);
        }
    }
};

int main(void) {
    int n;
    scanf("%d", &n);
    AVLtree atree;
    long long data;
    for(int i = 0; i < n; i++) {
        scanf("%lld", &data);
        atree.insert(data);
    }
    atree.print_tree(atree.root);
    printf("\n");
}