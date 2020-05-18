#include <stdio.h>
#include <algorithm>
#include <vector>

inline long long square(long long x) {
    return x * x;
}

struct Node {
    int coor[3];
    int bds[2][3];
    int l, r;
};

const int ksize = 2e5+1;
Node nodes[ksize];
// Node sorted[3][ksize];
int N, dim; 
bool zero_flag;
Node* output[2];
// int top;
long long adis;

int cmp1(Node &a, Node &b) {
    return a.coor[0] < b.coor[0];
}

int cmp2(Node &a, Node &b) {
    return a.coor[1] < b.coor[1];
}

int cmp3(Node &a, Node &b) {
    return a.coor[2] < b.coor[2];
}

int construct(int left, int right, int axis) {
    int mid = (left + right) / 2;
    int new_axis = (axis + 1)%dim;
    bool c1 = (left != mid);
    bool c2 = (right != mid);
    if(axis == 0) {
        std::nth_element(nodes+left, nodes+mid, nodes+right+1, cmp1);
    }else if(axis == 1) {
        std::nth_element(nodes+left, nodes+mid, nodes+right+1, cmp2);
    }else {
        std::nth_element(nodes+left, nodes+mid, nodes+right+1, cmp3);
    }
    if(c1) {
        //update left child
        nodes[mid].l = construct(left, mid-1, new_axis);
    }
    if(c2) {
        //update right child
        nodes[mid].r = construct(mid+1, right, new_axis);
    }
    left = nodes[mid].l;
    right = nodes[mid].r;
    for(int i = 0; i < dim; i++) {
        nodes[mid].bds[0][i] = nodes[mid].coor[i];
        nodes[mid].bds[1][i] = nodes[mid].coor[i];
        bool c3 = left != 0;
        bool c4 = right != 0;
        //update bounds
        if(c3) nodes[mid].bds[0][i] = std::min(nodes[mid].bds[0][i], 
                                                    nodes[left].bds[0][i]);
        if(c4) nodes[mid].bds[0][i] = std::min(nodes[mid].bds[0][i], 
                                                    nodes[right].bds[0][i]);  
        if(c3) nodes[mid].bds[1][i] = std::max(nodes[mid].bds[1][i], 
                                                    nodes[left].bds[1][i]);
        if(c4) nodes[mid].bds[1][i] = std::max(nodes[mid].bds[1][i], 
                                                    nodes[right].bds[1][i]);
    }
    return mid;
}

long long euc(Node &a, Node &b) {
    // euclidean distance
    long long result = 0;
    for(int i = 0; i < dim; i++) {
        result += square(a.coor[i]-b.coor[i]);
    }
    return result;
}

long long distance(Node &tar, Node &box) {
    //calculate the distance betwween target and the box represented by the tree rooted at box
    long long result = 0;
    for(int i = 0; i < dim; i++) {
        bool c1 = box.bds[0][i] > tar.coor[i];
        bool c2 = box.bds[1][i] < tar.coor[i];
        result += (c1)?square(tar.coor[i] - box.bds[0][i]):0;
        result += (c2)?square(tar.coor[i] - box.bds[1][i]):0;
    }
    return result;
}

void nearest(Node &t, Node &root) {
    long long dis = euc(t, root);

    if(!dis) {
        if(zero_flag) {
            output[0] = &t;
            output[1] = &root;
            adis = 0;
        }
        zero_flag = 1;
    }else if(dis < adis) {
        output[0] = &t;
        output[1] = &root;
        adis = dis;
    }

    bool c1 = distance(t, nodes[root.l]) < adis;
    bool c2 = distance(t, nodes[root.r]) < adis;
    if(c1) {
        nearest(t, nodes[root.l]);
    }
    if(c2) {
        nearest(t, nodes[root.r]);
    }
}


int main(void) {
    // zero_cnt = 0;
    // top = -1;
    adis = 0x7fffffffffffffff;

    scanf("%d%d", &N, &dim);
    for(int i = 1; i <= N; i++) {
        for(int j = 0; j < dim; j++) {
            scanf("%d", &nodes[i].coor[j]);
        }
    }
    
    int root = construct(1, N, 0);
    for(int i = 1; i <= N; i++) {
        zero_flag = false;
        nearest(nodes[i], nodes[root]);
    }
    for(int i = 0; i < dim; i++) {
        if(output[0]->coor[i] > output[1]->coor[i]) {
            Node* temp = output[0];
            output[0] = output[1];
            output[1] = temp;
            break;
        }else if(output[0]->coor[i] < output[1]->coor[i])break;
    }
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < dim-1; j++) {
            printf("%d ", output[i]->coor[j]);
        }
        printf("%d\n", output[i]->coor[dim-1]);
    }
}