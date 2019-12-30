#include <stdio.h>
#include <vector>
#include <algorithm>

class Node {
    public:
    int data;
    Node(int data) {
        this->data = data;
    }
};

using namespace std;
int main(void) {
    vector<Node*> a;
    a.push_back(new Node(1));
    a.push_back(new Node(2));
    a.push_back(new Node(3));
    make_heap(a.begin(), a.end(), [](Node* a1, Node* a2) {
        return a2->data < a1->data;
    });
    while(a.size()) {
        pop_heap(a.begin(), a.end(), [](Node* a1, Node* a2) {
        return a2->data < a1->data;
    });
        printf("%d ", a.back()->data);
        a.pop_back();
    }
}