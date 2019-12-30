#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;

enum COLOR {WHITE=0, YELLOW=1, RED=2};
class Vertex {
    public:
    int index;
    vector<Vertex*> aj;
    vector<Vertex*> in_vertices;
    int type;
    COLOR color;

    Vertex(int index): index(index) {
        color = WHITE;
    }
};

long long X[1001], Y[1001], r[1001], t[1001];
int n, type_cnt;
Vertex *vertices[1001];
Vertex *stack[1001];
Vertex *current, *_next;
vector<Vertex*> LR;
Vertex *list[1001];
vector<vector<Vertex*>*> SCCs;
int in_degrees[1001];

int main(void) {
    int top = -1;
    // int top_sec = -1;
    type_cnt = 0;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        scanf("%lld %lld %lld %lld", &X[i], &Y[i], &r[i], &t[i]);
        vertices[i] = new Vertex(i);
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i == j) continue;
            double dist = sqrtl((X[i]-X[j]) * (X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]));
            if(dist <= r[i]) {
                vertices[i]->aj.push_back(vertices[j]);
                vertices[j]->in_vertices.push_back(vertices[i]);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(vertices[i]->color == WHITE) {
            stack[++top] = vertices[i];
            vertices[i]->color = YELLOW;

            while(top != -1) {
                current = stack[top];
                if(current->color == RED) {
                    top--;
                    LR.push_back(current);
                    continue;
                }

                for(int j = 0; j < current->in_vertices.size(); j++) {
                    _next = current->in_vertices[j];
                    if(_next->color == WHITE) {
                        stack[++top] = _next;
                        _next->color = YELLOW;
                    }
                }
                current->color = RED;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        list[i] = LR[n - 1 - i];
    }

    top = -1;
    for(int i = 0; i < n; i++) {
        if(list[i]->color == RED) {
            stack[++top] = list[i];
            list[i]->color = YELLOW;
            vector<Vertex*>* scc = new vector<Vertex*>();

            while(top != -1) {
                current = stack[top--];
                if(current->color == WHITE) continue;
                current->color = WHITE;
                current->type = type_cnt;
                scc->push_back(current);

                for(int j = 0; j < current->aj.size(); j++) {
                    _next = current->aj[j];
                    if(_next->color == RED) {
                        stack[++top] = _next;
                        _next->color = YELLOW;
                    }
                }
            }
            type_cnt++;
            SCCs.push_back(scc);
        }
    }

    for(int i = 0; i < type_cnt; i++) {
        in_degrees[i] = 0;
    }

    for(int i = 0; i < SCCs.size(); i++) {
        for(int j = 0; j < SCCs[i]->size(); j++) {
            current = (*(SCCs[i]))[j];
            for(int k = 0; k < current->aj.size(); k++) {
                _next = current->aj[k];
                if(current->type != _next->type) {
                    in_degrees[_next->type]++;
                }
            }
        }
    }

    long long cost = 0;
    for(int i = 0; i < type_cnt; i++) {
        if(in_degrees[i] == 0) {
            long long min_t = __INT64_MAX__;
            for(int j = 0; j < SCCs[i]->size(); j++) {
                min_t = std::min(min_t, t[(*(SCCs[i]))[j]->index]);
            }
            cost += min_t;
        }
    }

    printf("%lld", cost);
}