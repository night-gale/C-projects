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

int main(void) {
    char _string[10000];
    int mmArray[10000];
    scanf("%s", &_string);
    int length = -1;
    while(_string[++length] != '\0');
    mismatch(mmArray, _string, length);
    for(int i = 0; i < length; i++) {
        printf("%d ", mmArray[i]);
    }
}