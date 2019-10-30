#include <stdio.h>
#include <vector>
using namespace std;

class Node {
    public:
    vector<Node*> childs;
    int data;
    Node(int _data) {
        data = _data;
    }
};

void find_depth(Node* node, int depth);
int T, N, a, b;
bool isChecked[100002];
int depths[100002];
Node *ref[100002];

int main(void) {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        scanf("%d", &N);

        //initialization
        for(int j = 1; j <= N; j++) {
            isChecked[j] = 0;
            depths[j] = 0;
            ref[j] = 0;
        }

        for(int j = 0; j < N - 1; j++) {
            scanf("%d %d", &a, &b);
            if(ref[a] == 0) {
                ref[a] = new Node(a);
            }
            if(ref[b] == 0) {
                ref[b] = new Node(b);
            }
            ref[a]->childs.push_back(ref[b]);
            ref[b]->childs.push_back(ref[a]);
        }

        if(ref[1] == 0) {
            ref[1] = new Node(1);
        }

        find_depth(ref[1], 0);

        //not deleted
        for(int j = 1; j <= N; j++) {
            printf("%d ", depths[j]);
            delete ref[j];
        }
        printf("\n");
    }
}

void find_depth(Node* node, int depth) {
    if(isChecked[node->data]) {
        return;
    }

    depths[node->data] = depth;
    isChecked[node->data] = 1;
    for(int i = 0; i < node->childs.size(); i++) {
        if(!isChecked[node->childs[i]->data]) {
            find_depth(node->childs[i], depth + 1);
        }
    }
}