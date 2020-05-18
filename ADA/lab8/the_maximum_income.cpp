#include <stdio.h>
#include <algorithm>

using namespace std;

struct Node {
    int s;
    int t;
    int w;
};

const int SIZE = 5000;
Node* tasks[SIZE + 1];
int n;
int ats[SIZE + 1];
int spot[SIZE + 1];
int top, x;
long long income;

bool cmp1(Node* a, Node* b) {
    return a->s < b->s;
}

bool cmp2(Node* a, Node* b) {
    return a->w > b->w;
}

bool insert(int i, int xp) {
    if(ats[xp] > tasks[i]->t) {
        return false;
    }
    if(spot[xp] == -1) {
        spot[xp] = i;
        return true;
    }
    int j = spot[xp];
    if(tasks[i]->t > tasks[j]->t) {
        return insert(i, xp+1);
    }else {
        if(insert(j, xp+1)) {
            spot[xp] = i;
            return true;
        }
        return false;
    }
}

int main(void) {
    scanf("%d", &n);
    top = 0;
    income = 0;
    for(int i = 0; i < n; i++) {
        tasks[i] = new Node();
        scanf("%d%d%d", &tasks[i]->s, &tasks[i]->t, &tasks[i]->w);
    }

    sort(tasks, tasks + n, cmp1);
    x = 0;
    for(int i = 0; i < n; i++) {
        x = (x+1) > tasks[i]->s? (x+1): tasks[i]->s;
        spot[top] = -1;
        ats[top++] = x; // active time slot
    }

    sort(tasks, tasks + n, cmp2);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(ats[j] >= tasks[i]->s) {
                x = j;
                break;
            }
        }
        insert(i, x);
    }

    for(int i = 0; i < n; i++) {
        if(spot[i] != -1) {
            income += tasks[spot[i]]->w;
        }
    }

    printf("%lld\n", income);
}