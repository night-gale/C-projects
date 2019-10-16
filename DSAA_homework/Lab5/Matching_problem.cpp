#include <stdio.h>

char s[200002], t[200002];
int T, n, m;

int main(void) {
    scanf("%d", &T);
    
    for(int i = 0; i < T; i++) {
        scanf("%d %d", &n, &m);
        scanf("%s", &s);
        scanf("%s", &t);
        int rightCounter = m;
        int failed = false;
        int pos = -1;

        if(m < n - 1) {
            printf("NO\n");
            continue;
        }

        while(pos != n && s[++pos] != '*');
        for(int j = 0; j < pos; j++) {
            if(s[j] != t[j]) {
                failed = true;
                break;
            }
        }
        for(int j = n - 1; j > pos; j--) {
            if(s[j] != t[--rightCounter]) {
                failed = true;
                break;
            }
        }
        if(failed || (pos == n && m > n)) {
            printf("NO\n");
        }else {
            printf("YES\n");
        }
    }
}