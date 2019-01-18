#include <algorithm>
#include <cmath>
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
const int size = 50005;
int A[size], B[230], C[230], LUT[10005];
void doSqrt(int i, int ib) {
    bool flag = A[i] > 1;
    B[ib] -= A[i];
    A[i] = LUT[A[i]];
    B[ib] += A[i];
    if(flag && A[i] <= 1)
        --C[ib];
}
int main() {
    int n = read();
    int bc = sqrt(n);
    int maxb = n / bc;
    for(int i = 0; i <= maxb; ++i) {
        int bp = std::max(1, i * bc),
            ep = std::min((i + 1) * bc - 1, n);
        C[i] = ep - bp + 1;
    }
    for(int i = 1; i <= 10000; ++i)
        LUT[i] = sqrt(i);
    for(int i = 1; i <= n; ++i) {
        int x = read();
        A[i] = x;
        B[i / bc] += x;
        C[i / bc] -= (x <= 1);
    }
    for(int i = 1; i <= n; ++i) {
        int op = read();
        int l = read();
        int r = read();
        int c = read();
        int lb = l / bc, rb = r / bc;
        if(op) {
            int ans = 0;
            if(lb == rb) {
                for(int i = l; i <= r; ++i)
                    ans += A[i];
            } else {
                int bb = (l - 1) / bc + 1,
                    eb = (r + 1) / bc - 1;
                int bbp = bb * bc, ebp = (eb + 1) * bc;
                for(int i = bb; i <= eb; ++i)
                    ans += B[i];
                for(int i = l; i < bbp; ++i)
                    ans += A[i];
                for(int i = ebp; i <= r; ++i)
                    ans += A[i];
            }
            printf("%d\n", ans);
        } else {
            if(lb == rb) {
                if(C[lb])
                    for(int i = l; i <= r; ++i)
                        doSqrt(i, lb);
            } else {
                int bb = (l - 1) / bc + 1,
                    eb = (r + 1) / bc - 1;
                int bbp = bb * bc, ebp = (eb + 1) * bc;
                for(int i = bb; i <= eb; ++i)
                    if(C[i]) {
                        int bp = std::max(1, i * bc),
                            ep = std::min(
                                (i + 1) * bc - 1, n);
                        for(int j = bp; j <= ep; ++j)
                            doSqrt(j, i);
                    }
                if(C[lb])
                    for(int i = l; i < bbp; ++i)
                        doSqrt(i, lb);
                if(C[rb])
                    for(int i = ebp; i <= r; ++i)
                        doSqrt(i, rb);
            }
        }
    }
    return 0;
}
