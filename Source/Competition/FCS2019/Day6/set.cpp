#include <algorithm>
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
const int size = 200005;
struct Edge {
    int to, nxt;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int son[size], p[size], d[size];
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        p[v] = u, d[v] = d[u] + 1;
        int vsiz = buildTree(v);
        siz += vsiz;
        if(vsiz > msiz)
            msiz = vsiz, son[u] = v;
    }
    return siz;
}
int top[size], id[size], map[size], tcnt = 0;
void buildChain(int u) {
    id[u] = ++tcnt;
    map[tcnt] = u;
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!top[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
int getLCA(int u, int v) {
    while(top[u] != top[v]) {
        if(d[top[u]] < d[top[v]])
            std::swap(u, v);
        u = p[top[u]];
    }
    return d[u] < d[v] ? u : v;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
int W[size];
struct BIT {
    Int64 S[size];
    void build(int n) {
        for(int i = 1; i <= n; ++i) {
            S[i] += W[map[i]];
            int j = i + (i & -i);
            if(j <= n)
                S[j] += S[i];
        }
    }
    void modify(int x, int n, int val) {
        while(x <= n) {
            S[x] += val;
            x += x & -x;
        }
    }
    Int64 query(int x) {
        Int64 res = 0;
        while(x) {
            res += S[x];
            x -= x & -x;
        }
        return res;
    }
    Int64 queryChain(int u, int v) {
        Int64 res = 0;
        while(top[u] != top[v]) {
            if(d[top[u]] < d[top[v]])
                std::swap(u, v);
            res +=
                query(id[u]) - query(id[top[u]] - 1);
            u = p[top[u]];
        }
        if(d[u] < d[v])
            std::swap(u, v);
        res += query(id[u]) - query(id[v] - 1);
        return res;
    }
} SA, SB;
int st[size], A[size];
int find(int r, int val) {
    int l = 1, ans = 1;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(A[st[m]] > val)
            l = m + 1, ans = m;
        else
            r = m - 1;
    }
    return st[ans];
}
Int64 tag[size];
int main() {
    int n = read();
    int q = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    int rt = n + 1;
    A[rt] = 1 << 30;
    int stop = 1;
    st[stop] = rt;
    for(int i = n; i >= 1; --i) {
        int p = find(stop, A[i]);
        addEdge(p, i);
        while(stop && A[st[stop]] <= A[i])
            --stop;
        st[++stop] = i;
    }
    buildTree(rt);
    top[rt] = rt;
    buildChain(rt);
    for(int i = 1; i <= n; ++i)
        W[i] = read();
    SA.build(tcnt);
    for(int i = 1; i <= q; ++i) {
        int op = read();
        int u = read();
        int v = read();
        if(op == 1) {
            SA.modify(id[u], tcnt, v);
            SB.modify(id[u], tcnt, v);
            tag[u] += v;
        } else {
            int lca = getLCA(u, v);
            bool flag = false;
            if(lca == u || lca == v)
                lca = p[lca], flag = true;
            if(lca != rt) {
                Int64 res;
                if(flag) {
                    if(p[u] == lca)
                        std::swap(u, v);
                    res = SA.queryChain(u, lca) +
                        SB.queryChain(p[u], p[lca]);
                } else {
                    res = SA.queryChain(u, v) +
                        SB.queryChain(p[u], p[v]) +
                        tag[lca] + tag[p[lca]];
                }
                printf("%lld\n", res);
            } else
                puts("?");
        }
    }
    return 0;
}
