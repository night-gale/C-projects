#include <stdio.h>

class Link{
    public:
    int ndex;
    Link* previous;
    Link* next;

    Link(int ndex) {
        Link::ndex = ndex;
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

    Delinked_list(){
        head = 0;
        tail = 0;
    }
    ~Delinked_list() {
        if(head != 0) {
            delete head;
        }
    }
    Link* insert(int ndex) {
        if(head == 0) {
            head = new Link(ndex);
            tail = head;
            return head;
        }
        Link* newLink = new Link(ndex);
        (*tail).next = newLink;
        (*newLink).previous = tail;
        tail = newLink;
        return newLink;
    }

    void swap(Link* x1, Link* y1, Link* x2, Link* y2) {
        Link *l1 = (*x1).previous;
        Link *r1 = (*y1).next;
        Link *l2 = (*x2).previous;
        Link *r2 = (*y2).next;
        if(r1 == x2) {
            if(l1 != 0) (*l1).next = x2;
            else head = x2;
            if(r2 != 0) (*r2).previous = y1;
            else tail = y1;
            (*x2).previous = l1;
            (*x1).previous = y2;
            (*y2).next = x1;
            (*y1).next = r2;
            return;
        }else if(r2 == x1) {
            if(l2 != 0) (*l2).next = x1;
            else head = x1;
            if(r1 != 0) (*r1).previous = y2;
            else tail = y2;
            (*x2).previous = y2;
            (*x1).previous = l2;
            (*y1).next = x2;
            (*y2).next = r1;
            return;
        }
        if(l1 != 0) (*l1).next = x2;
        else head = x2;
        if(l2 != 0) (*l2).next = x1;
        else head = x1;
        if(r1 != 0) (*r1).previous = y2;
        else tail = y2;
        if(r2 != 0) (*r2).previous = y1;
        else tail = y1;
        (*x1).previous = l2;
        (*x2).previous = l1;
        (*y1).next = r2;
        (*y2).next = r1;
    }
    void print() {
        Link *current = head;
        while((*current).next != 0) {
            printf("%d ", (*current).ndex);
            current = (*current).next;
        }
        printf("%d\n", (*current).ndex);
    }
};
#define y1 Y1

Link* reference[100000];
int T, N, M, x1, Y1, x2, y2;
int ndex;
Delinked_list* list;

int main(void) {
    scanf("%d", &T);
//const read-in
    for(int i = 0; i < T; i++) {
        list = new Delinked_list();
        scanf("%d %d", &N, &M);
    //linkedlist readin;
        for(int j = 0; j < N; j++) {
            scanf("%d", &ndex);
            reference[ndex] = (*list).insert(ndex);
        }
    //swap
        for(int j = 0; j < M; j++) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            (*list).swap(reference[x1], reference[y1], reference[x2], reference[y2]);
        }
        (*list).print();
        delete list;
    }
}