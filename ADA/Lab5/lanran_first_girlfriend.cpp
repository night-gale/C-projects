#include <stdio.h>
#include <algorithm>

int N;
const int k_SIZE = 500001;
struct Trick
{
    int a;
    int b;
};

Trick tricks[k_SIZE];
int result;
int T;
int last;

bool cmp(Trick a, Trick b) {
    return a.b < b.b;
}

int main(void) {
    scanf("%d", &T);
    for(int t = 0; t < T; t++) {
        result = 0;
        last = 0;
        scanf("%d", &N);
        for(int i = 0; i < N; i++) {
            scanf("%d %d", &(tricks[i].a), &(tricks[i].b));
        }

        std::sort(tricks, tricks+N, cmp);
        for(int i = 0; i < N; i++) {
            if(tricks[i].a > last) {
                last = tricks[i].b;
                result++;
            }
        }
        printf("%d\n", result);
    }


}