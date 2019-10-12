#include <stdio.h>

class Link
{
    public:
    int coefficient;
    int exponent;
    Link* next;

    Link(int coefficient, int exponent);
    ~Link();
};


int T;
int n;
int m;
int q;
int exponent;

int tempc;
int tempe;

int main(void) {
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        Link *head = NULL;
        Link *tail = NULL;
        scanf("%d", &n);
        for(int j = 0; j < n; j++) {
            scanf("%d %d", &tempc, &tempe);
            if(head == NULL) {
                head = new Link(tempc, tempe);
                tail = head;
            }else {
                (*tail).next = new Link(tempc, tempe);
                tail = (*tail).next;
            }
        }
        scanf("%d", &m);
        Link *current = head;
        for(int j = 0; j < m; j++) {
            scanf("%d %d", &tempc, &tempe);

            if(((*head).exponent > tempe)) {
                Link* newLink = new Link(tempc,tempe);
                (*newLink).next = head;
                head = newLink;
                current = head;
                continue;
            }

            while(current != tail) {
                if((*current).exponent == tempe) {
                    (*current).coefficient += tempc;
                    break;
                }else if((*(*current).next).exponent > tempe) {
                    Link* newLink = new Link(tempc, tempe);
                    (*newLink).next = (*current).next;
                    (*current).next = newLink;
                    break;
                }
                current = (*current).next;
            }

            if(current == tail) {
                if((*current).exponent == tempe) {
                    (*current).coefficient += tempc;
                }else {
                    (*tail).next = new Link(tempc, tempe);
                    tail = (*tail).next;
                }
            }
        }
        scanf("%d", &q);
        current = head;
        for(int j = 0; j < q; j++) {
            scanf("%d", &tempe);
            while(current != tail) {
                if((*current).exponent == tempe) {
                    printf("%d ", (*current).coefficient);
                    break;
                }else if((*(*current).next).exponent > tempe) {
                    printf("%d ", 0);
                    break;
                }
                current = (*current).next;
            }
            if(current == tail) {
                if(current == NULL) {
                    printf("0 ");
                }else if(tempe == (*tail).exponent) {
                    printf("%d ", (*tail).coefficient);
                }else {
                    printf("0 ");
                }
            }
        }
        printf("\n");
        delete head;
    }
}

Link::Link(int coefficent, int exponent)
{
    Link::coefficient = coefficent;
    Link::exponent = exponent;
    next = NULL;
}

Link::~Link() {
    if(next != NULL) {
        delete next;
    }
}