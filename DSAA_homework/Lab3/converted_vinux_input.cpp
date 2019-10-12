#include <stdio.h>

class Link{
    public:
    char data;
    Link* previous;
    Link* next;

    Link(char data) {
        Link::data = data;
        //initialize the pointers
        previous = 0;
        next = 0;
    }
    ~Link() {
        if(next != 0) {
            delete next;
        }
    }
};

class Delinked_list {
    public:
    Link* head;
    Link* tail;
    Link* current;

    Delinked_list(){
        head = new Link(0);
        (*head).next = new Link(-1);
        tail = (*head).next;
        (*tail).previous = head;
        current = (*head).next;
    }
    ~Delinked_list() {
        if(head != 0) {
            delete head;
        }
    }

    void insert(char data, char instruction) {
        switch (instruction) {
        case 'r': {
            if(current != tail) {
                (*current).data = data;
            }else {
                Link* newLink = new Link(data);
                Link* previous = (*current).previous;
                (*previous).next = newLink;
                (*newLink).next = current;
                (*newLink).previous = previous;
                (*current).previous = newLink;
                current = newLink;
            }
            break;
        }
        case 'I': {
            current = (*head).next;
            break;
        }
        case 'H': {
            if((*current).previous != head) {
                current = (*current).previous;
            }
            break;
        }
        case 'L': {
            if(current != tail) {
                current = (*current).next;
            }
            break;
        }
        case 'x': {
            if(current != tail) {
                Link* toDelete = current;
                (*(*current).previous).next = (*current).next;
                (*(*current).next).previous = (*current).previous;
                current = (*current).next;
                (*toDelete).next = 0;
                delete toDelete;
            }
            break;
        }
        default: {
            //insert to previous
            Link* newLink = new Link(data);
            Link* previous = (*current).previous;
            (*previous).next = newLink;
            (*newLink).next = current;
            (*newLink).previous = previous;
            (*current).previous = newLink;
            break;
        }
        }
    }

    void print() {
        Link *peek = (*head).next;
        while(peek != tail) {
            printf("%c", (*peek).data);
            peek = (*peek).next;
        }
        printf("\n");
    }
};

int T, n;
char currentInput = 0;
char previousInput = 0;
Delinked_list* list;

int main(void) {
    scanf("%d\n", &T);
    for(int i = 0; i < T; i++) {
        scanf("%d\n", &n);
        list = new Delinked_list();
        previousInput = 0;
        for(int j = 0; j < n; j++) {
            scanf("%c", &currentInput);
//            printf("%c%c ", currentInput, previousInput);
            if(((currentInput - 48)) >= 0 && ((currentInput - 48) <= 9)) {
                //currentinput is a number
                if(previousInput == 'r') {
                    (*list).insert(currentInput, 'r');
                }else {
                    (*list).insert(currentInput, 0);
                }
            }else if(currentInput != 'r') {
                (*list).insert(0, currentInput);
            }
            previousInput = currentInput;
        }
        (*list).print();
        delete list;
    }
}