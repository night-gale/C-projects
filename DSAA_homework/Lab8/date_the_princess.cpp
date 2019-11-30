#include <stdio.h>
#include <vector>
#include <math.h>
enum COLOR{
    WHITE=1,
    YELLOW=2,
    RED=3    
};

class Node{
    public:
    std::vector<Node*> aj;
    COLOR color;
    int distance;
    Node(COLOR color) {
        this->color = color;
        distance = __INT32_MAX__;
    }
};

Node* nodes[1000001];
int n, m, u, v, w, cnt, ft, ed;
Node* queue[1000001], *curr, *next;
int main(void) {
    scanf("%d %d", &n, &m);
    cnt = n;
    ft = 0, ed = 0;
    for(int i = 1; i <= n; i++) {
        nodes[i] = new Node(WHITE);
    }
    //construct adjacent list
    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        if(w == 1) {
            nodes[u]->aj.push_back(nodes[v]);
        }else {
            //split two nodes with road bewteen them 2 into three nodes
            nodes[++cnt] = new Node(WHITE);
            nodes[u]->aj.push_back(nodes[cnt]);
            nodes[cnt]->aj.push_back(nodes[v]);
        }
    }

    queue[ed++] = nodes[1];
    nodes[1]->distance = 0;
    nodes[1]->color = YELLOW;
    while(ed != ft) {
        curr = queue[ft++];
        if(curr->color == RED) continue;
        curr->color = RED;
        for(int j = 0; j < curr->aj.size(); j++) {
            next = curr->aj[j];
            if(next->color == WHITE) {
                queue[ed++] = next;
                next->color = YELLOW;
                next->distance =  curr->distance + 1;
            }
        }
    }
    if(nodes[n]->color != RED) {
        printf("%d\n", -1);
    }else {
        printf("%d\n", nodes[n]->distance);
    }
}