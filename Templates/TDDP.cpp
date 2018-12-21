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
} T[size << 2];
struct Vec {
    int f, g;
} A[size];
int V[size];
Vec update(Vec a, const Vec& b) {
    a.f += maxi(b.f, b.g);
    a.g += b.f;
    return a;
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
int p[size], son[size];
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
    return siz;
}
int top[size], id[size], pid[size], icnt = 0, ch[size];
Vec buildChain(int u) {
    int uid = ++icnt;
    id[u] = uid;
    pid[uid] = u;
    A[uid].g = V[u];
    Vec lazy;
    if(son[u]) {
        top[son[u]] = top[u];
        lazy = buildChain(son[u]);
        ch[u] = ch[son[u]] + 1;
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!top[v]) {
            top[v] = v;
            A[uid] = update(A[uid], buildChain(v));
        }
    }
    Vec res = son[u] ? update(A[uid], lazy) : A[uid];
    return res;
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void update(int id) {
    T[id] = T[id << 1] * T[id << 1 | 1];
}
int lid[size];
void build(int l, int r, int id) {
    if(l == r) {
        lid[pid[l]] = id;
        Mat& base = T[id];
        base[0][0] = base[0][1] = A[l].f;
        base[1][0] = A[l].g;
        base[1][1] = -inf;
    } else {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        update(id);
    }
}
Mat mat;
void updateMat(int u) {
    int id = lid[u];
    T[id] = mat;
    while(id >= 2)
        update(id >>= 1);
}
int nl, nr;
Mat query(int l, int r, int id) {
    if(nl <= l && r <= nr)
        return T[id];
    else {
        int m = (l + r) >> 1;
        if(nl <= m && m < nr)
            return query(ls) * query(rs);
        if(nl <= m)
            return query(ls);
        return query(rs);
    }
}
int n;
Mat getMat(int u) {
    nl = id[u], nr = id[u] + ch[u];
    return query(1, n, 1);
}
int main() {
    n = read();
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
    top[1] = 1;
    buildChain(1);
    build(1, n, 1);
    while(m--) {
        int x = read();
        int y = read();
        {
            mat = T[lid[x]];
            mat[1][0] += y - V[x];
            V[x] = y;
        }
        while(true) {
            int tx = top[x], ptx = p[tx];
            if(ptx) {
                Mat old = getMat(tx);
                updateMat(x);
                Mat now = getMat(tx);
                {
                    mat = T[lid[ptx]];
                    int delta =
                        maxi(now[0][0], now[1][0]) -
                        maxi(old[0][0], old[1][0]);
                    mat[0][0] = (mat[0][1] += delta);
                    mat[1][0] += now[0][0] - old[0][0];
                }
                x = ptx;
            } else
                break;
        }
        updateMat(x);
        Mat res = getMat(1);
        print(maxi(res[0][0], res[1][0]));
    }
    return 0;
}
