#include <iostream>

using namespace std;

int map[9][9];
bool fillRow(int n);
bool fillColumn(int n);
bool fillBox(int x, int y);
bool filledRows[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

int main() {
    //map read-in
    
    for(int i = 0; i < 9; i++) {
        char temp;
        for(int j = 0; j < 9; j++) {
            cin >> temp;
            if(temp == '|') {
                cin >> temp;
            }
            if(temp == 'x') {
                map[i][j] = 0;
                continue;
            }
            map[i][j] = (int) temp - 48;
        }
        cin >> temp;
    }

    while(true) {
        bool flag = 0;
        bool finishFlag = 1;
        for(int i = 0; i < 9; i++) {
            if(fillRow(i)) {
                flag = 1;
            };  //row scanning
        }
        for(int i = 0; i < 9; i++) {
            if(fillColumn(i)) {
                flag = 1;
            };  //column scanning
        }
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(fillBox(i, j)) {
                    flag = 1;
                };  //box scanning
            }
        }

        for(int i = 0; i < 9; i++) {
            if(filledRows[i] == 0) {
                finishFlag = 0;
                break;
            }
        }
        if(finishFlag) {
            for(int i = 0; i < 9; i++) {
                for(int j = 0; j < 9; j++) {
                    cout << map[i][j] << " ";
                    if((j + 1) % 3 == 0) {
                        cout << '|' << " ";
                    }
                }
                cout << endl;
                if((i + 1) % 3 == 0) {
                    cout << endl;
                }
            }
            return 0;
        }
        if(flag == 0) {
            cout << "The test data is incorrect" << endl;
            return 0;
        }
    }
    cin.get();
}

bool fillRow(int n) {
    if(filledRows[n] != 0) {
        return false;
    }
    bool dict[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int zeroCounter = 0;
    int memory;
    for(int i = 0; i < 9; i++) {
        if(map[n][i] != 0) {
            dict[map[n][i] - 1] = 1;
        }else{
            zeroCounter++;   //count the number of unfilled box
            memory = i;   //write the unfilled coordinate to memory
        }
    }
    if(zeroCounter == 0) {
        filledRows[n] = 1;
        return false;
    }
    if(zeroCounter == 1) {
        for(int i = 0; i < 9; i++) {
            if(!dict[i]) {
                map[n][memory] = i + 1;
                break;
            }
        }
        filledRows[n] = 1;
        return true;
    }
    return false;
}

bool fillColumn(int n) {
    bool dict[9] = {0, 0, 0, 0, 0, 0, 0 ,0, 0};
    int zeroCounter = 0;
    int memory;
    for(int i = 0; i < 9; i++) {
        if(map[i][n] != 0) {
            dict[map[i][n] - 1] = 1;
        }else {
            zeroCounter++;
            memory = i;
        }
    }
    if(zeroCounter == 1) {
        for(int i = 0; i < 9; i++) {
            if(!dict[i]) {
                map[memory][n] = i + 1;
                break;
            }
        }
        return true;
    }
    return false;
}

bool fillBox(int x, int y) {
    bool dict[9] = {0, 0, 0, 0, 0, 0, 0 ,0, 0};
    int zeroCounter = 0;
    int memory[2];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(map[x * 3 + i][y * 3 + j] != 0) {
                dict[map[x * 3 + i][y * 3 + j] - 1] = 1;
            }else {
                zeroCounter++;
                memory[0] = x * 3 + i;
                memory[1] = y * 3 + j;
            }
        }
    }
    if(zeroCounter == 1) {
        for(int i = 0; i < 9; i++) {
            if(!dict[i]) {
                map[memory[0]][memory[1]] = i + 1;
                break;
            }
        }
        return true;
    }
    return false;
}