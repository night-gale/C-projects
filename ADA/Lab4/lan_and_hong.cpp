#include <stdio.h>

const int SIZE = 8;
int n;
char a[SIZE + 1][SIZE + 1];
int dfs(int cx, int cy, bool* map, int accessed);
int countAvailable(int cx, int cy, const bool* map, int accessed);
bool checkConnectivity(int cx1, int cy1, int cx2, int cy2, bool* map);
int bp;
int addend[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
int order[4];
// int available_spot[4];
// bool is_spot_Available[4];

int main(void) {
    scanf("%d", &n);
    bp = 0; // count number of unreachable vertice
    for(int i = 0; i < n; i++) {
        scanf("%s", &a[i]);
    }

    bool* map = new bool[64+1];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[i][j] == '.'){
                map[i*n+j] = 0;
            }else {
                map[i*n+j] = 1;
                bp++;
            }
        }
    }
    int result = dfs(0, 0, map, bp);
    printf("%d", result);
}

int dfs(int cx, int cy, bool* map, int accessed) {
    accessed++;
    if(accessed == n * n - 1) {
        return 1;
    }

    int count = 0;
    // bool* a = new bool[64+1];
    map[cx*n+cy] = 1;
    int* available_spot = new int[4];
    int top = -1;

    
    for(int i = 0; i < 4; i++) {
        available_spot[i] = countAvailable(cx+addend[i][0], cy+addend[i][1], map, accessed);
        if(available_spot[i] == 1 && top == -1) {
            int tmp = order[0];
            order[++top] = i;
        }else if(available_spot[i] == 1 && top != -1) {
            map[cx*n+cy] = 0;
            return 0;
        }
    }

    if(top == -1) {
        for(int i = 0; i < 4; i++) {
            if(available_spot[i] > 0) {
                count += dfs(cx + addend[i][0], cy + addend[i][1], map, accessed);
            }
        }
    }else if (top != -1) {
        int idx = order[top--];
        count += dfs(cx+addend[idx][0], cy+addend[idx][1], map, accessed);
        // map[cx*n+cy] = 0;
        // return dfs(cx+addend[idx][0], cy+addend[idx][1], map, accessed);
    }
    // delete [] a;
    delete [] available_spot;
    map[cx*n+cy] = 0;
    return count;
}

int countAvailable(int cx, int cy, const bool* map, int accessed) {
    if(cx == n-1 && cy == 0) {
        return 0;
    }
    if(cx < 0 || cy < 0 || cx > n-1 || cy > n-1 || map[(cx)*n+cy]) {
        return 0;
    }
    int count = 0;
    if(cx > 0 && !map[(cx-1)*n+cy]) {
        count++;
    }
    if(cx < n - 1 && !map[(cx+1)*n+cy]) {
        count++;
    }
    if(cy > 0 && !map[(cx)*n+cy-1]) {
        count++;
    }
    if(cy < n - 1 && !map[(cx)*n+cy+1]) {
        count++;
    }
    return count;
}
