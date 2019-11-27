#define WHITE 0
#define YELLOW 1
#define RED 2
#include <vector>
#include <stdio.h>

using namespace std;
struct Node {
    int data;
    int color;
    bool isDefended;
    vector<Node*> naj;
    Node(int data, int color, bool isDefended) {
        this->data = data;
        this->color = color;
        this->isDefended = isDefended;
    }
};

Node* queue[200001];
int _front = 0, _end = 0;
Node* nodes[200001];
int T, n, m, u, v;
vector<Node*> ans;
int main() {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        _front = 0;
        _end = 0;
        ans.clear();
        scanf("%d %d", &n, &m);
        for(int j = 1; j <= n; j++) {
            nodes[j] = new Node(j, WHITE, false);
        }
        for(int j = 0; j < m; j++) {
            scanf("%d %d", &u, &v);
            nodes[u]->naj.push_back(nodes[v]);
            nodes[v]->naj.push_back(nodes[u]);
        }
        nodes[1]->color = YELLOW;
        queue[_end++] = nodes[1];
        Node *curr, *next;
        while(_front != _end) {
            curr = queue[_front++];
            if(curr->color == RED) continue;
            curr->color = RED;
            for(int a = 0; a < curr->naj.size(); a++) {
                next = curr->naj[a];
                if(next->color == WHITE) {
                    queue[_end++] = next;
                    next->color = YELLOW;
                }
                if(!next->isDefended) {
                    ans.push_back(next);
                    next->isDefended = 1;
                    for(int k = 0; k < next->naj.size(); k++) {
                        next->naj[k]->isDefended = 1;
                    } 
                }
            }
        }
        if(ans.size() <= n / 2) {
            printf("%d\n", ans.size());
            for(int x = 0; x < ans.size(); x++) {
                printf("%d ", ans[x]->data);
            }
            printf("\n");
        }else {
            printf("%d\n", n - ans.size());
            int counter = 0;
            Node* inv = ans[counter];
            for(int x = 1; x <= n; x++) {
                if(nodes[x] != inv) {
                    printf("%d ", nodes[x]->data);
                }else {
                    if(counter == ans.size() - 1) {
                        inv = 0;
                    }else {
                        inv = ans[++counter];
                    }
                }
            }
            printf("\n");
        }
        for(int x = 1; x <= n; x++) {
            delete nodes[x];
        }
    }
}
