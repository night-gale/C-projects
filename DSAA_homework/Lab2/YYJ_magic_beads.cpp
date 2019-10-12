#include <stdio.h>

int red[2][100000];
int blue[2][100000];
int T, n;
int rCounter = 0;
int bCounter = 0;
long long sum;

void merge(int array[2][100000], int start, int end, bool);

int main(void) {
    scanf("%d", &T);
    for(int t = 0;  t < T; t++) {
        scanf("%d", &n);
        int tempBlue, tempRed;
        sum = 0;
        long long magic = 0;
        rCounter = 0;
        bCounter = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d %d", &tempBlue, &tempRed);
            if(tempBlue > tempRed) {
                blue[0][bCounter] = tempBlue;
                blue[1][bCounter++] = tempRed;
            }else {
                red[0][rCounter] = tempBlue;
                red[1][rCounter++] = tempRed;
            }
        }
        merge(red, 0, rCounter - 1, true);   //according to blue in ascending order
        merge(blue, 0, bCounter - 1, false);  //according to red in descending order

        // for(int i = 0; i < rCounter; i++) {
        //     printf("%d %d\n", red[0][i], red[1][i]);
        // }
        // for(int j = 0; j < bCounter; j++) {
        //     printf("%d %d\n", blue[0][j], blue[1][j]);
        // }

        //sum represent the amount of red remained
        for(int j = 0; j < rCounter; j++) {
            if(sum < red[0][j]) {
                magic += sum;
                sum = red[1][j];
            }else {
                magic += red[0][j];
                sum += red[1][j] - red[0][j];
            }
        }
        for(int i = 0; i < bCounter; i++) {
            if(sum < blue[0][i]) {
                magic += sum;
                sum = blue[1][i];
            }else {
                magic += blue[0][i];
                sum += blue[1][i] - blue[0][i];
            }
        }
        printf("%lld\n", magic);
    }
}

void merge(int array[2][100000], int start, int end, bool accordingToBlue) {
    if(start >= end) {
        return;
    }

    int mid = (end + start) / 2;
    merge(array, start, mid, accordingToBlue);
    merge(array, mid + 1, end, accordingToBlue);
    int leftSize = mid - start + 1;
    int rightSize = end - mid;
    int left[2][leftSize];
    int right[2][rightSize];
    
     
    for(int i = 0; i < leftSize; i++) {
        left[0][i] = array[0][start + i];
        left[1][i] = array[1][start + i];
    }
    for(int j = 0; j < rightSize; j++) {
        right[0][j] = array[0][mid + j + 1];
        right[1][j] = array[1][mid + j + 1];
    }
    int leftCounter = 0;
    int rightCounter = 0;

    for(int i = start; i <= end; i++) {
        bool flag;
        if(accordingToBlue) {
            flag = left[0][leftCounter] < right[0][rightCounter];
        }else {
            flag = left[1][leftCounter] > right[1][rightCounter];
        }
        if((leftCounter != leftSize) && ((rightCounter == rightSize || flag))) {
            array[1][i] = left[1][leftCounter];
            array[0][i] = left[0][leftCounter++];
        }else{
            array[1][i] = right[1][rightCounter];
            array[0][i] = right[0][rightCounter++];
        }
    }
}