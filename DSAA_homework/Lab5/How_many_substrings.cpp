#include <stdio.h>

int T;

int main(void) {
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        char string[1002] = {0};
        int counter = -1;
        scanf("%s", &string);

        while(string[++counter] != '\0');
        printf("%d\n", (counter + 1) * (counter) / 2);
    }
}