#include <cstdio>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 1000005;
typedef long long Int64;
Int64 S[size], dA[size], dB[size];
Int64 deltaA(int i, int j) {
    return dA[i] - dA[j];
}
Int64 deltaB(int i, int j) {
    return dB[i] - dB[j];
}
int q[size];
int main() {
    int n = read();
    Int64 A = read(), B = read(), C = read();
    for(int i = 1; i <= n; ++i)
        S[i] = S[i - 1] + read();
    int b = 1, e = 1;
    q[1] = 0, dA[0] = C;
    Int64 dpv;
    for(int i = 1; i <= n; ++i) {
        while(b + 1 <= e &&
              -S[i] * deltaB(q[b], q[b + 1]) >=
                  deltaA(q[b], q[b + 1]))
            ++b;
        int t = q[b];
        dpv = dA[t] + (dB[t] + A * S[i] + B) * S[i];
        dA[i] = dpv + (A * S[i] - B) * S[i] + C;
        dB[i] = -2 * A * S[i];
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
