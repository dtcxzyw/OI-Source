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
int maxi(int a, int b) {
    return a > b ? a : b;
}
const int size = 200005;
int ch[size][2], p[size], siz[size], son[size];
void buildTree(int u) {
    siz[u] = 1;
    for(int i = 0; i < 2; ++i) {
        int v = ch[u][i];
        if(v) {
            p[v] = u;
            buildTree(v);
            siz[u] += siz[v];
            if(siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}
int id[size], icnt = 0, top[size];
void buildChain(int u) {
    id[u] = ++icnt;
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = 0; i < 2; ++i) {
        int v = ch[u][i];
        if(v && !id[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
int n;
namespace Size {
    int dsiz[size];
    void add(int x, int op) {
        while(x <= n) {
            dsiz[x] += op;
            x += x & -x;
        }
    }
    void addRange(int l, int r) {
        add(l, 1);
        add(r + 1, -1);
    }
    void addNode(int u) {
        while(top[u]) {
            addRange(id[top[u]], id[u]);
            u = p[top[u]];
        }
    }
    int query(int x) {
        x = id[x];
        int res = 0;
        while(x) {
            res += dsiz[x];
            x -= x & -x;
        }
        return res;
    }
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
namespace RemoveTime {
    int at[size], maxt[size << 2];
    void update(int id) {
        maxt[id] =
            maxi(maxt[id << 1], maxt[id << 1 | 1]);
    }
    void build(int l, int r, int id) {
        if(l == r)
            maxt[id] = at[l];
        else {
            int m = (l + r) >> 1;
            build(ls);
            build(rs);
            update(id);
        }
    }
    int query(int l, int r, int id, int nl, int nr) {
        if(nl <= l && r <= nr)
            return maxt[id];
        else {
            int m = (l + r) >> 1, res = 0;
            if(nl <= m)
                res = maxi(res, query(ls, nl, nr));
            if(m < nr)
                res = maxi(res, query(rs, nl, nr));
            return res;
        }
    }
    void remove(int l, int r, int id, int p) {
        if(l == r)
            maxt[id] = 0;
        else {
            int m = (l + r) >> 1;
            if(p <= m)
                remove(ls, p);
            else
                remove(rs, p);
            update(id);
        }
    }
    void remove(int u) {
        remove(1, n, 1, id[u]);
    }
    int query(int u) {
        return query(1, n, 1, id[u],
                     id[u] + siz[u] - 1);
    }
}
namespace CurrentTop {
    int tag[size << 2];
    void modify(int l, int r, int id, int nl, int nr,
                int val) {
        if(nl <= l && r <= nr)
            tag[id] = val;
        else {
            int m = (l + r) >> 1;
            if(tag[id]) {
                tag[id << 1] = tag[id << 1 | 1] =
                    tag[id];
                tag[id] = 0;
            }
            if(nl <= m)
                modify(ls, nl, nr, val);
            if(m < nr)
                modify(rs, nl, nr, val);
        }
    }
    int query(int l, int r, int id, int p) {
        if(tag[id])
            return tag[id];
        int m = (l + r) >> 1;
        if(p <= m)
            return query(ls, p);
        return query(rs, p);
    }
    void modifyPoint(int u, int val) {
        modify(1, n, 1, id[u], id[u], val);
    }
    void modifyChain(int fu, int u, int val) {
        while(top[u] != top[fu]) {
            modify(1, n, 1, id[top[u]], id[u], val);
            u = p[top[u]];
        }
        modify(1, n, 1, id[fu], id[u], val);
    }
    int query(int u) {
        return query(1, n, 1, id[u]);
    }
}
int A[size], cq;
bool flag[size];
void DFS(int u) {
    for(int i = 0; i < 2; ++i) {
        int v = ch[u][i];
        if(v && !flag[v])
            DFS(v);
    }
    A[++cq] = u;
}
int ctid[size];
long long ans[size];
int main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 0; j < 2; ++j)
            ch[i][j] = read();
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    int q = read();
    for(int i = 1; i <= q; ++i) {
        A[i] = read();
        flag[A[i]] = true;
    }
    if(q != n) {
        cq = q;
        DFS(1);
    }
    for(int i = 1; i < n; ++i) {
        int u = A[i];
        RemoveTime::at[id[u]] = i;
    }
    RemoveTime::build(1, n, 1);
    Size::addNode(1);
    int ctcnt = 0;
    ctid[1] = ctcnt = 1;
    CurrentTop::modifyPoint(1, 1);
    long long cans = 0;
    for(int i = n - 1; i >= 1; --i) {
        ans[i] = cans;
        int u = A[i];
        Size::addNode(u);
        RemoveTime::remove(u);
        ctid[++ctcnt] = u;
        CurrentTop::modifyPoint(u, ctcnt);
        while(p[u]) {
            int pu = p[u];
            int ou = u ^ ch[pu][0] ^ ch[pu][1];
            int su = Size::query(u),
                sou = Size::query(ou);
            int tpu = CurrentTop::query(pu),
                nxt = ctid[tpu];
            if(sou == 0) {
                CurrentTop::modifyPoint(u, tpu);
                cans += u;
            } else {
                bool rep = false;
                if(su > sou)
                    rep = true;
                else if(su == sou) {
                    int tu = RemoveTime::query(u);
                    int tou = RemoveTime::query(ou);
                    if(tu || tou)
                        rep = (tu > tou);
                    else
                        rep = (u == ch[pu][0]);
                }
                if(rep) {
                    cans += u - ou;
                    int id = CurrentTop::query(u);
                    ctid[id] = nxt;
                    CurrentTop::modifyChain(nxt, pu,
                                            id);
                    ctid[tpu] = ou;
                }
            }
            u = nxt;
        }
    }
    ans[0] = cans;
    for(int i = 0; i <= q; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
