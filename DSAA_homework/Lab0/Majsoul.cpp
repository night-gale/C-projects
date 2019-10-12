#include <iostream>
#include <cstring>

using namespace std;

int main(void) {
    char projection1[4] = {'W', 'T', 'Y'};
    char projection2[7] = {'E', 'S', 'W', 'N', 'B', 'F', 'Z'};
    int turns;
    cin >> turns;
    for(int i = 0; i < turns; i++) {
        int* input = new int[13];
        for(int j = 0 ; j < 13; j++) {
            char temp[3];
            cin >> temp;
            if(strlen(temp) >= 2) {
                for(int k = 0; k < 3; k++) {
                    if(temp[0] == projection1[k]) {
                        input[j] = (k + 1) * 10;
                    }
                }
                input[j] += ((int) temp[1]) - 48;
            }else{
                for(int k = 0; k < 7; k++) {
                    if(temp[0] == projection2[k]) {
                        input[j] = (k + 1) * 100;
                    }
                }
            }
        }
        
        for(int j = 0; j < 13; j++) {
            for(int k = j + 1; k < 13; k++) {
                if(input[j] > input[k]) {
                    int temp = input[j];
                    input[j] = input[k];
                    input[k] = temp;
                }
            }
        }
        for(int j = 0; j < 13; j++) {
            if(input[j] < 100) {
                cout << projection1[input[j] / 10 - 1] << input[j] % 10 << " ";
            }else {
                cout << projection2[input[j] / 100 - 1] << " ";
            }
        }
        cout << endl;
        delete [] input;
    }
    cin.get();
}