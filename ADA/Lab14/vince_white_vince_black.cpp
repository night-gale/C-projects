#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int index;
    vector<Node*> i;
    vector<Node*> o;
    bool visited;
};

const int k_size = 1005;
int n, m, tmp, u, v;
int s, t;
Node nodes[k_size], *tn, *ta, nr[k_size];
int flow[k_size][k_size], fr[k_size][k_size];
int cost[k_size][k_size], cr[k_size][k_size];
vector<Node*> A;
vector<Node*> B;
int path[k_size];
queue<Node*> stack;
int result;

bool BFS() {
    for(int i = 0; i <= n+1; i++) {
        path[i] = -1;
        nr[i].visited = false;
    }

    stack.push(&nr[s]);
    while(!stack.empty()) {
        tn = stack.front();
        stack.pop();
        if(tn->visited == true) continue;
        tn->visited = true;
        for(int i = 0; i < tn->o.size(); ++i) {
            ta = tn->o[i];
            if((!nr[ta->index].visited) && (cr[tn->index][ta->index] > 0)) {
                stack.push(ta);
                path[ta->index] = tn->index;
                // if(ta->index == t) return true;
            }
        }
    }
    return (path[t]!=-1);
}

int minCutMaxFlow() {
    int root;
    int bottleneck;
    int maxflow = 0;
    while(BFS()) {
        root = t;
        bottleneck = __INT32_MAX__;
        while(root != s) {
            if(bottleneck > cr[path[root]][root]) {
                bottleneck = cr[path[root]][root];
            }
            root = path[root];
        }
        root = t;
        // update flow
        while(root != s) {
            cr[path[root]][root] -= bottleneck;
            cr[root][path[root]] += bottleneck;
            root = path[root];
        }
        maxflow += bottleneck;
    }
    return maxflow;
}

int main(void) {
    scanf("%d%d", &n, &m);
    s = 0;
    nodes[s].index = s;
    nr[s].index = s;
    t = n + 1;
    nodes[t].index = t;
    nr[t].index = t;
    result = 0;
    for(int i = 1; i <= n; ++i) {
        nodes[i].index = i;
        nr[i].index = i;
        scanf("%d", &tmp);
        if(tmp) {
            cost[s][i] = 1;
            cr[s][i] = 1;
            nodes[s].o.push_back(&nodes[i]);
            nodes[i].i.push_back(&nodes[s]);
            nr[s].o.push_back(&nr[i]);
            nr[i].o.push_back(&nr[s]);
            nr[s].i.push_back(&nr[i]);
            nr[i].i.push_back(&nr[s]);
        }else {
            cost[i][t] = 1;
            cr[i][t] = 1;
            nodes[i].o.push_back(&nodes[t]);
            nodes[t].i.push_back(&nodes[i]);
            nr[t].o.push_back(&nr[i]);
            nr[i].o.push_back(&nr[t]);
            nr[t].i.push_back(&nr[i]);
            nr[i].i.push_back(&nr[t]);
        }
    }

    for(int i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        cost[u][v] = 1;
        cr[u][v] = 1;
        cost[v][u] = 1;
        cr[v][u] = 1;
        nodes[u].o.push_back(&nodes[v]);
        nodes[v].i.push_back(&nodes[u]);
        nr[u].o.push_back(&nr[v]);
        nr[v].o.push_back(&nr[u]);
        nr[u].i.push_back(&nr[v]);
        nr[v].i.push_back(&nr[u]);
    }

    result = minCutMaxFlow();
    printf("%d\n", result);
}
