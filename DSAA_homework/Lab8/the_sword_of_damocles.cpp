#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;
enum COLOR {
    WHITE = 0,
    YELLOW = 1,
    RED = 2
};

struct Node {
    long long x;
    long long y;
    long long s;
    COLOR color;
    std::vector<Node*> aj;
    Node(long long x, long long y, long long s, COLOR color) {
        this->x = x;
        this->y = y;
        this->s = s;
        this->color = color;
    }
};
long long T, n, m, k, x, y, s;
std::vector<Node*> nodes;
Node* queue[1010];

int main(void) {
    scanf("%lld", &T);
    
    for(int i = 0; i < T; i++) {
        scanf("%lld %lld %lld", &n, &m, &k);
        Node* begin = new Node(0, 0, 0, WHITE);
        Node* end = new Node(n, m, 0, WHITE);
        int qf = 0, qe = 0;

        //graph construction
        for(int j = 0; j < k; j++) {
            scanf("%lld %lld %lld", &x, &y, &s);
            Node* temp = new Node(x, y, s, WHITE);
            
            if(n - x <= s || y <= s) {
                begin->aj.push_back(temp);
                temp->aj.push_back(begin);
            }
            if(x <= s || m - y <= s) {
                end->aj.push_back(temp);
                temp->aj.push_back(end);
            }
            for(int kc = 0; kc < nodes.size(); kc++) {
                Node* inter = nodes[kc];
                long long dx = abs(x - inter->x);
                long long dy = abs(y - inter->y);
                if(sqrtl(dx * dx + dy * dy) <= (s + inter->s)) {
                    inter->aj.push_back(temp);
                    temp->aj.push_back(inter);
                }
            }
            nodes.push_back(temp);
        }

        queue[qe++] = begin;
        begin->color = YELLOW;
        while(qf != qe) {
            Node* curr = queue[qf++];
            if(curr->color == RED) continue;
            curr->color = RED;
            for(int kc = 0; kc < curr->aj.size(); kc++) {
                Node* temp = curr->aj[kc];
                if(temp->color == WHITE) {
                    queue[qe++] = temp;
                    temp->color = YELLOW;
                }
            }
        }
        if(end->color != WHITE) {
            printf("No\n");
        }else {
            printf("Yes\n");
        }
        delete begin;
        delete end;
        for(int j = 0; j < nodes.size(); j++) {
            delete nodes[j];
        }
        nodes.clear();
    }
}