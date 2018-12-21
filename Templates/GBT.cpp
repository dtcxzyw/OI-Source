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
void printImpl(int x) {
    if(x >= 10)
        printImpl(x / 10);
    putchar('0' + x % 10);
}
void print(int x) {
    if(x < 0)
        putchar('-'), x = -x;
    printImpl(x);
    putchar('\n');
}
int maxi(int a, int b) {
    return a > b ? a : b;
}
const int size = 100005, inf = 1 << 29;
struct Mat {
    int A[2][2];
    int* operator[](int i) {
        return A[i];
    }
    const int* operator[](int i) const {
        return A[i];
    }
    Mat operator*(const Mat& rhs) const {
        Mat res;
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 2; ++j)
                res[i][j] = maxi(A[i][0] + rhs[0][j],
                                 A[i][1] + rhs[1][j]);
        return res;
    }
    int maxv() const {
        return maxi(A[0][0], A[1][0]);
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
int p[size], son[size], w[size];
int buildTree(int u) {
    int siz = 1, ms = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u]) {
            p[v] = u;
            int sv = buildTree(v);
            siz += sv;
            if(sv > ms)
                son[u] = v, ms = sv;
        }
    }
    w[u] = siz - ms;
    return siz;
}
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
int ch[size], sw[size];
int buildChainImpl(int l, int r) {
    if(l > r)
        return 0;
    int sum = 0, tot = sw[r] - sw[l - 1];
    for(int i = l; i <= r; ++i) {
        int u = ch[i];
        sum += w[u];
        if(sum * 2 >= tot) {
            ls = buildChainImpl(l, i - 1);
            rs = buildChainImpl(i + 1, r);
            fa[ls] = fa[rs] = u;
            update(u);
            return u;
        }
    }
}
bool flag[size];
int buildChain(int u) {
    for(int i = u; i; i = son[i])
        flag[i] = true;
    for(int i = u; i; i = son[i]) {
        for(int j = last[i]; j; j = E[j].nxt) {
            int v = E[j].to;
            if(!flag[v]) {
                int p = buildChain(v);
                fa[p] = i;
                T[i].mat[0][0] = T[i].mat[0][1] +=
                    T[p].mul.maxv();
                T[i].mat[1][0] += T[p].mul[0][0];
            }
        }
    }
    int csiz = 0;
    for(int i = u; i; i = son[i]) {
        ch[++csiz] = i;
        sw[csiz] = sw[csiz - 1] + w[i];
    }
    return buildChainImpl(1, csiz);
}
int V[size];
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i)
        V[i] = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    buildTree(1);
    for(int i = 1; i <= n; ++i) {
        T[i].mat[1][0] = V[i];
        T[i].mat[1][1] = -inf;
    }
    int root = buildChain(1);
    while(m--) {
        int x = read();
        int y = read();
        T[x].mat[1][0] += y - V[x];
        V[x] = y;
        for(int i = x; i; i = fa[i])
            if(fa[i] && isRoot(i)) {
                int p = fa[i];
                T[p].mat[0][0] = T[p].mat[0][1] -=
                    T[i].mul.maxv();
                T[p].mat[1][0] -= T[i].mul[0][0];
                update(i);
                T[p].mat[0][0] = T[p].mat[0][1] +=
                    T[i].mul.maxv();
                T[p].mat[1][0] += T[i].mul[0][0];
            } else
                update(i);
        print(T[root].mul.maxv());
    }
    return 0;
}
