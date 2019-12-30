#include <stdio.h>
#include <vector>

enum COLOR{WHTIE=0, YELLOW=1, RED=2};
class Node {
    public:
    int index;
    long long dist;
    COLOR color;
    std::vector<Node*> aj;
    Node(int index, long long dist = (long long)1e16) {
        this->index = index;
        this->dist = dist;
        color = WHTIE;
    }
};

Node* nodes[1001];
long long edges[1001][1001];
long long n, m, u, v, w;
int s, t;
int main(void) {
    Node* next;
    scanf("%lld %lld", &n, &m);

    for(int i = 1; i <= n; i++) {
        nodes[i] = new Node(i);
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            edges[i][j] = __INT32_MAX__;
        }
    }

    for(int i = 0; i < m; i++) {
        scanf("%lld %lld %lld", &u, &v, &w);
        edges[u][v] = std::min(w, edges[u][v]);
        nodes[u]->aj.push_back(nodes[v]);
        edges[v][u] = std::min(w, edges[v][u]);
        nodes[v]->aj.push_back(nodes[u]);
    }
    
    scanf("%d %d", &s, &t);
    nodes[s]->dist = 0;
    while(true) {
        long long _min = (long long) 1e16;
        int min_index = -1;
        for(int i = 1; i <= n; i++) {
            if(nodes[i]->color == WHTIE) {
                if(_min > nodes[i]->dist) {
                    _min = nodes[i]->dist;
                    min_index = i;
                }
            }
        }
        if(min_index == -1) break;

        for(int j = 0; j < nodes[min_index]->aj.size(); j++) {
            next = nodes[min_index]->aj[j];
            next->dist = std::min(nodes[min_index]->dist + edges[min_index][next->index], next->dist);
        }
        nodes[min_index]->color = YELLOW;
    }
    if(nodes[t]->dist != (long long) 1e16) {
        printf("%lld\n", nodes[t]->dist);
    }else {
        printf("%d\n", -1);
    }
}