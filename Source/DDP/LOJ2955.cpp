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
const int size = 100005;
typedef long long Int64;
const Int64 inf = 1LL << 50;
Int64 mini(Int64 a, Int64 b) {
    return a < b ? a : b;
}
struct Mat {
    Int64 A[2][2];
    Int64* operator[](int id) {
        return A[id];
    }
    const Int64* operator[](int id) const {
        return A[id];
    }
    Mat operator*(const Mat& rhs) const {
        Mat res;
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 2; ++j)
                res[i][j] = mini(A[i][0] + rhs[0][j],
                                 A[i][1] + rhs[1][j]);
        return res;
    }
    Int64 minv() const {
        return mini(A[0][1], A[1][1]);
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
        if(v != p) {
            int vsiz = buildTree(v, u);
            siz += vsiz;
            if(vsiz > msiz)
                msiz = vsiz, son[u] = v;
        }
    }
    w[u] = siz - msiz;
    return siz;
}
int ch[size], sw[size];
int buildChainImpl(int l, int r) {
    if(l > r)
        return 0;
    int tot = sw[r] - sw[l - 1], cw = 0;
    for(int i = l; i <= r; ++i) {
        int u = ch[i];
        cw += w[u];
        if(cw * 2 >= tot) {
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
                fa[p] = i;
                T[i].mat[0][1] += T[p].mul[1][1];
                T[i].mat[1][0] = T[i].mat[1][1] +=
                    T[p].mul.minv();
            }
        }
    int csiz = 0;
    for(int i = u; i; i = son[i]) {
        ch[++csiz] = i;
        sw[csiz] = sw[csiz - 1] + w[i];
    }
    return buildChainImpl(1, csiz);
}
void updateMat(int u) {
    while(u) {
        int p = fa[u];
        if(p && isRoot(u)) {
            T[p].mat[0][1] -= T[u].mul[1][1];
            T[p].mat[1][0] = T[p].mat[1][1] -=
                T[u].mul.minv();
            update(u);
            T[p].mat[0][1] += T[u].mul[1][1];
            T[p].mat[1][0] = T[p].mat[1][1] +=
                T[u].mul.minv();
        } else
            update(u);
        u = p;
    }
}
void apply(int u, int op) {
    if(op)
        T[u].mat[0][1] += inf;
    else
        T[u].mat[1][0] = T[u].mat[1][1] += inf;
    updateMat(u);
}
void unapply(int u, int op) {
    if(op)
        T[u].mat[0][1] -= inf;
    else
        T[u].mat[1][0] = T[u].mat[1][1] -= inf;
    updateMat(u);
}
int main() {
    freopen("defense.in", "r", stdin);
    freopen("defense.out", "w", stdout);
    int n = read();
    int m = read();
    int t = read();
    for(int i = 1; i <= n; ++i) {
        T[i].mat[0][0] = inf;
        T[i].mat[1][0] = T[i].mat[1][1] = read();
    }
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    buildTree(1, 0);
    int root = buildChain(1);
    while(m--) {
        int a = read();
        int x = read();
        int b = read();
        int y = read();
        apply(a, x);
        apply(b, y);
        Int64 res = T[root].mul.minv();
        if(res >= inf)
            puts("-1");
        else
            printf("%lld\n", res);
        unapply(b, y);
        unapply(a, x);
    }
    return 0;
}
