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
    Node(int _data) {
        data = _data;
        father = 0;
    }
};

int T, N;
Node* ref[100002];
bool isChecked[100002];
Node* find_biggest(Node* root, int color);
int find_depth(Node* root, Node* key, int depth);

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

        Node* red = find_biggest(ref[1], RED);
        Node* blue = find_biggest(ref[1], BLUE);
        int counter = 0;
        Node* red_father = red->father;
        Node* blue_father = blue->father;
        for(int j = 0; j < N; j++) {
            isChecked[j + 1] = 0;
        }
        int distance;
        if(red_father) {
            
            distance = find_depth(red_father, blue, 0);
        }else if(blue_father) {
            isChecked[blue->data] = 1;
            distance = find_depth(blue_father, red, 0);
        }else
            distance = 0;
        if(distance == -1) {
            printf("%d", 0);
        }else 
            printf("%d", distance);
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
        if(isChecked[root->childs[i]->data]) {
            root->father = root->childs[i];
            continue;
            };
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

int find_depth(Node* root, Node* key, int depth) {
    if(root == key) {
        return depth;
    }else if(root->childs.empty()){
        return -1;
    }else {
        int temp_de;
        for(int i = 0; i < root->childs.size(); i++) {
            if(isChecked[root->childs[i]->data]) continue;
            temp_de = find_depth(root->childs[i], key, depth + 1);
            if(temp_de != -1) {
                break;
            }
        }
        return temp_de;
    }
}