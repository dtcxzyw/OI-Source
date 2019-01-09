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
const int size = 25, maxs = 1 << 18, mod = 998244353;
typedef long long Int64;
#define asInt64 static_cast<Int64>
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int inv[size];
struct Info {
    int k, b;
    Info() {}
    Info(int k, int b) : k(k), b(b) {}
    Info operator+(const Info& rhs) const {
        return Info(add(k, rhs.k), add(b, rhs.b));
    }
    Info operator*(Int64 fac) const {
        return Info(k * fac % mod, b * fac % mod);
    }
};
int dst;
Info DFS(int u, int p) {
    if(dst & (1 << (u - 1)))
        return Info(0, 0);
    Info sum(0, 0);
    int lcnt = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p)
            sum = sum + DFS(v, u);
        ++lcnt;
    }
    Int64 ilc = inv[lcnt];
    Info res;
    res.k = ilc;
    res.b = (1 + ilc * sum.b) % mod;
    int fac = (1 - ilc * sum.k) % mod;
    if(fac < 0)
        fac += mod;
    return res * powm(fac, mod - 2);
}
int dp[maxs], x;
int calcE(int st) {
    int& res = dp[st];
    if(res == -1) {
        dst = st;
        res = DFS(x, 0).b;
    }
    return res;
}
bool bc[maxs];
int main() {
    int n = read();
    int q = read();
    x = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    inv[1] = 1;
    for(int i = 2; i < n; ++i)
        inv[i] = asInt64(mod - mod / i) *
            inv[mod % i] % mod;
    int end = 1 << n;
    memset(dp, -1, sizeof(int) * end);
    for(int i = 1; i < end; ++i)
        bc[i] = bc[i >> 1] ^ (i & 1);
    while(q--) {
        int k = read(), st = 0;
        while(k--)
            st |= 1 << read();
        st >>= 1;
        int sum = 0;
        for(int i = st; i; i = st & (i - 1)) {
            int val = calcE(i);
            if(bc[i])
                sum = add(sum, val);
            else
                sum = sub(sum, val);
        }
        printf("%d\n", sum);
    }
    return 0;
}
