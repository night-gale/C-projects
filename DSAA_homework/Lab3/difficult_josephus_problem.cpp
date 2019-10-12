#include <stdio.h>

#include <stdio.h>

class Link{
    public:
    int note;
    int index_;
    Link* previous;
    Link* next;

    Link(int note, int index_) {
        Link::note = note;
        Link::index_ = index_;
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
    int length;
    int previousNote;

    Delinked_list(int note, int index_, int previousNote){
        head = new Link(note, index_);
        tail = head;
        current = head;
        length = 1;
        Delinked_list::previousNote = previousNote;
    }
    ~Delinked_list() {
        if(head != 0) {
            delete head;
        }
    }

    void insert(int note, int index_) {
        Link* newLink = new Link(note, index_);
        (*tail).next = newLink;
        (*newLink).previous = tail;
        tail = newLink;
        length++;
    }

    void linkHeadAndTail() {
        (*head).previous = tail;
        (*tail).next = head;
    }

    int countAndRemove() {
        int modedNumber = (previousNote - 1) % length;
        if(modedNumber > ((length) / 2)) {
            for(int i = 0; i < (length - modedNumber); i++) {
                current = (*current).previous;
            }
        }else {
            for(int i = 0; i < modedNumber; i++) {
                current = (*current).next;
            }
        }
        remove();
        return length;
    }

    void remove() {
        previousNote = (*current).note;
        Link* pre = (*current).previous;
        Link* nex = (*current).next;
        (*pre).next = nex;
        (*nex).previous = pre;
        (*current).next = 0;
        delete current;
        current = nex;
        length--;
    }

};


int T, n, m;
Delinked_list* list;

int main(void) {
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        scanf("%d %d", &n, &m);
        int note;
        scanf("%d", &note);
        list = new Delinked_list(note, 1, m);
        for(int j = 2; j <= n; j++) {
            scanf("%d", &note);
            (*list).insert(note, j);
        }
        (*list).linkHeadAndTail();
        for(int j = 0; j < n - 1; j++) {
            (*list).countAndRemove();
        }
        printf("%d\n", (*(*list).current).index_);
    }
}