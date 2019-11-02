#include <stdio.h>
#include <vector>

#define WHITE 0
#define RED 1
#define BLUE 2

using namespace std;


class Node {
    public:
    vector<Node*> childs;
    int data;
    int color;
    Node(int _data) {
        data = _data;
    }
};

int T, N;
Node* ref[100002];
bool isChecked[100002];
Node* find_biggest(Node* root, int color);

int main() {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        scanf("%d", &N);
        
        for(int j = 0; j < N; j++) {
            ref[j + 1] = new Node(j + 1);
            isChecked[j + 1] = 0;
        }

        for(int j = 0; j < N - 1; j++) {
            int a, b;
            scanf("%d %d", &a, &b);
            ref[a]->childs.push_back(ref[b]);
            ref[b]->childs.push_back(ref[a]);
        }
        int color_in;
        for(int j = 0; j < N; j++) {
            scanf("%d", &(ref[j + 1]->color));
        }

        Node* test = find_biggest(ref[1], RED);
        printf("%d", test->data);
    }
}

//find the smallest tree that contains all the nodes that $color specified
Node* find_biggest(Node* root, int color) {
    if(root->color == color) {
        return root;
    }else if(root->childs.empty() && root->color != color) {
        return NULL;
    }
    isChecked[root->data] = 1;
    vector<Node*> _have;
    for(int i = 0; i < root->childs.size(); i++) {
        if(isChecked[root->childs[i]->data]) continue;
        Node* temp = find_biggest(root->childs[i], color);
        if(temp) {
            _have.push_back(temp);
        }
    }
    int _size = _have.size();
    if(_size > 1) {
        return root;
    }else if(_size == 1){
        return _have.back();
    }else {
        return NULL;
    }
}