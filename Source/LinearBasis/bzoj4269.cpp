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
struct Base {
    int A[35];
    void insert(int x) {
        for(int i = 30; i >= 0; --i)
            if(x & (1 << i)) {
                if(A[i])
                    x ^= A[i];
                else {
                    A[i] = x;
                    return;
                }
            }
    }
    int B[35], bcnt;
    void cook() {
        for(int i = 30; i >= 0; --i) {
            for(int j = i - 1; j >= 0; --j)
                if(A[i] & (1 << j))
                    A[i] ^= A[j];
        }
        for(int i = 0; i <= 30; ++i)
            if(A[i])
                B[bcnt++] = A[i];
    }
    int query(int k) const {
        int res = 0;
        for(int i = 0; i < bcnt; ++i)
            if(k & (1 << i))
                res ^= B[i];
        return res;
    }
} B;
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        B.insert(read());
    B.cook();
    int a = B.query((1 << B.bcnt) - 1);
    int b = B.query((1 << B.bcnt) - 2);
    printf("%d %d\n", a, b);
    return 0;
}
