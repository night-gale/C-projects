#include <stdio.h>
#include <vector>

using namespace std;

class Node {
    public:
    vector<Node*> childs;
    Node* father;
    int data;
    bool has_people;
    int max_depth;
    Node(int _data) {
        data = _data;
        father = 0;
        has_people = 0;
        max_depth = 0;
    }
};

int T, N, K;
Node* ref[100001];
bool isChecked[100001];
void find_max_depth(Node* root);
int find_distance(Node* root);

int main(void) {
    scanf("%d", &T);

    for(int p = 0; p < T; p++) {
        scanf("%d %d", &N, &K);
        int a, b;
        for(int i = 0; i < N; i++) {
            isChecked[i + 1] = 0;
            ref[i + 1] = new Node(i + 1);
        }

        for(int i = 0; i < N - 1; i++) {
            scanf("%d %d", &a, &b);
            ref[a]->childs.push_back(ref[b]);
            ref[b]->childs.push_back(ref[a]);
        }

        for(int i = 1; i <= K; i++) {
            int temp;
            scanf("%d", &temp);
            ref[temp]->has_people = 1;
        }

        find_max_depth(ref[1]);
        int max_depth = find_distance(ref[1]);
        printf("%d\n", max_depth / 2 + max_depth % 2);
    }
}

void find_max_depth(Node* root) {
    int max_depth = -1;
    isChecked[root->data] = 1;
    for(int i = 0; i < root->childs.size(); i++) {
        if(isChecked[root->childs[i]->data]){
            root->father = root->childs[i];
            continue;
        }
        find_max_depth(root->childs[i]);
        if(max_depth < root->childs[i]->max_depth) {
            max_depth = root->childs[i]->max_depth;
        }
    }
    if(max_depth == -1) {
        if(root->has_people) {
            root->max_depth = 0;
        }else {
            root->max_depth = -1;
        }
    }else {
        root->max_depth = max_depth + 1;
    }
}

int find_distance(Node* root) {
    if(root->max_depth == 0) {
        return 0;
    }

    int max = -1;
    int ptr = -1;
    int se_max = -1;
    int sptr = -1;

    for(int i = 0; i < root->childs.size(); i++) {
        if(root->childs[i]->max_depth > max) {
            se_max = max;
            sptr = ptr;
            max = root->childs[i]->max_depth;
            ptr = i;
        }else if(root->childs[i]->max_depth > se_max) {
            se_max = root->childs[i]->max_depth;
            sptr = i;
        }
    }
    if(max != -1 && se_max != -1) {
        return max + se_max + 2;
    }else if((max == -1 || se_max == -1)) {
        //treat its father as one branch of the current ${root}
        if(!root->father) {
            //${root} does not have father
            if(root->has_people) {
                //one person in ${root} Node
                root->max_depth = 0;
            }else {
                //nobody lives here
                root->max_depth = -1;
            }
        }else {
            //has father
            if(root->father->max_depth != -1) {
                //father branch has max valuable depth that does not equal to -1
                root->max_depth = root->father->max_depth + 1;
            }else if(root->has_people) {
                //father branch has no valuable Node
                //but ${root} Node has a person
                root->max_depth = 0;
            }else {
                //no effective father, nobody
                root->max_depth = -1;
            }
        }
        //equivalent to find the max distance of root->childs[ptr]
        //which has the biggest ${max_depth} value among all other branch
        return find_distance(root->childs[ptr]);
    }
}