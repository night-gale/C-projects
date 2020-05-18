#include <stdio.h>
#include <algorithm>
#include <cmath>


struct Node {
    long long x;
    long long y;
};

const int k_size = 10;
const double pi = 3.14159265358979323846;
long long N, min_y_i, min_y, min_x;
Node* nodes[k_size], *e1, *e2;
Node* stack[k_size];
long long top, result, l1, l2;

bool cmp(Node* a, Node* b) {
    long long cp = (a->x - nodes[0]->x)*(b->y - nodes[0]->y) - (a->y - nodes[0]->y)*(b->x - nodes[0]->x);
    if(cp == 0) {
        return (a->y-nodes[0]->y)*(a->y-nodes[0]->y)+(a->x-nodes[0]->x)*(a->x-nodes[0]->x) > 
               (b->y-nodes[0]->y)*(b->y-nodes[0]->y)+(b->x-nodes[0]->x)*(b->x-nodes[0]->x);
    }else {
        return cp > 0;
    }
}

long long cp(Node *a, Node *b) {
    return (a->x - nodes[0]->x)*(b->y - nodes[0]->y) - (a->y - nodes[0]->y)*(b->x - nodes[0]->x);
}

long long leqn(Node *a, Node *b, Node *c) {
    return (b->x-a->x)*(c->y-b->y)-(c->x-b->x)*(b->y-a->y);
}

int main(void) {
    scanf("%d", &N);
    min_y_i = -1;
    min_y = 1e9 + 1;
    top = -1;
    result = 0;

    for(int i = 0; i < N; i++) {
        nodes[i] = new Node();
        scanf("%lld%lld", &nodes[i]->x, &nodes[i]->y);
        if(min_y > nodes[i]->y) {
            min_y = nodes[i]->y;
            min_y_i = i;
        }
    }
    Node *temp = nodes[min_y_i];
    nodes[min_y_i] = nodes[0];
    nodes[0] = temp;

    std::sort(nodes+1, nodes+N, cmp);

    stack[++top] = nodes[0];
    // stack[++top] = nodes[1];
    // stack[++top] = nodes[2];
    for(int i = 1; i < N; i++) {
        if(i != 1 && cp(nodes[i], nodes[i-1])==0) continue;
        if(top < 2) stack[++top] = nodes[i];
        else {
            while(top >= 2) {
                e1 = stack[top];
                e2 = stack[top-1];
                // double a = leqn(e2, nodes[i], e1);
                // double b = leqn(e2, nodes[i], nodes[top-2]);
                if(leqn(e2, e1, nodes[i]) > 0) {
                    stack[++top] = nodes[i];
                    break;
                }else {
                    top--;
                }
            }
            if(top < 2) stack[++top] = nodes[i];
        }       
    }

    result = top + 1;

    for(int i = 1; i < N; i++) {
        if((nodes[i] != stack[1]) && cp(nodes[i], stack[1]) == 0) {
            result++;
        }
        
        if((nodes[i] != stack[top]) && cp(nodes[i], stack[top]) == 0) {
            result++;
        }
    }

    printf("%d", result);
}