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
const int size = 200005;
typedef long long Int64;
Int64 min3(Int64 a, Int64 b, Int64 c) {
    return std::min(a, std::min(b, c));
}
const Int64 inf = 1LL << 40;
struct Mat {
    Int64 A10, A20, A21;
    Mat(Int64 A10, Int64 A20, Int64 A21)
        : A10(A10), A20(A20), A21(A21) {}
    Mat(Int64 A) : A10(A), A20(inf), A21(0) {}
    Mat() {}
    Mat operator*(const Mat& rhs) const {
        return Mat(A10, min3(A20, A21 + rhs.A10,
                             A21 + rhs.A20),
                   A21 + rhs.A21);
    }
    Int64 minv() {
        return std::min(A10, A20);
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
int son[size], lsiz[size], p[size], id[size], icnt = 0;
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p[u])
            continue;
        p[v] = u;
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
    int l, r, p;
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
bool isRoot(int u) {
    int p = T[u].p;
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
            T[ls].p = T[rs].p = u;
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
            T[vid].p = i;
            T[i].mat.A21 += T[vid].mul.minv();
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
    buildChain(1);
    int m = read();
    for(int t = 1; t <= m; ++t) {
        int op = getOp();
        int x = read();
        if(op == 'C') {
            int to = read();
            T[x].mat.A10 += to;
            for(int i = x; i; i = T[i].p)
                if(T[i].p && isRoot(i)) {
                    int p = T[i].p;
                    Int64 old = T[i].mul.minv();
                    update(i);
                    Int64 now = T[i].mul.minv();
                    T[p].mat.A21 += now - old;
                } else
                    update(i);
        } else {
            Mat res;
            bool init = false;
            int last = T[x].l;
            while(true) {
                if(T[x].l == last) {
                    if(init)
                        res = res * T[x].mat;
                    else
                        res = T[x].mat, init = true;
                    if(T[x].r)
                        res = res * T[T[x].r].mul;
                }
                last = x;
                if(isRoot(x))
                    break;
                else
                    x = T[x].p;
            }
            printf("%lld\n", res.minv());
        }
    }
    return 0;
}
