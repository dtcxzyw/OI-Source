#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
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
const int size = 1 << 16, maxn = 50005,
          mod = 998244353;
typedef long long Int64;
#define asInt64 static_cast<Int64>
const Int64 end =
    LLONG_MAX - asInt64(mod - 1) * (mod - 1);
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int tot, root[size], invR[size];
void init(int n) {
    tot = n;
    Int64 base = powm(3, (mod - 1) / n);
    Int64 invBase = powm(base, mod - 2);
    root[0] = invR[0] = 1;
    for(int i = 1; i < n; ++i)
        root[i] = root[i - 1] * base % mod;
    for(int i = 1; i < n; ++i)
        invR[i] = invR[i - 1] * invBase % mod;
}
void NTT(int n, int* A, const int* w) {
    for(int i = 0, j = 0; i < n; ++i) {
        if(i < j)
            std::swap(A[i], A[j]);
        for(int l = n >> 1; (j ^= l) < l; l >>= 1)
            ;
    }
    for(int i = 2; i <= n; i <<= 1) {
        int m = i >> 1, fac = tot / i;
        for(int j = 0; j < n; j += i)
            for(int k = 0; k < m; ++k) {
                int &x = A[j + k], &y = A[j + k + m];
                int t = asInt64(w[fac * k]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}

void reset(int* A, int n, int rn) {
    memset(A + rn, 0, sizeof(int) * (n - rn));
}
int getSize(int n) {
    int p = 1;
    while(p < n)
        p <<= 1;
    return p;
}
const int k = 200;
int C[k];
int* mul(int beg, int rn, int* A, int* B) {
    if(rn < k) {
        for(int i = beg; i < rn; ++i) {
            Int64 sum = 0;
            for(int j = 0; j <= i; ++j) {
                sum += asInt64(A[j]) * B[i - j];
                if(sum > end)
                    sum %= mod;
            }
            C[i] = sum % mod;
        }
        return C;
    } else {
        int n = getSize(rn);
        reset(A, n, rn);
        NTT(n, A, root);
        reset(B, n, rn);
        NTT(n, B, root);
        for(int i = 0; i < n; ++i)
            A[i] = asInt64(A[i]) * B[i] % mod;
        NTT(n, A, invR);
        Int64 div = powm(n, mod - 2);
        for(int i = beg; i < rn; ++i)
            A[i] = A[i] * div % mod;
        return A;
    }
}
int f[maxn], A[size], B[size];
void solve(int l, int r) {
    if(l == r)
        f[l] =
            (f[l] + asInt64(l - 1) * f[l - 1]) % mod;
    else {
        int m = (l + r) >> 1;
        solve(l, m);
        {
            int siz = std::min(m, r - l);
            int end = m - l + siz + 1;
            for(int i = l; i <= m; ++i)
                A[i - l] = asInt64(i - 1) * f[i] % mod;
            reset(A, end, m - l + 1);
            B[0] = B[1] = 0;
            for(int i = 2; i <= siz; ++i)
                B[i] = f[i];
            reset(B, end, siz + 1);
            int* C = mul(m - l + 1, end, A, B);
            for(int i = m + 1; i <= r && i - l < end;
                ++i)
                f[i] = add(f[i], C[i - l]);
        }
        {
            int siz = std::min(l - 1, r - l);
            int end = m - l + siz + 1;
            for(int i = l; i <= m; ++i)
                A[i - l] = f[i];
            reset(A, end, m - l + 1);
            B[0] = B[1] = 0;
            for(int i = 2; i <= siz; ++i)
                B[i] = asInt64(i - 1) * f[i] % mod;
            reset(B, end, siz + 1);
            int* C = mul(m - l + 1, end, A, B);
            for(int i = m + 1; i <= r && i - l < end;
                ++i)
                f[i] = add(f[i], C[i - l]);
        }
        solve(m + 1, r);
    }
}
void pre(int n) {
    f[0] = 1, f[1] = 2;
    if(n >= 3) {
        init(getSize(n));
        solve(2, n - 1);
    }
}
int L[maxn], st[maxn], top;
int foo(int n) {
    for(int i = 1; i <= n; ++i)
        L[i] = read();
    if(L[n] != n)
        return 0;
    Int64 res = 1;
    top = 0;
    for(int i = 1; i <= n; ++i) {
        int cnt = 0, cl = i - L[i];
        while(top && st[top] > cl) {
            int x = st[top], lx = x - L[x];
            if(lx >= cl)
                --top, ++cnt;
            else
                return 0;
        }
        st[++top] = i;
        res = res * f[cnt] % mod;
    }
    return res;
}
int main() {
    int t = read();
    int n = read();
    pre(n);
    while(t--)
        printf("%d\n", foo(n));
    return 0;
}
