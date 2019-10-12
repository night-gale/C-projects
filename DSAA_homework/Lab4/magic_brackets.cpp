#include <stdio.h>

class Stack{
    public:
    char* array;
    int top;
    
    Stack(int sizeOfArray) {
        array = new char[sizeOfArray + 1];
        top = -1;
    }

    void push(char data) {
        array[++top] = data;
    }

    char pop() {
        return array[top--];
    }

    char peek() {
        return top == -1? -1: array[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

int T, n;
char input[30001];

int main(void) {
    scanf("%d", &T);
    
    for(int i = 0; i < T; i++) {
        Stack stack(30001);
        scanf("%d", &n);
        scanf("%s", &input);
        int j = 0;
        bool fail_flag = false;

        for(j; j < n; j++) {
            if(input[j] == '(' || input[j] == '{' || input[j] == '[') {
                stack.push(input[j]);
            }else if(input[j] == ')') {
                if(stack.isEmpty() || stack.peek() != '(') {
                    fail_flag = true;
                    break;
                }else {
                    stack.pop();
                }
            }else if(input[j] == '}') {
                if(stack.isEmpty() || stack.peek() != '{') {
                    fail_flag = true;
                    break;
                }else {
                    stack.pop();
                }
            }else if(input[j] == ']') {
                if(stack.isEmpty() || stack.peek() != '[') {
                    fail_flag = true;
                    break;
                }else {
                    stack.pop();
                }
            }
        }
        if(stack.isEmpty() && j == n) {
            printf("YES\n");
        }else if(fail_flag || (!stack.isEmpty())) {
            printf("NO\n");
        }
    }
}