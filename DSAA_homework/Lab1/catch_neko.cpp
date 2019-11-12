#include <stdio.h>
#include <windows.h>


long long binarySearch(long long start, long long end);

long long position[2][100001];
long long eveX, eveY, N;

long long absolute(long long n) {
    if(n > 0) {
        return n;
    }else {
        return -n;
    }
}

int main(void) {
    scanf("%lld %lld", &eveX, &eveY);
    scanf("%lld %lld", &position[0][0], &position[1][0]);
//    scanf("%lld\n", &N);  //get rid of \n

    scanf("%lld", &N);
    scanf("%c");

    for(int i = 1; i <= N; i++) {
        char temp;
        scanf("%c", &temp);  //use scanf("%s", ${char_array}) would be better
        position[0][i] = position[0][i - 1];
        position[1][i] = position[1][i - 1];
        switch(temp) {
            case 'U': {
                position[1][i]++;
                break;
            }case 'D': {
                position[1][i]--;
                break;
            }case 'L': {
                position[0][i]--;
                break;
            }case 'R': {
                position[0][i]++;
                break;
            }
        }
    }
    //3e14 the upper bound
    long long currentX = ((long long) 3e14) / N * (position[0][N] - position[0][0]) + position[0][((long long) 3e14) % N];
    long long currentY = ((long long) 3e14)/ N * (position[1][N] - position[1][0]) + position[1][((long long) 3e14) % N];
    long long distance = absolute(currentX - eveX) + absolute(currentY - eveY);
    
    if((eveX == position[0][0]) && (eveY == position[1][0])) {
        printf("%d", 0);
    }else if(distance > ((long long) 3e14)) {
        printf("%d", -1);
    }else {
        printf("%lld", binarySearch(0, (long long) 3e14));
    }
    system("pause");
}

long long binarySearch(long long start, long long end) {
    long long mid;
    long long currentX, currentY;
    long long distance;

    while(true) {
        mid = (start + end) / 2;
        //currentPosition = currentCycles * displacementPerCycle + remainingPart + originPosition
        currentX = (mid / N) * (position[0][N] - position[0][0]) + position[0][mid % N];
        currentY = (mid / N) * (position[1][N] - position[1][0]) + position[1][mid % N];
        distance = absolute(currentX - eveX) + absolute(currentY - eveY);

        if((start + 1) == end) {
            return end;
        }

        if(mid >= distance) {
            //neko can be caught
            end = mid;
        }else if(mid < distance) {
            //neko won't be caught
            start = mid;
        }
    }
}