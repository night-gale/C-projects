#include <stdio.h>

#define SIZE 500003
void mismatch(int *, char *, int);
char key[256];
char code[SIZE];
char decoded[SIZE];
int mmArray[SIZE];

int main(void) {
    char temp[2];
    int size = -1;
    int cptr = 0;
    int dptr = 0;
    for(int i = 0; i < 26; i++) {
        scanf("%s", &temp);
        key['a' + i] = temp[0];
    }
    scanf("%s", &code);
    while(code[++size] != '\0');
    for(int i = 0; i < size; i++) {
        decoded[i] = key[code[i]];
    }
    mismatch(mmArray, code, size);

    dptr = size / 2 - 1;
    while(dptr != size ) {
        if(code[cptr] == decoded[dptr] && (cptr != dptr - cptr)) {
            //overlap counted as mismactch
            cptr++;
            dptr++;
        }else {
            if(cptr != 0) {
                cptr = mmArray[cptr - 1];
            }else dptr++;
        }
    }
    printf("%d\n", size - cptr);
}

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