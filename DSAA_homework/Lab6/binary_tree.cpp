class bTree_node{
    public:
    int data;
    bTree_node* left;
    bTree_node* right;
    bTree_node(int data) {
        this->data = data;
        left = 0;
        right = 0;
    }
    ~bTree_node() {
        if(left != 0) {
            delete left;
        }if(right != 0) {
            delete right;
        }
    }
};

class bTree {
    public:
    bTree_node* root;

    bTree(int data) {
        root = new bTree_node(data);
    }
    ~bTree() {
        delete root;
    }

    void insert(int toIns) {
        bTree_node* newNode = new bTree_node(toIns);
        bTree_node* current = root;
        while(true) {
            if(toIns > current->data) {
                if(current->right == 0) {
                    current->right = newNode;
                    break;
                }
                current = current->right;
            }else{
                if(current->left == 0) {
                    current->left = newNode;
                    break;
                }
                current = current->left;
            }
        }
    }

    bTree_node* has(int key) {
        bTree_node* current = root;
        while(true) {
            if(current == 0) {
                return 0;
            }
            if(key > current->data) {
                current = current->right;
            }else if(key < current->data){
                current = current->left;
            }else {
                return current;
            }
        }
    }
    
};