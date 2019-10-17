#include <stdio.h>

void mismatch(int *mmArray, char *_string,  int size) {
    mmArray[0] = 0;
    for(int i = 1; i < size; i++) {
        int temp = mmArray[i - 1];
        while(true) {
            if(_string[temp] == _string[i]) {
                mmArray[i] = temp + 1;
                break;
            }
            
            if(temp == 0) {
                mmArray[i] = 0;
                break;
            }
            temp = mmArray[temp - 1];
        }
    }
}

int N;
char pattern[10003];
char input[10003];
int mmArray[10003];

int main(void) {

    int counter = 0;

    scanf("%d", &N);


    for(int i = 0; i < N; i++) {
        int size = -1;
        int iptr = 0;  //pointer to input
        int pptr = 0;   //pointer to pattern
        scanf("%s", &pattern);
        while(pattern[++size] != '\0');
        if(size % 3) size = size / 3 + 1;
        else size = size / 3;
        mismatch(mmArray, pattern, size);
        scanf("%s", &input);
        
        while(input[iptr] != '\0') {
            if(input[iptr] == pattern[pptr]) {
                iptr++;
                pptr++;
                if(pptr == size) {
                    counter++;
                    break;
                }
            }else {
                if(pptr != 0) {
                    pptr = mmArray[pptr - 1];
                }else iptr++;
            }
        }
    }
    printf("%d\n", counter);
}

