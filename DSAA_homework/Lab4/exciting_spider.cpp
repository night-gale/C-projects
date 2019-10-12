#include <stdio.h>
#include <sys/time.h>

long long getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int T, n, input[300002], output[300001];
int stack[300002];

int main(void) {
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        scanf("%d", &n);
        int target = 1;
        int start = 0;
        int top = -1;
        int counter = -1;
        bool isInStack[300002] = {0};
        
        // long long t0 = getCurrentTime();

        for(int j = 0; j < n; j++) {
            scanf("%d", &input[j]);
        }
        
        // long long t1 = getCurrentTime();    

        while(true) {
            if((top > -1) && (stack[top] <= target)) {
                //stack not empty and top element is less or equal than target
                output[++counter] = stack[top--];  //pop and print
            }else if((target <= n) && (!(isInStack[target]))) {  //if target is in queue
                while((start < n) && (input[start] != target)) {
                    isInStack[input[start]] = true;
                    stack[++top] = input[start++];
                }
                output[++counter] = input[start++];
                target++;
            }else if(target <= n){
                target++;
            }

            if(start >= n) {
                while(top > -1) {
                   output[++counter] = stack[top--];
                }
                break;
            }
        }

        // long long t2 = getCurrentTime();

        for(int j = 0; j <= counter; j++) {
            printf("%d ", output[j]);
        }
        printf("\n");

        // long long t3 = getCurrentTime();

        // printf("input: %d\nrun: %lld\noutput: %lld", t1 - t0, t2 - t1, t3 - t2);
    }
}