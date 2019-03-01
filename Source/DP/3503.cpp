#include <algorithm>
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
typedef long long Int64;
const int size = 1000005;
int A[size], qA[size], qB[size];
Int64 S[size];
int main() {
    int n = read();
    int m = read();
    Int64 sum = 0;
    for(int i = 1; i <= n; ++i) {
        int x = read();
        A[i] = x;
        sum += x;
    }
    for(int t = 0; t < m; ++t) {
        Int64 k = read();
        if(k * n <= sum) {
            printf("%d ", n);
            continue;
        }
        for(int i = 1; i <= n; ++i)
            S[i] = S[i - 1] + A[i] - k;
        int topA = 0, topB = 0;
        for(int i = 1; i <= n; ++i) {
            Int64 cur = S[i];
            if(S[qA[topA]] > cur)
                qA[++topA] = i;
            while(topB && S[qB[topB]] <= cur)
                --topB;
            qB[++topB] = i;
        }
        int res = 0;
        for(int i = 1, j = 0; i <= topB; ++i) {
            int r = qB[i];
            Int64 cur = S[r];
            while(S[qA[j]] > cur)
                ++j;
            res = std::max(res, r - qA[j]);
        }
        printf("%d ", res);
    }
    return 0;
}
