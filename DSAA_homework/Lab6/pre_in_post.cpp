#include <stdio.h>
#include <vector>

using namespace std;

class Node {
    public:
    Node* left;
    Node* right;
    int data;
    Node(int _data) {
        data = _data;
        left = 0;
        right = 0;
    }

};

void print_tree(Node* root);
void recurse(int start, int end, int _start, int _end);

int _pre[1001];
int _in[1001];
Node* nodes[1001];
int T, N;

int main() {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        scanf("%d", &N);
        for(int j = 0; j < N; j++) {
            scanf("%d", &_pre[j]);
            nodes[j + 1] = new Node(j + 1);
        }
        for(int j = 0; j < N; j++) {
            scanf("%d", &_in[j]);
        }

        recurse(0, N - 1, 0, N - 1);
        print_tree(nodes[_pre[0]]);
        printf("\n");
        //deinitialize
        for(int j = 1; j <= N; j++) {
            delete nodes[j];
        }
    }
}

void recurse(int start, int end, int _start, int _end) {
    if(start >= end) {
        return;
    }

    int counter = 0;
    while(true) {
        if(_pre[start] == _in[_start + counter]) {
            break;
        }
        counter++;
    }

    if(start + counter + 1 <= end) {
        nodes[_pre[start]]->right = nodes[_pre[start + counter + 1]];
    }
    if(counter != 0) {
        nodes[_pre[start]]->left = nodes[_pre[start + 1]];
    }

    recurse(start + 1, start + counter, _start, _start + counter - 1);
    recurse(start + counter + 1, end, _start + counter + 1, _end);
}

void print_tree(Node* root) {
    if(root->left)
        print_tree(root->left);
    if(root->right)
        print_tree(root->right);
    printf("%d ", root -> data);
}