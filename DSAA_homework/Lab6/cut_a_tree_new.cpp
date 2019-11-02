#include <stdio.h>
#include <vector>
#define WHITE 0
#define RED 1
#define BLUE 2

using namespace std;

class Node {
    public:
    vector<Node*> childs;
    Node* father;
    int data;
    int color;
    int red;
    int blue;
    Node(int _data) {
        data = _data;
        father = 0;
        color = 0;
        red = 0;
        blue = 0;
    }
};

int T, N;
Node* ref[100002];
bool isChecked[100002];
void find_father(Node* root);
int edgeCounter(Node* root);
int red_counter, blue_counter;

int main(void) {
    scanf("%d", &T);

    for(int p = 0; p < T; p++) {
        scanf("%d", &N);
        int a, b;
        red_counter = 0;
        blue_counter = 0;

        for(int i = 1; i <= N; i++) {
            ref[i] = new Node(i);
            isChecked[i] = 0;
        }
        for(int i = 0; i < N - 1; i++) {
            scanf("%d %d", &a, &b);

            ref[a]->childs.push_back(ref[b]);
            ref[b]->childs.push_back(ref[a]);
        }

        for(int i = 0; i < N; i++) {
            scanf("%d", &(ref[i + 1]->color));
            if(ref[i+1]->color == RED) {
                red_counter++;
            }else if(ref[i + 1]->color == BLUE) {
                blue_counter++;
            }
        }
        find_father(ref[1]);
        
        printf("%d\n", edgeCounter(ref[1]));
    }
}

void find_father(Node* root) {
    if(root->color == RED) {
        root->red++;
    }else if(root->color == BLUE) {
        root->blue++;
    }
    isChecked[root->data] = 1;
    for(int i = 0; i < root->childs.size(); i++) {
        if(isChecked[root->childs[i]->data]) {
            root->father = root->childs[i];
            continue;
        }
        find_father(root->childs[i]);
        root->red += root->childs[i]->red;
        root->blue += root->childs[i]->blue;
    }
}

int edgeCounter(Node* root) {
    int edge = 0;
    if(root->blue == blue_counter && root->red == 0) {
        edge++;
    }else if(root->blue == 0 && root->red == red_counter) {
        edge++;
    }
    for(int i = 0; i < root->childs.size(); i++) {
        if(root->childs[i] == root->father) {
            continue;
        }
        edge += edgeCounter(root->childs[i]);
    }
    return edge;
}