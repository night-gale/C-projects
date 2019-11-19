#include <stdio.h>
#include <iostream>
using namespace std;

long long _abs(long long a) {
    if(a > 0) {
        return a;
    }else {
        return -a;
    }
}

class Node {
    public:
    int depth;
    long long data;
    int nchild;
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
        nchild = 0;
    }
    ~Node() {
        parent = 0;
        left = 0;
        right = 0;
        depth = -1;
        nchild = -1;
        data = -1;
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
                Node* par = stack[top];
                if(par->data < data) {
                    par->right = child;
                }else {
                    par->left = child;
                }
                child->parent = par;
                while(top != -1) {
                    child = par;
                    par = stack[top--];
                    int status = isBalanced(par);
                    if(status == -2) {
                        status = isBalanced(par->right);
                        if(status == -1 || status == 0) {
                            //RR
                            LRotate(par);
                        }else if(status == 1) {
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
                    }else {
                        getDepth(par);
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
                root = 0;
                top = 0;
                return;
            }else {
                if(par->left == current) {
                    par->left = 0;
                    top--;
                }else if(par->right == current) {
                    par->right = 0;
                    top--;
                }
                getDepth(par);
            }
            delete current;
        }else {
            //internal node
            Node* relp;
            if(current->left) {
                //has left node
                relp = current->left;
                while(relp->right) {
                    stack[++top] = relp;
                    relp = relp->right;
                }
                current->data = relp->data;
                if(relp != current->left) {
                    //current node has a predecessor
                    relp->parent->right = relp->left;
                    if(relp->left) relp->left->parent = relp->parent;
                }else {
                    //current node does not have a predecessor
                    if(relp->left) relp->left->parent = current;
                    current->left = relp->left;
                }
                delete relp;
            }else {
                relp = current->right;
                while(relp->left) {
                    stack[++top] = relp;
                    relp = relp->left;
                }
                current->data = relp->data;
                if(relp != current->right) {
                    //current node has a successor
                    relp->parent->left = relp->right;
                    if(relp->right) relp->right->parent = relp->parent;
                }else {
                    //current node does not have a successor
                    if(relp->right) relp->right->parent = current;
                    current->right = relp->right;
                }
                delete relp;
            }
        }
        while(top != -1) {
            current = stack[top--];
            int status = isBalanced(current);
            if(status == -2) {
                //right > left
                status = isBalanced(current->right);
                if(status == -1 || status == 0) {
                    //RR inbalance
                    LRotate(current);
                }else if(status == 1) {
                    //RL inbalance
                    RRotate(current->right);
                    LRotate(current);
                }
            }else if(status == 2) {
                //left > right
                status = isBalanced(current->left);
                if(status == 1 || status == 0) {
                    //LL inbalance
                    RRotate(current);
                }else if(status == -1) {
                    //LR inbalance
                    LRotate(current->left);
                    RRotate(current);
                }
            }else {
                getDepth(current);
            }
        }
    }

    Node* find(long long key, Node* subroot) {
        Node* current = subroot;
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

    Node* find_Min_Cls(long long key) {
        if(!root) {
            return NULL;
        }
        Node* current = root;
        Node* cpar = 0, *succ = 0, *pred = 0;
        long long sa;
        long long pa;
        while(current) {
            if(current->data < key) {
                cpar = current;
                current = current->right;
            }else if(current->data > key) {
                cpar = current;
                current = current->left;
            }else {
                break;
            }
        }
        if(current) {
            return current;
        }else if(cpar->data > key) {
            succ = cpar;
            current = cpar;
            while(cpar) {
                if(cpar->right == current) {
                    pred = cpar;
                    break;
                }
                current = cpar;
                cpar = cpar->parent;
            }
        }else {
            pred = cpar;
            current = cpar;
            while(cpar) {
                if(cpar->left == current) {
                    succ = cpar;
                    break;
                }
                current = cpar;
                cpar = cpar->parent;
            }
        }
        if(succ) sa = _abs(succ->data - key);
        if(pred) pa = _abs(pred->data - key);
        if(succ && pred) {
            return pa <= sa? pred: succ;
        }else if(succ) {
            return succ;
        }else if(pred) {
            return pred;
        }else{
            return 0;
        }
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
        int lc = -1, rc = -1;
        if(subroot->left) {
            ld = subroot->left->depth;
            lc = subroot->left->nchild;
        }
        if(subroot->right) {
            rd = subroot->right->depth;
            rc = subroot->right->nchild;
        }
        subroot->depth = ((ld > rd)? ld: rd) + 1;
        subroot->nchild = lc + rc + 2;
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
};

int n;


int main(void) {
    scanf("%d", &n);
    AVLtree pets;
    AVLtree humans;
    int isHuman;
    long long feature;
    long long ans = 0;

    for(int i = 0; i < n; i++) {
        scanf("%d %lld", &isHuman, &feature);
        if(isHuman) {
            Node* temp = pets.find_Min_Cls(feature);
            if(!temp) {
                humans.insert(feature);
            }else {
                ans += _abs(temp->data - feature);
                pets.delete_Node(temp->data);
            }
        }else {
            Node* temp = humans.find_Min_Cls(feature);
            if(!temp) {
                pets.insert(feature);
            }else {
                ans += _abs(temp->data - feature);
                humans.delete_Node(temp->data);
            }
        }
    }
    printf("%lld\n", ans);
}