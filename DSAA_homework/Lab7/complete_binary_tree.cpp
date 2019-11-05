#include <stdio.h>

class Node {
    public:
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
    }
};

int T, n;
Node* nodes[150001];
bool appeared[150001];
int queue[150001];

int main(void) {
    scanf("%d", &T);

    for(int p = 0; p < T; p++) {
        scanf("%d", &n);
        int left, right;
        int counter = 0;
        int front = 1;
        int end = 1;
        Node* root;

        for(int i = 1; i <= n; i++) {
            nodes[i] = new Node(i);
            queue[i] = 0;
            appeared[i] = 0;
        }

        for(int i = 1; i <= n; i++) {
            scanf("%d %d", &left, &right);
            nodes[i]->left = nodes[left];
            nodes[i]->right = nodes[right];
            appeared[left] = 1; appeared[right] = 1;
        }

        for(int i = 1; i <= n; i++) {
            if(appeared[i] == 0) {
                root = nodes[i];
                break;
            }
        }

        queue[end++] = root->data;
        Node* l, * r;
        bool flag = 0;
        while(front != end) {
            l = nodes[queue[front]]->left;
            r = nodes[queue[front++]]->right;

            if(l) {
                queue[end++] = l->data;
                if(flag == 1) {
                    break;
                }
            }else flag = 1;
            if(r) {
                queue[end++] = r->data;
                if(flag == 1) {
                    break;
                }
            }else flag = 1;
        }

        if(flag && front != end) {
            printf("No\n");
        }else printf("Yes\n");
    }
}