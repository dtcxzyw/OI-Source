#include <algorithm>
#include <cstdio>
#include <vector>
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
const int size = 3005, mod = 1000000007;
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 inv(Int64 a) {
    Int64 res = 1;
    int k = mod - 2;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
std::vector<int> A, B;
int S[size];
int main() {
    freopen("BM-in.txt", "r", stdin);
    int n = read();
    int ld = 1, lp = 0;
    A.push_back(mod - 1);
    B.push_back(mod - 1);
    for(int i = 1; i <= n; ++i) {
        S[i] = read();
        int val = 0;
        for(int j = 0; j < A.size(); ++j)
            val =
                (val + asInt64(A[j]) * S[i - j]) % mod;
        if(val) {
            int off = i - lp;
            int cd =
                std::max(A.size(), B.size() + off);
            B.resize(cd);
            Int64 fac = asInt64(val) * ld % mod;
            if(fac)
                fac = mod - fac;
            for(int j = cd - 1; j >= 0; --j) {
                int av = (j < A.size() ? A[j] : 0);
                int bv = (j >= off ? B[j - off] : 0);
                B[j] = (av + fac * bv) % mod;
            }
            A.swap(B);
            while(A.back() == 0)
                A.pop_back();
            lp = i, ld = inv(val);
        }
    }
    for(int i = A.size(); i <= n; ++i) {
        int val = 0;
        for(int j = 0; j < A.size(); ++j)
            val =
                (val + asInt64(A[j]) * S[i - j]) % mod;
        if(val != 0)
            throw;
    }
    printf("%d\n", A.size() - 1);
    Int64 k = asInt64(mod - 1) * inv(A[0]) % mod;
    for(int i = 0; i < A.size(); ++i)
        A[i] = A[i] * k % mod;
    for(int i = 1; i < A.size(); ++i)
        printf("%d ", A[i]);
    return 0;
}
