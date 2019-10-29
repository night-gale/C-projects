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
    ~Node() {
        Node* temp;
        while(!childs.empty()) {
            temp = childs.back();
            if(temp != NULL)
                delete temp;
            childs.pop_back();
        }
    }
};
void find_depth(Node*, int depth);
int T, N, a, b;

int main(void) {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        scanf("%d", &N);
        Node *ref[100001] = {0};
        bool isChecked[100001] = {0};
        int depth[100001] = {0};
        for(int j = 0; j < N; j++) {
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

    }
}

void find_depth(int node, int depth, bool* isChecked) {
    if(isChecked[node]) {
        
    }
}