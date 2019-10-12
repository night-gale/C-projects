#include <iostream>
#include <sstream>

using namespace std;

int main(void) {
    int turns;
    cin >> turns;
    char result[2];
    for(int i = 0; i < turns; i++) {
        for(int j = 0; j < 9; j++) {
            char temp;
            cin >> temp;
            if(j == 4) {
                cout << temp << endl;
            }
        }
    }
}