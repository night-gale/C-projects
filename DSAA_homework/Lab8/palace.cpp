#include <stdio.h>
#include <vector>
using namespace std; 

enum COLOR{WHITE=0, YELLOW=1, RED=2};
class Node {
    public:
    int a;
    int b;
    int c;
    int sum;
    vector<Node*> aj;
    COLOR color;
    int in_degree;
    Node(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->sum = 0;
        color = WHITE;
        in_degree = 0;
    }
};

Node *nodes[2001], *current, *_next;
int T, n, a, b, c;
Node *queue[2001];
int main(void) {
    scanf("%d", &T);

    for(int t = 0; t < T; t++) {
        int _max = 0;
        int fr = 0, ed = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            nodes[i] = 0;
        }
        for(int i = 0; i < n; i++) {
            scanf("%d %d %d", &a, &b, &c);
            nodes[i] = new Node(a, b, c);
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(nodes[j] && ((nodes[j]->a > nodes[i]->a && nodes[j]->b > nodes[i]->b) 
                                || (nodes[j]->a > nodes[i]->b && nodes[j]->b > nodes[i]->a))) {
                    nodes[j]->aj.push_back(nodes[i]);
                    nodes[i]->in_degree++;
                }
            }
        }

        for(int i = 0; i < n; i++) {
            if(!nodes[i]->in_degree) {
                queue[ed++] = nodes[i];
                nodes[i]->color = YELLOW;
                nodes[i]->sum = nodes[i]->c;
                _max = _max > nodes[i]->sum? _max: nodes[i]->sum;
            }
        }
        while(fr != ed) {
            current = queue[fr++];
            if(current->color == RED) continue;
            current->color = RED;
            for(int j = 0; j < current->aj.size(); j++) {
                _next = current->aj[j];
                _next->in_degree--;
                _next->sum = std::max(current->sum + _next->c, _next->sum);
                _max = _max > _next->sum? _max: _next->sum;
                if(_next->in_degree == 0 && _next->color == WHITE) {
                    queue[ed++] = _next;
                    _next->color = YELLOW;
                }
            } 
        }
        printf("%d\n", _max);
    }
}