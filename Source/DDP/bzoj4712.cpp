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
int getOp() {
    int c;
    do
        c = getchar();
    while(c != 'C' && c != 'Q');
    return c;
}
const int size = 200005, inf = 1 << 30;
int min3(int a, int b, int c) {
    return std::min(a, std::min(b, c));
}
struct Mat {
    int A00, A01, A02, A10, A11, A12;
    Mat(int A00, int A01, int A02, int A10, int A11,
        int A12)
        : A00(A00), A01(A01), A02(A02), A10(A10),
          A11(A11), A12(A12) {}
    Mat(int A)
        : A00(A), A01(inf), A02(inf), A10(inf), A11(0),
          A12(0) {}
    Mat() {}
    Mat operator*(const Mat& rhs) const {
        return Mat(
            min3(A00, A01 + rhs.A00, A02 + rhs.A10),
            min3(A00, A01 + rhs.A01, A02 + rhs.A11),
            min3(A00, A01 + rhs.A02, A02 + rhs.A12),
            min3(A10, A11 + rhs.A00, A12 + rhs.A10),
            min3(A10, A11 + rhs.A01, A12 + rhs.A11),
            min3(A10, A11 + rhs.A02, A12 + rhs.A12));
    }
    int minv() {
        return min3(A00, A11, A12);
    }
};
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int son[size], lsiz[size], p[size];
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p[u])
            continue;
        int vsiz = buildTree(v);
        siz += vsiz;
        if(msiz < vsiz)
            msiz = vsiz, son[u] = v;
    }
    lsiz[u] = siz - msiz;
    return siz;
}
struct Node {
    Mat mat, mul;
    int l, r;
} T[size];
#define ls T[u].l
#define rs T[u].r
void update(int u) {
    T[u].mul = T[u].mat;
    if(ls)
        T[u].mul = T[ls].mul * T[u].mul;
    if(rs)
        T[u].mul = T[u].mul * T[rs].mul;
}
int fa[size];
bool isRoot(int u) {
    int p = fa[u];
    return T[p].l != u && T[p].r != u;
}
int ssiz[size], ch[size];
int buildChainImpl(int l, int r) {
    if(l > r)
        return 0;
    int tot = ssiz[r] - ssiz[l - 1];
    for(int i = l, sum = 0; i <= r; ++i) {
        int u = ch[i];
        sum += lsiz[u];
        if(sum * 2 >= tot) {
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
    for(int i = u; i; i = son[i]) {
        for(int j = last[i]; j; j = E[j].nxt) {
            int v = E[j].to;
            if(flag[v])
                continue;
            int vid = buildChain(v);
            fa[vid] = i;
            T[i].mat.A11 =
                (T[i].mat.A10 += T[vid].mat.minv());
        }
    }
    int ccnt = 0;
    for(int i = u; i; i = son[i]) {
        ch[++ccnt] = i;
        ssiz[ccnt] = ssiz[ccnt - 1] + lsiz[i];
    }
    return buildChainImpl(1, ccnt);
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        T[i].mat = Mat(read());
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    buildTree(1);
    int rt = buildChain(1);
    int m = read();
    for(int t = 1; t <= m; ++t) {
        int op = getOp();
        int x = read();
        if(op == 'C') {
            int to = read();
        } else {
            Mat base(0);
            while(true) {
            }
        }
    }
    return 0;
}
