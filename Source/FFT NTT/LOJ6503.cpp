#include <cstdio>
#include <cstring>
#include <queue>
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
const int size = 1 << 18, maxn = 100005, maxm = 20005,
          mod = 998244353;
typedef long long Int64;
#define asInt64 static_cast<Int64>
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
                int t = asInt64(w[k * fac]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
int getSize(int n) {
    int p = 1;
    while(p < n)
        p <<= 1;
    return p;
}
typedef std::vector<int> Poly;
void copyAndDFT(const Poly& A, int* B, int p) {
    memcpy(B, A.data(), sizeof(int) * A.size());
    memset(B + A.size(), 0,
           sizeof(int) * (p - A.size()));
    NTT(p, B, root);
}
int X[size], Y[size];
int mul(Poly& A, Poly& B) {
    int end = A.size() + B.size() - 1;
    int p = getSize(end);
    copyAndDFT(A, X, p);
    copyAndDFT(B, Y, p);
    for(int i = 0; i < p; ++i)
        X[i] = asInt64(X[i]) * Y[i] % mod;
    NTT(p, X, invR);
    Poly res(end), empty;
    memcpy(res.data(), X, sizeof(int) * end);
    res.swap(A);
    B.swap(empty);
    return p;
}
int fac[maxn], invFac[maxn];
Poly A[maxm];
struct Node {
    int id, siz;
    Node(int id, int siz) : id(id), siz(siz) {}
    bool operator<(const Node& rhs) const {
        return siz > rhs.siz;
    }
};
int main() {
    int m = read();
    int n = read();
    int k = read();
    init(getSize(n * 2));
    fac[0] = invFac[0] = invFac[1] = 1;
    for(int i = 1; i <= n; ++i)
        fac[i] = asInt64(fac[i - 1]) * i % mod;
    for(int i = 2; i <= n; ++i)
        invFac[i] = asInt64(mod - mod / i) *
            invFac[mod % i] % mod;
    for(int i = 1; i <= n; ++i)
        invFac[i] =
            asInt64(invFac[i - 1]) * invFac[i] % mod;
    std::priority_queue<Node> heap;
    Int64 mv = 1, dv = 1;
    for(int i = 0; i < m; ++i) {
        int a = read();
        // mv = mv * fac[a] % mod * fac[a - 1] % mod;
        mv = mv * fac[a - 1] % mod;
        A[i].resize(a);
        for(int j = 0; j < a; ++j)
            A[i][j] = asInt64(invFac[j]) *
                invFac[a - j] % mod *
                invFac[a - j - 1] % mod;
        heap.push(Node(i, a));
        // dv = dv * fac[a] % mod;
    }
    while(heap.size() > 1) {
        Node a = heap.top();
        heap.pop();
        Node b = heap.top();
        heap.pop();
        dv = dv * mul(A[a.id], A[b.id]) % mod;
        heap.push(Node(a.id, A[a.id].size()));
    }
    Poly& res = A[heap.top().id];
    Int64 ans = 0;
    for(int i = k; i < res.size(); ++i) {
        Int64 val = asInt64(res[i]) * fac[n - i] %
            mod * fac[i] % mod * invFac[i - k];
        if((i ^ k) & 1)
            ans = (ans - val) % mod;
        else
            ans = (ans + val) % mod;
    }
    dv = dv * fac[k] % mod;
    ans = ans * mv % mod * powm(dv, mod - 2) % mod;
    if(ans < 0)
        ans += mod;
    printf("%lld\n", ans);
    return 0;
}
