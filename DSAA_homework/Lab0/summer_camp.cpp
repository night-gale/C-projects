#include <iostream>
#include <cmath>

using namespace std;

int turns;
long long n;

int main(void) {
    cin >> turns;
    for(int i = 0; i < turns; i++) {
        cin >> n;
        if(n == 1) {
            cout << "impossible" << endl;
            continue;
        }
        if(n % 2 == 1) {
            cout << 2 << endl;
            continue;
        }
        bool found = 0;
        for(long long j = 3; j < sqrtl(2 * n); j++) {
            if(j % 2 == 1) {
                if((n % j == 0) && ((n / j - j / 2) >= 1)) {
                    cout << j << endl;
                    found = 1;
                    break;
                }
            }else if(j % 2 == 0) {
                if(((n - (n / j * j)) == (j / 2)) && ((n / j - j / 2 + 1) >= 1)) {
                    cout << j << endl;
                    found = 1;
                    break;
                }
            }
        }
        if(!found) {
            cout << "impossible" << endl;
        }
    }
}