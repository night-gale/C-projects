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

int T;
char string[200003];
int mmArray[200003];

int main(void) {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        scanf("%s", &string);
        int size = -1;
        int max = 0;
        int counter = -1;
        while(string[++size] != '\0');
        mismatch(mmArray, string, size);
        
        max = size - mmArray[size - 1];
        if(mmArray[size - 1] / max) {
            printf("%d\n", (max - (mmArray[size - 1] % max)) % max);
        }else printf("%d\n", (max - (mmArray[size - 1] % max)));
    }
}