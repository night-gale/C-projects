#include <stdio.h>

int queue[20000001];
int front = 0;
int rear = 0;
int n;
char operation[2];

int main(void) {
    scanf("%d\n", &n);

    for(int i = 0; i < n; i++) {
        scanf("%s", &operation);

        if(operation[0] == 'E') {
            scanf("%d", &queue[rear++]);
        }else if(operation[0] == 'D') {
            front++;
        }else if(operation[0] == 'A') {
            printf("%d\n", queue[front]);
        }
    }

    for(int j = front; j < rear; j++) {
        printf("%d ", queue[j]);
    }
}