#include <algorithm>
#include <cinttypes>
#include <cstdio>
#include <cstring>
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
int getOp() {
    int c;
    do
        c = getchar();
    while(c != 'C' && c != 'Q');
    return c;
}
const int size = 30005, maxb = 128, inv2 = 5004,
          mod = 10007;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int N;
struct Seq {
    int A[maxb];
    void FWT() {
        for(int i = 2; i <= N; i <<= 1) {
            int m = i >> 1;
            for(int j = 0; j < N; j += i)
                for(int k = 0; k < m; ++k) {
                    int &x = A[j + k],
                        &y = A[j + k + m], t = y;
                    y = sub(x, t);
                    x = add(x, t);
                }
        }
    }
    void IFWT() {
        for(int i = 2; i <= N; i <<= 1) {
            int m = i >> 1;
            for(int j = 0; j < N; j += i)
                for(int k = 0; k < m; ++k) {
                    int &x = A[j + k],
                        &y = A[j + k + m], t = y;
                    y = sub(x, t) * inv2 % mod;
                    x = add(x, t) * inv2 % mod;
                }
        }
    }
    Seq operator*(const Seq& rhs) const {
        Seq res;
        for(int i = 0; i < N; ++i)
            res.A[i] = A[i] * rhs.A[i] % mod;
        return res;
    }
    Seq operator+(const Seq& rhs) const {
        Seq res;
        for(int i = 0; i < N; ++i)
            res.A[i] = add(A[i], rhs.A[i]);
        return res;
    }
    Seq operator-(const Seq& rhs) const {
        Seq res;
        for(int i = 0; i < N; ++i)
            res.A[i] = sub(A[i], rhs.A[i]);
        return res;
    }
};
Seq I;
struct Mat {
    Seq A10, A11, A20, A21;
    Mat() {}
    Mat(const Seq& A10, const Seq& A11, const Seq& A20,
        const Seq& A21)
        : A10(A10), A11(A11), A20(A20), A21(A21) {}
    Mat operator*(const Mat& rhs) const {
        return Mat(A10 + A11 * rhs.A10, A11 * rhs.A11,
                   A20 + A21 * rhs.A10 + rhs.A20,
                   A21 * rhs.A11 + rhs.A21);
    }
    Seq getS() const {
        return A10 + A20;
    }
};
struct Node {
    Mat mat, mul;
    int l, r, p;
} T[size];
bool isRoot(int u) {
    int p = T[u].p;
    return T[p].l != u && T[p].r != u;
}
#define ls T[u].l
#define rs T[u].r
void update(int u) {
    T[u].mul = T[u].mat;
    if(ls)
        T[u].mul = T[ls].mul * T[u].mul;
    if(rs)
        T[u].mul = T[u].mul * T[rs].mul;
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
int son[size], w[size];
int buildTree(int u, int p) {
    int siz = 1, msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(p != v) {
            int vsiz = buildTree(v, u);
            siz += vsiz;
            if(vsiz > msiz)
                son[u] = v, msiz = vsiz;
        }
    }
    w[u] = siz - msiz;
    return siz;
}
int ch[size], sw[size];
int buildChainImpl(int l, int r) {
    if(l > r)
        return 0;
    int tot = sw[r] - sw[l - 1], csum = 0;
    for(int i = l; i <= r; ++i) {
        int u = ch[i];
        csum += w[u];
        if(2 * csum >= tot) {
            ls = buildChainImpl(l, i - 1);
            rs = buildChainImpl(i + 1, r);
            T[ls].p = T[rs].p = u;
            update(u);
            return u;
        }
    }
    return -1;
}
bool flag[size];
int id[size], L[size], R[size], icnt = 0;
Seq IS[size * 2];
int buildChain(int u) {
    for(int i = u; i; i = son[i])
        flag[i] = true;
    for(int i = u; i; i = son[i]) {
        std::vector<int> chs;
        for(int j = last[i]; j; j = E[j].nxt) {
            int v = E[j].to;
            if(!flag[v]) {
                int vid = buildChain(v);
                T[vid].p = i;
                chs.push_back(vid);
            }
        }
        L[i] = ++icnt;
        IS[icnt] = T[i].mat.A10;
        for(int j = 0; j < chs.size(); ++j) {
            int v = chs[j];
            id[v] = ++icnt;
            IS[icnt] = T[v].mul.A10 + I;
            T[i].mat.A10 = T[i].mat.A10 +
                T[i].mat.A10 * T[v].mul.A10;
            T[i].mat.A20 =
                T[i].mat.A20 + T[v].mul.getS();
        }
        T[i].mat.A11 = T[i].mat.A10;
        R[i] = icnt;
    }
    int csiz = 0;
    for(int i = u; i; i = son[i]) {
        ch[++csiz] = i;
        sw[csiz] = sw[csiz - 1] + w[i];
    }
    return buildChainImpl(1, csiz);
}
Seq X[size << 3];
void updateSeg(int id) {
    X[id] = X[id << 1] * X[id << 1 | 1];
}
void build(int l, int r, int id) {
    if(l == r)
        X[id] = IS[l];
    else {
        int m = (l + r) >> 1;
        build(l, m, id << 1);
        build(m + 1, r, id << 1 | 1);
        updateSeg(id);
    }
}
void modify(int l, int r, int id, int p,
            const Seq& s) {
    if(l == r)
        X[id] = s;
    else {
        int m = (l + r) >> 1;
        if(p <= m)
            modify(l, m, id << 1, p, s);
        else
            modify(m + 1, r, id << 1 | 1, p, s);
        updateSeg(id);
    }
}
Seq query(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        return X[id];
    else {
        int m = (l + r) >> 1;
        if(nl <= m && m < nr) {
            Seq lres = query(l, m, id << 1, nl, nr),
                rres = query(m + 1, r, id << 1 | 1, nl,
                             nr);
            return lres * rres;
        }
        if(nl <= m)
            return query(l, m, id << 1, nl, nr);
        return query(m + 1, r, id << 1 | 1, nl, nr);
    }
}
void updateMat(int u) {
    while(u) {
        int p = T[u].p;
        if(p && isRoot(u)) {
            Seq old = T[u].mul.getS();
            update(u);
            modify(1, icnt, 1, id[u],
                   T[u].mul.A10 + I);
            T[p].mat.A10 = T[p].mat.A11 =
                query(1, icnt, 1, L[p], R[p]);
            Seq cur = T[u].mul.getS();
            T[p].mat.A20 = T[p].mat.A20 + cur - old;
        } else
            update(u);
        u = p;
    }
}
int val[size];
int main() {
    int n = read();
    N = read();
    memset(&I, 0, sizeof(I));
    I.A[0] = 1;
    I.FWT();
    for(int i = 1; i <= n; ++i) {
        val[i] = read();
        Seq x;
        memset(&x, 0, sizeof(int) * N);
        x.A[val[i]] = 1;
        x.FWT();
        T[i].mat.A10 = T[i].mat.A11 = x;
        T[i].mat.A21 = I;
    }
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    buildTree(1, 0);
    int root = buildChain(1);
    build(1, icnt, 1);
    int q = read();
    Seq cres = T[root].mul.getS();
    bool lazy = true;
    for(int t = 1; t <= q; ++t) {
        if(getOp() == 'Q') {
            if(lazy)
                lazy = false, cres.IFWT();
            printf("%" PRId32 "\n", cres.A[read()]);
        } else {
            int u = read();
            int v = read();
            val[u] = v;
            Seq z;
            memset(&z, 0, sizeof(int) * N);
            z.A[v] = 1;
            z.FWT();
            modify(1, icnt, 1, L[u], z);
            T[u].mat.A10 = T[u].mat.A11 =
                query(1, icnt, 1, L[u], R[u]);
            updateMat(u);
            cres = T[root].mul.getS();
            lazy = true;
        }
    }
    return 0;
}
