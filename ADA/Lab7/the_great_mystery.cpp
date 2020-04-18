#include <stdio.h>
#include <algorithm>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

const int k_SIZE = 1001;
int us[2][k_SIZE*k_SIZE];
Edge edges[k_SIZE*(k_SIZE-1)*2+1];
int vert[k_SIZE*k_SIZE];
int n, m, w, top, s, size, u, v;
long long result;
Edge cur;
void make_set(int size) {
    for(int i; i < size; i++) {
        us[0][i] = i; // root of the tree
        us[1][i] = 1; // size of the tree
    }
};

void unionU(int a, int b) {
    if(us[1][u] > us[1][v]) {
        us[0][u] = v;
        us[1][v] += us[1][u];
    }else {
        us[0][v] = u;
        us[1][u] += us[1][v];
    }
}

int find(int tar) {
    int par = tar;
    int temp;
    while(us[0][par] != par) {
        par = us[0][par];
    }
    while(tar != par) {
        temp = us[0][tar];  // temp equals to parent of target
        us[0][tar] = us[0][par];
        tar = temp;  // set tartget to parent
    }
    return par;
}

bool cmp(Edge a, Edge b) {
    return a.w > b.w;
}

int main(void) {
    top = -1;
    scanf("%d %d", &n, &m);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &vert[i * m + j]);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            s = i * m + j;
            if(j != m - 1) {
                top++;
                edges[top].u = s;
                edges[top].v = s + 1;
                edges[top].w = vert[s] ^ vert[s+1];
            }if(i != n - 1) {
                top++;
                edges[top].u = s;
                edges[top].v = s + m;
                edges[top].w = vert[s] ^ vert[s+m];
            }
        }
    }
    size = (n-1)*m + n*(m-1);
    make_heap(edges, edges+size, cmp);
    make_set(n * m);
    while(size != 0) {
        cur = edges[0];
        pop_heap(edges, edges+size, cmp);
        size--;
        u = find(cur.u);
        v = find(cur.v);
        if(u != v) {
            unionU(u, v);
            result += cur.w;
        }
    }
    printf("%lld", result);
}