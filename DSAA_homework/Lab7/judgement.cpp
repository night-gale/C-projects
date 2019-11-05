#include <stdio.h>

class Node {
    public:
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Node() {
        left = 0;
        right = 0;
        parent = 0;
        data = 0;
    }
};

int T, n;
Node* nodes[100001];
Node* queue[100002];

int main(void) {
    scanf("%d", &T);

    for(int c = 0; c < T; c++) {
        scanf("%d", &n);
        int parent, child;
        int front = 1, end = 1;
        bool failed = 0;
        bool flag = 0;
        int max = -1;
        Node* root, *l, *r, *p;

        for(int i = 1; i <= n; i++) {
            nodes[i] = new Node();
            scanf("%d", &nodes[i]->data);
        }

        for(int i = 1; i < n; i++) {
            scanf("%d %d", &parent, &child);
            nodes[child]->parent = nodes[parent];
            if(!nodes[parent]->left) {
                nodes[parent]->left = nodes[child];
            }else if(!nodes[parent]->right) {
                nodes[parent]->right = nodes[child];
            }else {
                failed = true;
            }
        }
        
        root = nodes[1];
        while(root->parent) {
            root = root->parent;
        }

        //min or max binary heap

        queue[end++] = root;
        while(front != end && !failed) {
            p = queue[front++];
            l = p->left;
            r = p->right;

            if(l) {
                if(max == -1) {
                    max = l->data == p->data? -1: l->data < p->data;
                }else {
                    if(max == 1) {
                        if(l->data > p->data) {
                            failed = 1;
                        }
                    }else {
                        if(l->data < p->data) {
                            failed = 1;
                        }
                    }
                }
                queue[end++] = l;
                if(flag) break;
            }else flag = 1;
            if(r) {
                if(max == -1) {
                    max = r->data == p->data? -1: r->data < p->data;
                }else {
                    if(max == 1) {
                        if(r->data > p->data) {
                            failed = 1;
                        }
                    }else {
                        if(r->data < p->data) {
                            failed = 1;
                        }
                    }
                }
                queue[end++] = r;
                if(flag) break;
            }else flag = 1;
        }

        printf("Case #%d: ", c + 1);
        if(failed || (front != end && flag)) {
            printf("NO\n");
        }else {
            printf("YES\n");
        }
    }
}