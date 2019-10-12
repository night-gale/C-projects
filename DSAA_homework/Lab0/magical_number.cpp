#include <iostream>
#include <math.h>

using namespace std;

long long N;
int turns;
int digits;
long long counter = 0;

long long recurse(int n);
bool isNBigger(int temp, int digits, bool isEven);

int main(void) {
    cin >> turns;
    for(int i = 0; i < turns; i++) {
        counter = 0;
        cin >> N;
        if(N < 10) {
            cout << N + 1 << endl;
            continue;
        }
        digits = log10l(N);
        for(int k = 1; k <= digits; k++) {
            counter += recurse(k);
        }
        if(digits % 2 == 0) {
            //odd number of digits
            long long temp = N / powl(10, digits / 2);
            if(isNBigger(temp, digits, false)) {
                counter += temp - powl(10, digits / 2) + 1;
            }else {
                counter += temp - powl(10, digits / 2);
            }
        }else {
            //even number of digits
            long long temp = N / powl(10, digits / 2 + 1);
            if(isNBigger(temp, digits, true)) {
                counter += temp - powl(10, digits / 2) + 1;
            }else {
                counter += temp - powl(10, digits / 2);
            }
        }
        cout << counter << endl;
    }
}

long long recurse(int n) {
    if(n == 3) {
        return 90;
    }else if(n == 2) {
        return 9;
    }else if(n == 1) {
        return 10;
    }else {
        return (10 * recurse(n - 2));
    }
}

bool isNBigger(int temp, int digits, bool isEven) {
    long long result;
    if(isEven) {
        result = temp * powl(10, digits / 2 + 1);
        for(int i = 0; i < digits / 2 + 1; i++) {
            result += (temp % (int)powl(10, digits / 2 - i + 1)) / (int) powl(10, digits / 2 - i) * powl(10, i);
        }
    }else {
        result = temp * powl(10, digits / 2);
        for(int i = 0; i < digits / 2; i++) {
            result += (temp % (int)powl(10, digits / 2 - i + 1)) / (int) powl(10, digits / 2 - i) * powl(10, i);
        }
    }
    return result <= N;
}