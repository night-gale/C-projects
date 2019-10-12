#include <stdio.h>

class Link{
    public:
    int data;
    Link* next;

    Link(int data) {
        Link::data = data;
        //initialize the pointer
        next = 0;
    }
    ~Link() {
        if(next != 0) {
            delete next;
        }
    }
};

int n;
char operation;
Link* head;
Link* tail;

int main(void) {
    scanf("%d\n", &n);
    head = new Link(0);
    tail = head;

    for(int i = 0; i < n; i++) {
        scanf("%c", &operation);

        if(operation == 'E') {
            int toEnqueue;
            scanf("%d", &toEnqueue);
            (*tail).next = new Link(toEnqueue);
            tail = (*tail).next;
        }else if(operation == 'D') {
            Link* temp = head;
            head = (*head).next;
            (*temp).next = 0;
            delete temp;
        }else if(operation == 'A') {
            printf("%d\n", (*(*head).next).data);
        }
        scanf("%c", &operation);
    }
    Link* current = (*head).next;
    while(current != NULL) {
        printf("%d ", (*current).data);
        current = (*current).next;
    }
    delete head;
    return 0;
}