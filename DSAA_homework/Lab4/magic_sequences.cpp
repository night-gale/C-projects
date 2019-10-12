#include <stdio.h>

class StackAndQueue{
    public:
    int* array;
    int* _index;
    int front;
    int rear;
    
    StackAndQueue(int sizeOfArray) {
        array = new int[sizeOfArray + 1];
        _index = new int[sizeOfArray + 1];
        front = 0;
        rear = 0;
    }

    void push(int data, int index) {
        _index[rear] = index;
        array[rear++] = data;
        
    }

    int pop() {
        return (isEmpty()? __INT64_MAX__: array[--rear]);
    }

    int deQueue() {
        return array[front++];
    }

    int peek() {
        return (isEmpty())? __INT64_MAX__: array[rear - 1];
    }

    int peekFrontIndex() {
        return _index[front];
    }

    int peekFront() {
        return array[front];
    }

    bool isEmpty() {
        return front >= rear;
    }
};

int input[20000001], m, counter = -1;
int xorSum = 0;

int main(void) {
    scanf("%d", &m);
    int temp;
    StackAndQueue sq(2000001);
    scanf("%d", &temp);
    sq.push(temp, ++counter);
    while(true) {
        scanf("%d", &temp);
        counter++;
        if(temp == -1) {
            break;
        }
        
        while(!(sq.isEmpty()) && sq.peek() < temp) {
            sq.pop();
        }

        sq.push(temp, counter);

        if(!sq.isEmpty() && ((counter - sq.peekFrontIndex()) >= m)) {
            sq.deQueue();
        }

        if(counter >= m - 1) {
            xorSum ^= sq.peekFront();
        }
    }

    printf("%d", xorSum);
}