#include <stdio.h>


int T;
int operPriority[256];

int main(void) {
    scanf("%d", &T);
    operPriority['+'] = 4;
    operPriority['-'] = 4;
    operPriority['*'] = 3;
    operPriority['&'] = 5;
    operPriority['^'] = 6;
    operPriority['|'] = 7; 
    operPriority['('] = 1;

    // printf("%d", ~3);

    for(int i = 0; i < T; i++) {
        char input[150] = {0};
        int inputCounter = 0;
        int numb[150] = {0};
        char oper[150] = {0};
        int expCounter = -1;
        bool isPreviousNumber;
        char opStack[150] = {0};
        int top = -1;
        char signStack[150] = {0};
        int signTop = -1;
        int compCounter = 0;
        int numStack[150];
        int numTop = -1;
        scanf("%s", &input);

        while(input[inputCounter] != '\0') {
            if((input[inputCounter] - 48 <= 9) && (input[inputCounter] - 48 >= 0)) {
                int temp = input[inputCounter] - 48;
                inputCounter++;
                // printf("%d%d", '&' - 48 <= 9, '&' - 48 >= 0);
                while((input[inputCounter] - 48 <= 9) && (input[inputCounter] - 48 >= 0)) {
                    temp = temp * 10 + (input[inputCounter] - 48);
                    inputCounter++;
                }
                while(signTop != -1) {
                    switch(signStack[signTop--]) {
                        case '+': {
                            break;
                        }case '-': {
                            temp = -temp;
                            break;
                        }case '~': {
                            temp = ~temp;
                            break;
                        }
                    }
                }
                numb[++expCounter] = temp;
                isPreviousNumber = true;
            }else {
                switch(input[inputCounter]) {
                     case '(': {
                        opStack[++top] = input[inputCounter++];
                        isPreviousNumber = true;
                        break;
                    }case ')': {
                        while(opStack[top] != '(') {
                            oper[++expCounter] = opStack[top--];
                        }
                        top--;
                        inputCounter++;
                        isPreviousNumber = true;
                        break;
                    }case '+':
                     case '-':
                     case '*':
                     case '&':
                     case '^':
                     case '|': {
                        char temp = input[inputCounter];
                        signTop = -1;
                        if(!isPreviousNumber) {
                            signStack[++signTop] = temp;
                        }else {
                            while((top != -1) && (opStack[top] != '(') && (operPriority[temp] >= operPriority[opStack[top]])) {
                                oper[++expCounter] = opStack[top--];
                            }
                            opStack[++top] = temp;
                        }
                        inputCounter++;
                        while(input[inputCounter] == '+' || input[inputCounter] == '-' || input[inputCounter] == '~') {
                            signStack[++signTop] = input[inputCounter++];
                        }
                        break;
                    }
                }
            }
        }
        while(top != -1) {
            oper[++expCounter] = opStack[top--];
        }
        
        while(compCounter <= expCounter) {
            if(oper[compCounter] != 0) {
                int a = numStack[numTop--];
                int b = numStack[numTop--];
                int result;
                switch(oper[compCounter++]) {
                    case '+': {
                        result = a + b;
                        break;
                    }case '-': {
                        result = a - b;
                        break;
                    }case '*': {
                        result = a * b;
                        break;
                    }case '&': {
                        result = a & b;
                        break;
                    }case '|': {
                        result = a | b;
                        break;
                    }case '^': {
                        result = a ^ b;
                        break;
                    }
                }
                numStack[++numTop] = result;
            }else {
                numStack[++numTop] = numb[compCounter++];
            }
        }
        printf("%d\n", numStack[numTop--]);
        // printf("%d\n", 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2);
    }
    
}