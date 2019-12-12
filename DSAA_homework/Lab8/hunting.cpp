#include <stdio.h>
#include <vector>

using namespace std;

enum COLOR{WHITE=0, YELLOW=1, RED=2};
class Node {
    public:
    int index;
    vector<Node*> out;
    vector<Node*> in;
    long long sum;
    COLOR color;
    int in_degree;
    Node(int index) {
        this->index = index;
        in_degree = 0;
        sum = 0;
        this->color = WHITE;
    }
};

long long modulo(long long a) {
    if(a >= ((long long)1e9) + 7) {
        a %= ((long long)1e9) + 7;
    }
    return a;
}

Node *nodes[100001];
Node *queue[100001];
Node *topolist[100001];
int T, n, m, u, v;
long long a[100001], b[100001];
int main(void) {
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        int fr = 0, ed = 0, cnt = 0;
        Node *current, *_next, *prev;
        long long sum = 0;
        scanf("%d %d", &n, &m);
        
        for(int j = 1; j <= n; j++) {
            scanf("%lld %lld", &a[j], &b[j]);
            nodes[j] = new Node(j);
        }

        for(int j = 0; j < m; j++) {
            scanf("%d %d", &u, &v);
            nodes[u]->out.push_back(nodes[v]);
            nodes[v]->in.push_back(nodes[u]);
            nodes[v]->in_degree++; 
        }

        for(int j = 1; j <= n; j++) {
            if(!nodes[j]->in_degree) {
                queue[ed++] = nodes[j];
                nodes[j]->color = YELLOW;
            }
        }

        while(fr != ed) {
            current = queue[fr++];
            if(current->color == RED) continue;
            current->color = RED;
            topolist[cnt++] = current;
            for(int j = 0; j < current->out.size(); j++) {
                _next = current->out[j];
                _next->in_degree--;
                if((!_next->in_degree) && (_next->color == WHITE)) {
                    queue[ed++] = _next;
                    _next->color = YELLOW;
                }
            }
        }

        for(int j = 0; j < cnt; j++) {
            current = topolist[j];
            for(int k = 0; k < current->in.size(); k++) {
                prev = current->in[k];
                current->sum = modulo(modulo(current->sum + prev->sum) + modulo(a[prev->index]));
            }
            sum = modulo(modulo(modulo(current->sum) * modulo(b[current->index])) + sum);
        }
        printf("%lld\n", modulo(sum));

        for(int j = 1; j <= n; j++) {
            delete nodes[j];
        }
    }
}