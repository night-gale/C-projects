#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

int turns;
long long Index, x, y;
void findCoordinate(long long currentIndex);
void findIndex(long long currentX, long long currentY);

int main(void) {
    cin >> turns;
    for(int i = 0; i < turns; i++) {
        if(cin.peek() == '\n') {
            cin.get();
        }
        if(cin.peek() == '(') {
            //coordinates to index
            scanf("(%ld,%ld)", &y, &x);
            Index = 0;
            findIndex(x, y);
            cout << Index << endl;
        }else {
            //index to coordinates
            cin >> Index;
            x = 0;
            y = 0;
            findCoordinate(Index);
            printf("(%ld,%ld)\n", y, x);
        }
    }
}

void findCoordinate(long long currentIndex) {
    int scale = (int) log2l(currentIndex) / 2;
    if(currentIndex <= 3) {
        x++;
        y++;
        if(currentIndex == 3) {
            x++;
            y++;
        }else if(currentIndex == 2) {
            y++;
        }
        return;
    }else {
        int position = (currentIndex - 1) / (long long)powl(4, scale) + 1;
        if((currentIndex - (long long) powl(4, scale)) == 0) {
            x += powl(2, scale);
            y += 1;
            return;
        }else {
            if(position == 3) {
                x += powl(2, scale);
                y += powl(2, scale);
            }else if(position == 4) {
                x += powl(2, scale);
            }else if(position == 2) {
                y += powl(2, scale);
            }
            findCoordinate(currentIndex - (long long) powl(4, scale) * (position - 1));
        }
    }
}

void findIndex(long long currentX, long long currentY) {
    int xScale = (int) log2l(currentX - 1);
    int yScale = (int) log2l(currentY - 1);
    int scale = max(xScale, yScale);
    if(currentX <= 2 && currentY <= 2) {
        if(currentX == 1) {
            if(currentY == 1) {
                Index += 1;
            }else {
                Index += 2;
            }
        }else {
            if(currentY == 1) {
                Index += 4;
            }else {
                Index += 3;
            }
        }
        return;
    }else {
        if(((currentX - (long long) powl(2, scale)) == 0) && currentY == 1) {
            Index += currentX * currentX;
            return;
        }else {
            if(currentX > powl(2, scale) && currentY <= powl(2, scale)) {
                Index += 3 * powl(4, scale);
                findIndex(currentX - powl(2, scale), currentY);
            }else if(currentX > powl(2, scale) && currentY > powl(2, scale)) {
                Index += 2 * powl(4, scale);
                findIndex(currentX - powl(2, scale), currentY - powl(2, scale));
            }else if(currentX <= powl(2, scale) && currentY > powl(2, scale)) {
                Index += powl(4, scale);
                findIndex(currentX, currentY - powl(2, scale));
            }
        }
    }
}

