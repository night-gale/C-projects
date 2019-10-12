#include <stdio.h>
#include <windows.h>

int main(void) {
    char buffer[100];
    scanf("%s", &buffer);
    printf("%s", buffer);
    int i = 0;
    while(buffer[i] != '\0') {
        printf("%c", buffer[i]);
        i++;
    }
    system("pause");
}