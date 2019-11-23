#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int main(void) {
    vector<int> a;
    for(int i = 0; i < 100001; i++) {
        a.push_back(i);
    }
    srand(time(NULL));
    sort(a.begin(), a.end(), [](int a1, int a2) {
        return rand() > RAND_MAX / 2;
    });
    printf("%d ", 100001);
    for(int i = 0; i < 100001; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}