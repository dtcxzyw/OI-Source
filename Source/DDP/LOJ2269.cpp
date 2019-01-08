#include <algorithm>
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
int getOp() {
    int c;
    do
        c = getchar();
    while(c < 'A' || c > 'Z');
    return c;
}
typedef short Int16;
#define asInt static_cast<Int16>
const int size = 30005, maxb = 128, inv2 = 5004;
const Int16 mod = 10007;
Int16 add(Int16 a, Int16 b) {
    a += b;
    return a < mod ? a : a - mod;
}
Int16 sub(Int16 a, Int16 b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int N, rev[maxb];
struct Seq {
    Int16 A[maxb];
    void FWT() {
        for(int i = 0; i < N; ++i)
            if(i < rev[i])
                std::swap(A[i], A[rev[i]]);
        for(int i = 2; i <= N; i <<= 1) {
            int m = i >> 1;
            for(int j = 0; j < N; j += i)
                for(int k = 0; k < m; ++k) {
                    Int16 &x = A[j + k],
                          &y = A[j + k + m], t = y;
                    y = sub(x, t);
                    x = add(x, t);
                }
        }
    }
    void IFWT() {
        for(int i = 0; i < N; ++i)
            if(i < rev[i])
                std::swap(A[i], A[rev[i]]);
        for(int i = 2; i <= N; i <<= 1) {
            int m = i >> 1;
            for(int j = 0; j < N; j += i)
                for(int k = 0; k < m; ++k) {
                    Int16 &x = A[j + k],
                          &y = A[j + k + m], t = y;
                    y = sub(x, t) * inv2 % mod;
                    x = add(x, t) * inv2 % mod;
                }
        }
    }
    Seq operator*(const Seq& rhs) const {
        Seq res;
        for(int i = 0; i < N; ++i)
            res.A[i] = asInt(A[i]) * rhs.A[i] % mod;
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
struct Mat {
    Seq A[2][2];
    Seq* operator[](int id) {
        return A[id];
    }
    const Seq* operator[](int id) const {
        return A[id];
    }
    Mat operator*(const Mat& rhs) const {
        Mat res;
        res[0][0] = rhs[0][0] + A[0][0] * rhs[1][0];
        res[0][1] =
            rhs[0][1] + A[0][0] * rhs[1][1] + A[0][1];
        res[1][0] = A[1][0] * rhs[1][0];
        res[1][1] = A[1][0] * rhs[1][1] + A[1][1];
        return res;
    }
    Seq getRes() const {
        Seq res = A[0][1];
        res.IFWT();
        return res;
    }
};
struct Node {
    int ls, rs;
    Mat mat, mul;
} T[size];
int fa[size];
bool isRoot(int u) {
    int p = fa[u];
    return T[p].ls != u && T[p].rs != u;
}
#define ls T[u].ls
#define rs T[u].rs
void update(int u) {
    if(ls && rs)
        T[u].mul = T[ls].mul * T[u].mat * T[rs].mul;
    else if(ls)
        T[u].mul = T[ls].mul * T[u].mat;
    else if(rs)
        T[u].mul = T[u].mat * T[rs].mul;
    else
        T[u].mul = T[u].mat;
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
            fa[ls] = fa[rs] = u;
            update(u);
            return u;
        }
    }
    return -1;
}
bool flag[size];
int buildChain(int u) {
    for(int i = u; i; i = son[i])
        flag[i] = true;
    for(int i = u; i; i = son[i])
        for(int j = last[i]; j; j = E[j].nxt) {
            int v = E[j].to;
            if(!flag[v]) {
                int p = buildChain(v);
                Seq w =
                    T[u].mat[1][1] * T[p].mul[1][1];
                T[u].mat[0][0] = T[u].mat[1][0] =
                    T[u].mat[1][1] =
                        T[u].mat[1][1] + w;
                T[u].mat[0][1] = T[u].mat[0][1] +
                    T[p].mul[0][1] + w;
            }
        }
    int csiz = 0;
    for(int i = u; i; i = son[i]) {
        ch[++csiz] = i;
        sw[csiz] = sw[csiz - 1] + w[i];
    }
    return buildChainImpl(1, csiz);
}
void setF(int u, const Seq& f) {
    T[u].mat[0][1] = f;
}
void setG(int u, const Seq& g) {
    T[u].mat[0][0] = T[u].mat[1][0] = T[u].mat[1][1] =
        g;
}
Seq inv(const Seq& s) {}
void updateMat(int u) {
    while(u) {
        int p = fa[u];
        if(p && isRoot(u)) {
            {
                Seq x = T[u].mul[1][1];
                x.A[0] = add(x.A[0], 1);
                setG(p, T[p].mat[1][1] * inv(x));
                setF(p, T[p].mat[0][1] -
                         T[u].mul[0][1] -
                         T[p].mat[1][1] *
                             T[u].mul[1][1]);
            }
            update(u);
            {
                Seq w =
                    T[u].mul[1][1] * T[p].mat[1][1];
                setG(p, T[p].mat[1][1] + w);
                setF(p, T[p].mat[0][1] +
                         T[u].mul[0][1] + w);
            }
        } else
            update(u);
        u = p;
    }
}
int val[size];
int main() {
    int n = read();
    N = read();
    for(int i = 0, j = 0; i < N; ++i) {
        rev[i] = j;
        for(int l = N >> 1; (j ^= l) < l; l >>= 1)
            ;
    }
    for(int i = 1; i <= n; ++i) {
        val[i] = read();
        Seq x;
        memset(&x, 0, sizeof(x));
        x.A[val[i]] = 1;
        x.FWT();
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 2; ++j)
                T[i].mat[i][j] = x;
    }
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    buildTree(1, 0);
    int root = buildChain(1);
    int q = read();
    Seq cres = T[root].mul.getRes();
    while(q--) {
        if(getOp() == 'Q')
            printf("%d\n", asInt(cres.A[read()]));
        else {
            int u = read();
            int v = read();
            int old = val[u];
            val[u] = v;
            int swp = v ^ old;
            Seq x = T[u].mat[1][1], y;
            x.IFWT();
            for(int i = 0; i < N; ++i)
                y.A[i ^ swp] = x.A[i];
            y.FWT();
            setG(u, y);
            setF(u, T[u].mat[0][1] - x + y);
            updateMat(u);
            cres = T[root].mul.getRes();
        }
    }
    return 0;
}
