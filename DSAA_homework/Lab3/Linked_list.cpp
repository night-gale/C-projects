class Link
{
    public:
    int data;
    Link* next;

    Link(int data);
    ~Link();
    void setNext(int data);
    void removeNext();
};

class Linked_list
{
    public:
    Link* head;
    Link* tail;

    Linked_list(int data);
    ~Linked_list();
    void insert_descending(int data);
    void insert_ascending(int data);
    void insert_at_end(int data);
    void insert_at_head(int data);
    void remove(int key);
};

Linked_list::Linked_list(int data) 
{
    head = new Link(data);
    tail = head;
}

Linked_list::~Linked_list() 
{
    delete head;
}

void Linked_list::insert_ascending(int data) 
{
    Link* current = head;
    Link* next = (*head).next;
    while(next != 0)
    {
        if((*next).data >= data)
        {
            current = new Link(data);
            (*current).next = next;
            return;
        }
        current = (*current).next;
        next = (*next).next;
    }
    insert_at_end(data);
}

Link::Link(int data)
{
    Link::data = data;
}

void Link::setNext(int data) 
{
    next = new Link(data);
}

void Link::removeNext()
{
    delete next;
}

Link::~Link()
{
    if(next != 0) {
        delete next;
    }
}