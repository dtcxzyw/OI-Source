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
typedef long long Int64;
#define asInt64 static_cast<Int64>
const Int64 end = 1LL << 62;
const int size = 50005;
int A[size], C[230];
Int64 B[230];
int main() {
    int n = read();
    int bc = sqrt(n);
    for(int i = 1; i <= n; ++i)
        B[i / bc] += A[i] = read();
    for(int i = 1; i <= n; ++i) {
        int op = read();
        int l = read();
        int r = read();
        int c = read();
        int lb = l / bc, rb = r / bc;
        if(op) {
            Int64 ans = 0;
            ++c;
            if(lb == rb) {
                for(int i = l; i <= r; ++i)
                    ans += A[i];
                ans += asInt64(r - l + 1) * C[lb];
            } else {
                int bb = (l - 1) / bc + 1,
                    eb = (r + 1) / bc - 1;
                int bbp = bb * bc, ebp = (eb + 1) * bc;
                for(int i = bb; i <= eb; ++i) {
                    ans += B[i];
                    if(ans >= end)
                        ans %= c;
                }
                for(int i = l; i < bbp; ++i)
                    ans += A[i];
                if(l < bbp)
                    ans += asInt64(bbp - l) * C[lb];
                if(ans >= end)
                    ans %= c;
                for(int i = ebp; i <= r; ++i)
                    ans += A[i];
                if(ebp <= r)
                    ans +=
                        asInt64(r - ebp + 1) * C[rb];
            }
            printf("%lld\n", ans % c);
        } else {
            if(lb == rb) {
                for(int i = l; i <= r; ++i)
                    A[i] += c;
                B[lb] += asInt64(r - l + 1) * c;
            } else {
                int bb = (l - 1) / bc + 1,
                    eb = (r + 1) / bc - 1;
                int bbp = bb * bc, ebp = (eb + 1) * bc;
                for(int i = bb; i <= eb; ++i) {
                    int bp = std::max(1, i * bc),
                        ep = std::min((i + 1) * bc - 1,
                                      n);
                    B[i] += asInt64(ep - bp + 1) * c;
                    C[i] += c;
                }
                for(int i = l; i < bbp; ++i)
                    A[i] += c;
                if(l < bbp)
                    B[lb] += asInt64(bbp - l) * c;
                for(int i = ebp; i <= r; ++i)
                    A[i] += c;
                if(ebp <= r)
                    B[rb] += asInt64(r - ebp + 1) * c;
            }
        }
    }
    return 0;
}
