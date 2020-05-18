#include <stdio.h>
#include <cmath>

struct Complex {
    double real;
    double imag;
};
void mul(Complex&r, Complex&a, Complex&b) {
    r.real = a.real*b.real - a.imag*b.imag;
    r.imag = a.real*b.imag + a.imag*b.real;
}
void add(Complex&r, Complex&a, Complex&b) {
    r.real = a.real + b.real;
    r.imag = a.imag + b.imag;
}
void sub(Complex&r, Complex&a, Complex&b) {
    r.real = a.real - b.real;
    r.imag = a.imag - b.imag;
}
const double pi = 3.14159265358979323846l;
const int k_size = 0x0fffff + 1;
Complex co[k_size];
Complex pv[k_size];
Complex* fft(int n, Complex *arr) {
    if(n==1) {
        Complex* result = new Complex[1];
        result[0] = arr[0];
        return result;
    }
    Complex* y = new Complex[n];
    Complex* ec = new Complex[n/2];
    Complex* oc = new Complex[n/2];
    for(int i = 0; i < n/2; i++) {
        ec[i] = arr[2*i];
        oc[i] = arr[2*i+1];
    }
    Complex* epv = fft(n/2, ec);
    Complex* opv = fft(n/2, oc);
    Complex omega;
    for(int i = 0; i < n/2; i++) {
        omega.real = cos(-2*pi*i/n);
        omega.imag = sin(-2*pi*i/n);

        mul(y[i], omega, opv[i]);
        add(y[i], epv[i], y[i]);
        mul(y[i+n/2], omega, opv[i]);
        sub(y[i+n/2], epv[i], y[i+n/2]);
    }
    // delete [] y;
    delete [] ec;
    delete [] oc;
    delete [] epv;
    delete [] opv;
    return y;
}

Complex* ifft(int n, Complex *arr) {
    if(n==1) {
        Complex* result = new Complex[1];
        result[0] = arr[0];
        return result;
    }
    Complex* y = new Complex[n];
    Complex* ec = new Complex[n/2];
    Complex* oc = new Complex[n/2];
    for(int i = 0; i < n/2; i++) {
        ec[i] = arr[2*i];
        oc[i] = arr[2*i+1];
    }
    Complex* epv = ifft(n/2, ec);
    Complex* opv = ifft(n/2, oc);
    Complex omega;
    for(int i = 0; i < n/2; i++) {
        omega.real = cos(2*pi*i/n);
        omega.imag = sin(2*pi*i/n);

        mul(y[i], omega, opv[i]);
        add(y[i], epv[i], y[i]);
        mul(y[i+n/2], omega, opv[i]);
        sub(y[i+n/2], epv[i], y[i+n/2]);
    }
    // delete [] y;
    delete [] ec;
    delete [] oc;
    delete [] epv;
    delete [] opv;
    return y;
}

int n, p, zero_cnt;
Complex cco[2*k_size];
long long etr[k_size];
long long rte[k_size];
long long result[k_size];
long long t;

bool isPrimitiveRoot(long long p, long long r) {
    etr[0] = 1;
    for(int i = 1; i < p-1; i++) {
        etr[i] = (etr[i-1] * r) % p;
        rte[etr[i]] = i;
        if(etr[i] == 1) {
            return false;
        }
    }
    etr[p-1] = (etr[p-2]*r)%p;
    if(etr[p-1] != 1) return false;
    rte[etr[p-1]] = p-1;
    return true;
}

long long myPow(long long base, long long exp) {
    long long result = 1;
    for(int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int main(void) {
    scanf("%d %d", &n, &p);
    zero_cnt = 0;
    long long len = myPow(2, ceil(log2(p)));
    int temp;
    int cnt = 2;
    while(true) {
        if(isPrimitiveRoot(p, cnt)) break;
        cnt++;
    }
    for(int i = 0; i < p; i++) result[i] = 0;
    for(int i = 0; i < 2*len; i++) {
        co[i].real = 0;
        co[i].imag = 0;
    }
    for(int i = 0; i < 2*len; i++) {
        cco[i].real = 0;
        cco[i].imag = 0;
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &temp);
        temp = temp % p;
        if(temp == 0) {
            zero_cnt++;
            continue;
        }
        co[rte[temp]].real += 1;
        // co[i].imag = 0;
    }
    result[0] = n*n-(n-zero_cnt)*(n-zero_cnt);
    
    Complex *A = fft(2*len, co);
    // Complex tc1;
    for(int i = 0; i < 2*len; i++) {
        mul(cco[i], A[i], A[i]);
    }
    delete [] A;
    // len = myPow(2, ceil(log2(2*p-1)));
    A = ifft(2*len, cco);
    for(int i = 2; i <= 2*p-2; i++) {
        // printf("%.1f ", A[i].real);
        t = (A[i].real/len/2)+0.5l;
        result[etr[i%(p-1)]] += t;
    }
    // printf("\n");
    for(int i = 0; i < p; i++) {
        printf("%lld\n", result[i]);
    }
}

