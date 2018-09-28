#include <algorithm>
#include <cstdio>
#include <queue>
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
int getOp() {
    int c;
    do
        c = getchar();
    while(c != 'C' && c != 'A');
    return c;
}
const int size = 100005;
struct Edge {
    int to, nxt, w;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int icnt = 0, A[18][size * 2], L[size], d[size],
    len[size];
void pre(int u, int p) {
    A[0][++icnt] = u;
    L[u] = icnt;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            d[v] = d[u] + 1;
            len[v] = len[u] + E[i].w;
            pre(v, u);
            A[0][++icnt] = u;
        }
    }
}
int choose(int u, int v) {
    return d[u] < d[v] ? u : v;
}
void buildST() {
    for(int i = 1; i < 18; ++i) {
        int off = 1 << (i - 1),
            end = icnt - (1 << i) + 1;
        for(int j = 1; j <= end; ++j)
            A[i][j] =
                choose(A[i - 1][j], A[i - 1][j + off]);
    }
}
int ilg2(int x) {
    return 31 - __builtin_clz(x);
}
int getLca(int u, int v) {
    int l = L[u], r = L[v];
    if(l > r)
        std::swap(l, r);
    int p = ilg2(r - l + 1);
    return choose(A[p][l], A[p][r - (1 << p) + 1]);
}
int getDis(int u, int v) {
    return len[u] + len[v] - (len[getLca(u, v)] << 1);
}
bool vis[size];
int root, tsiz, msiz, siz[size];
void getRootImpl(int u, int p) {
    int maxs = 0;
    siz[u] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v] && v != p) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            maxs = std::max(maxs, siz[v]);
        }
    }
    maxs = std::max(maxs, tsiz - siz[u]);
    if(maxs < msiz) {
        msiz = maxs;
        root = u;
    }
}
int getRoot(int u, int csiz) {
    msiz = 1 << 30, tsiz = csiz;
    getRootImpl(u, 0);
    return root;
}
const int nan = 0xc0c0c0c0;
class Heap {
private:
    std::priority_queue<int> A, B;
    void update() {
        while(B.size() && B.top() == A.top())
            A.pop(), B.pop();
    }

public:
    void insert(int val) {
        if(val != nan)
            A.push(val);
    }
    void erase(int val) {
        if(val != nan)
            B.push(val);
    }
    void modify(int val, bool op) {
        if(val != nan)
            (op ? A : B).push(val);
    }
    int getMax() {
        update();
        return A.size() ? A.top() : nan;
    }
    int getMix() {
        int vala = getMax();
        if(vala != nan) {
            A.pop();
            int valb = getMax();
            A.push(vala);
            if(valb != nan)
                return vala + valb;
        }
        return nan;
    }
    void replace(int a, int b) {
        erase(a);
        insert(b);
    }
} df[size], md[size], glo;
int fa[size];
void DFS(int u, int p, int a, int b) {
    df[a].insert(getDis(u, b));
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v] && v != p)
            DFS(v, u, a, b);
    }
}
void divide(int u) {
    md[u].insert(0);
    md[u].insert(0);
    if(fa[u])
        DFS(u, 0, u, fa[u]);
    vis[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int nrt = getRoot(v, siz[v]);
            fa[nrt] = u;
            divide(nrt);
            md[u].insert(df[nrt].getMax());
        }
    }
}
void modify(int p, int u, bool op) {
    int pp = fa[p];
    int dis = getDis(pp, u);
    int old = df[p].getMax();
    df[p].modify(dis, op);
    int now = df[p].getMax();
    if(old != now) {
        int omix = md[pp].getMix();
        md[pp].replace(old, now);
        int nmix = md[pp].getMix();
        if(omix != nmix)
            glo.replace(omix, nmix);
    }
}
bool col[size];
int main() {
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    pre(1, 0);
    buildST();
    int rt = getRoot(1, n);
    divide(rt);
    for(int i = 1; i <= n; ++i)
        glo.insert(md[i].getMix());
    int q = read();
    while(q--) {
        if(getOp() == 'C') {
            int u = read();
            bool op = col[u];
            col[u] ^= 1;
            {
                int omix = md[u].getMix();
                md[u].modify(0, op);
                md[u].modify(0, op);
                int nmix = md[u].getMix();
                if(omix != nmix)
                    glo.replace(omix, nmix);
            }
            int p = u;
            while(fa[p]) {
                modify(p, u, op);
                p = fa[p];
            }
        } else {
            int res = glo.getMax();
            if(res != nan)
                printf("%d\n", res);
            else
                puts("They have disappeared.");
        }
    }
    return 0;
}
