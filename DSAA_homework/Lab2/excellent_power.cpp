#include <stdio.h>

int n, p, q;
int array[2][200000];
long long result[200000];
long long sum = 0;

void merge(int ,int);

int main(void) {
    scanf("%d %d %d", &n, &p, &q);

    for(int i = 0; i < n; i++) {
        scanf("%d %d", &array[0][i], &array[1][i]);
    }
    long long spell1 = 1;
    for(int i = 0; i < p; i++) {
        spell1 *= 2;
    }

    merge(0, n - 1);

    for(int i = 0; i < n; i++) {
        if(i < q) {
            if(array[0][i] > array[1][i]){
                sum += array[0][i];
            }else {
                sum += array[1][i];
            }
        }else {
            sum += array[1][i];
        }
    }
    if(q == 0) {
        printf("%lld", sum);
        return 0;
    }

    long long max = 0;
    for(int i = 0; i < n; i++) {
        long long addition = spell1 * (long long) array[0][i];
        if(addition < array[1][i]){
            //double p times of ith soldier's hp still less than its attack
            result[i] = sum;
        }else {
            if(i < q) {
                //among the first q soldiers
                if(array[0][i] > array[1][i]) {
                    //if the ith solider with spell2
                    result[i] = sum - array[0][i] + array[0][i] * spell1;
                }else {
                    //not with spell2, eliminate its attack, add p times of its hp
                    result[i] = sum - array[1][i] + array[0][i] * spell1;
                }
            }else {
                if(array[0][q - 1] > array[1][q - 1]) {
                    //q - 1th soldier spelled, no remaining spell2
                    //spell ith soldier, cancel the spell to q th soldier
                    result[i] = sum - array[1][i] + array[0][i] * spell1 - array[0][q - 1] + array[1][q - 1];
                }else {
                    //q-1th soldier not spelled, remains at least one spell2
                    result[i] = sum - array[1][i] + array[0][i] * spell1;
                }
            }
        }
        if(result[i] > max) {
            max = result[i];
        }
    }

    printf("%lld\n", max);
}

void merge(int start, int end) {
    if(start == end) {
        return;
    }

    int mid = (end + start) / 2;
    merge(start, mid);
    merge(mid + 1, end);
    int leftSize = mid -start + 1;
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
        if((leftCounter != leftSize) && ((rightCounter == rightSize || ((left[0][leftCounter] - left[1][leftCounter])  > (right[0][rightCounter] - right[1][rightCounter]))))) {
            array[0][i] = left[0][leftCounter];
            array[1][i] = left[1][leftCounter++];
        }else{
            array[0][i] = right[0][rightCounter];
            array[1][i] = right[1][rightCounter++];
        }
    }
}
