#include <stdio.h>
#include <vector>

using namespace std;

enum COLOR{WHITE=1, YELLOW=2, RED=3};
class Vertex {
    public:
    int index;
    vector<Vertex*> aj;
    COLOR color;
    Vertex(int index):index(index) {
        color = WHITE;
    };
};

vector<Vertex*> LR;
Vertex* vertices[200001];
Vertex* stack[200001];
Vertex* L[200001];
int n, m, u, v;
Vertex *current, *_next;

int main(void) {
    int top_first = -1;
    scanf("%d %d", &n, &m);

    for(int i = 1; i <= n; i++) {
        vertices[i] = new Vertex(i);
    }

    for(int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        vertices[u]->aj.push_back(vertices[v]);
    }

    stack[++top_first] = vertices[1];
    vertices[1]->color = YELLOW;
    while(top_first != -1) {
        current = stack[top_first--];
        if(current->color == RED) continue;
        LR.push_back(current);
        current->color = RED;
        
        for(int j = 0; j < current->aj.size(); j++) {
            _next = current->aj[j];
            if(_next->color == WHITE) {
                stack[++top_first] = _next;
                _next->color = YELLOW;
            }
        }
    }
    //reverse
    // for(int i = 0; i < LR.size(); i++) {
    //     L[i] = LR[n - 1 - i];
    // }
    
    int cnt_sec = 0;
    int top_sec = -1;
    bool fail_flag = 0;
    int ele_cnt = 0; //count number of elements that have been poped out by stack
    stack[++top_sec] = LR[LR.size() - 1];
    LR[LR.size() - 1]->color = YELLOW;
    while(top_sec != -1) {
        current = stack[top_sec--];
        if(current->color == WHITE) continue;
        current->color = WHITE;
        ele_cnt++;

        for(int j = 0; j < current->aj.size(); j++) {
            _next = current->aj[j];
            if(_next->color == RED) {
                stack[++top_sec] = _next;
                _next->color = YELLOW;
            }
        }
    }
    if(ele_cnt != n) {
        printf("ovarB\n");
    }else {
        printf("Bravo\n");
    }
}