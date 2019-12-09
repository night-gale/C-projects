#include <stdio.h>

int T, N;
char input[7];
void printLEC(bool* isOut, char* out, int cnt);

int main(void) {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        scanf("%d", &N);
        scanf("%s", &input);

        for(int x = 0; x < N - 1; x++) {
            for(int y = x + 1; y < N; y++) {
                if(input[x] > input[y]) {
                    char temp = input[x];
                    input[x] = input[y];
                    input[y] = temp;
                }
            }
        }
        bool a[7] = {0};
        char ch[7] = {0};
        printLEC(a, ch, 0);
    }
}

void printLEC(bool* isOut, char* out, int cnt) {
    if(cnt == N) {
        for(int i = 0; i < N; i++) {
            printf("%c", out[i]);
        }
        printf("\n");
        return;
    }
    int i;
    for(i = 0; i < N; i++) {
        if(!isOut[i]) {
            bool temp[7];
            char _out[7];
            for(int j = 0; j < N; j++) {
                temp[j] = isOut[j];
                _out[j] = out[j];
            }
            temp[i] = 1;
            _out[cnt] = input[i];
            printLEC(temp, _out, cnt + 1);
        }
    }
}