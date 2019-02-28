#include <cstdio>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 50005;
typedef long long Int64;
Int64 A[size], dA[size], dB[size];
Int64 deltaA(int a, int b) {
    return dA[a] - dA[b];
}
Int64 deltaB(int a, int b) {
    return dB[a] - dB[b];
}
int q[size];
int main() {
    int n = read();
    Int64 l = read() + 1;
    for(int i = 1; i <= n; ++i)
        A[i] = A[i - 1] + read() + 1;
    int b = 1, e = 1;
    q[1] = 0;
    dA[0] = l * l, dB[0] = -2 * l;
    Int64 dpv;
    for(int i = 1; i <= n; ++i) {
        while(b + 1 <= e &&
              -A[i] * deltaB(q[b], q[b + 1]) <=
                  deltaA(q[b], q[b + 1]))
            ++b;
        int t = q[b];
        dpv = dA[t] + (dB[t] + A[i]) * A[i];
        Int64 c = A[i] + l;
        dA[i] = dpv + c * c;
        dB[i] = -2 * c;
        while(b + 1 <= e &&
              deltaA(q[e - 1], q[e]) *
                      deltaB(q[e], i) <=
                  deltaA(q[e], i) *
                      deltaB(q[e - 1], q[e]))
            --e;
        q[++e] = i;
    }
    printf("%lld\n", dpv);
    return 0;
}
