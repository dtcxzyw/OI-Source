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
const int size = 100005, inf = 1 << 30,
          magic = 0xc0c0c0c0;
int X[size];
struct Node {
    int l, r, siz, minv, maxv;
} T[size * 80];
int tcnt = 0;
#define ls T[id].l
#define rs T[id].r
void update(int id) {
    T[id].siz = T[ls].siz + T[rs].siz;
    T[id].minv = std::min(T[ls].minv, T[rs].minv);
    T[id].maxv = std::max(T[ls].maxv, T[rs].maxv);
}
int build(int l, int r) {
    int id = ++tcnt;
    if(l == r) {
        T[id].siz = 1;
        if(X[l] == magic)
            T[id].minv = inf, T[id].maxv = 0;
        else
            T[id].minv = T[id].maxv = X[l];
    } else {
        int m = (l + r) >> 1;
        T[id].l = build(l, m);
        T[id].r = build(m + 1, r);
        update(id);
    }
    return id;
}
int merge(int u, int v) {
    if(u && v) {
        T[u].siz += T[v].siz;
        T[u].maxv = std::max(T[u].maxv, T[v].maxv);
        T[u].minv = std::min(T[u].minv, T[v].minv);
        T[u].l = merge(T[u].l, T[v].l);
        T[u].r = merge(T[u].r, T[v].r);
        return u;
    }
    return u | v;
}
int split(int src, int k) {
    if(T[src].siz == k)
        return 0;
    int id = ++tcnt;
    T[id].siz = T[src].siz - k;
    T[src].siz = k;
    int lsiz = T[T[src].l].siz;
    if(lsiz >= k) {
        T[id].l = split(T[src].l, k);
        T[id].r = T[src].r;
        T[src].r = 0;
    } else
        T[id].r = split(T[src].r, k - lsiz);
    update(id);
    update(src);
    return id;
}
void split(int u, int l, int r, int& a, int& b,
           int& c) {
    a = u;
    b = split(a, l - 1);
    c = split(b, r - l + 1);
}
int merge(int a, int b, int c) {
    return merge(merge(a, b), c);
}
int getMaxv(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        return T[id].maxv;
    else {
        int m = (l + r) >> 1, res = 0;
        if(nl <= m)
            res = std::max(
                res, getMaxv(l, m, T[id].l, nl, nr));
        if(m < nr)
            res = std::max(
                res,
                getMaxv(m + 1, r, T[id].r, nl, nr));
        return res;
    }
}
int getMinv(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        return T[id].minv;
    else {
        int m = (l + r) >> 1, res = inf;
        if(nl <= m)
            res = std::min(
                res, getMinv(l, m, T[id].l, nl, nr));
        if(m < nr)
            res = std::min(
                res,
                getMinv(m + 1, r, T[id].r, nl, nr));
        return res;
    }
}
bool set(int l, int r, int id, int p, int val) {
    if(l == r) {
        if(T[id].minv == inf && T[id].maxv == 0)
            return false;
        T[id].minv = T[id].maxv = val;
        return true;
    } else {
        int m = (l + r) >> 1;
        bool res = p <= m ?
            set(l, m, T[id].l, p, val) :
            set(m + 1, r, T[id].r, p, val);
        update(id);
        return res;
    }
}
void exchange(int& A, int& B, int l, int r) {
    int a1, b1, c1;
    split(A, l, r, a1, b1, c1);
    int a2, b2, c2;
    split(B, l, r, a2, b2, c2);
    A = merge(a1, b2, c1);
    B = merge(a2, b1, c2);
}
int siz[size], p[size], son[size], ch[size][2];
void buildTree(int u) {
    siz[u] = 1;
    for(int i = 0; i < 2; ++i) {
        int v = ch[u][i];
        if(v == 0)
            continue;
        p[v] = u;
        buildTree(v);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]])
            son[u] = v;
    }
}
int top[size], id[size], icnt = 0;
void buildChain(int u) {
    id[u] = ++icnt;
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = 0; i < 2; ++i) {
        int v = ch[u][i];
        if(v == 0 || top[v])
            continue;
        top[v] = v;
        buildChain(v);
    }
}
int A[size], root[2];
bool nrt[size];
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        A[i] = read();
        ch[i][0] = read();
        ch[i][1] = read();
        nrt[ch[i][0]] = true;
        nrt[ch[i][1]] = true;
    }
    int rt = 0;
    for(int i = 1; i <= n; ++i)
        if(!nrt[i]) {
            rt = i;
            break;
        }
    p[rt] = 0;
    buildTree(rt);
    top[rt] = rt;
    buildChain(rt);
    T[0].minv = inf;
    // rt0
    for(int i = 1; i <= n; ++i)
        if(i == rt || i == ch[p[i]][1])
            X[id[i]] = magic;
        else
            X[id[i]] = A[p[i]];
    root[0] = build(1, n);
    // rt1
    for(int i = 1; i <= n; ++i)
        if(i == rt || i == ch[p[i]][0])
            X[id[i]] = magic;
        else
            X[id[i]] = A[p[i]];
    root[1] = build(1, n);
    for(int t = 1; t <= m; ++t) {
        int op = read();
        int x = read();
        switch(op) {
            case 1: {
                int y = read();
                A[x] = y;
                for(int i = 0; i < 2; ++i) {
                    int v = ch[x][i];
                    if(v == 0)
                        continue;
                    if(!set(1, n, root[0], id[v], y))
                        set(1, n, root[1], id[v], y);
                }
            } break;
            case 2: {
                for(int i = 0; i < 2; ++i) {
                    int v = ch[x][i];
                    if(v == 0)
                        continue;
                    exchange(root[0], root[1], id[v],
                             id[v] + siz[v] - 1);
                }
            } break;
            case 3: {
                bool flag = true;
                int key = A[x];
                while(x) {
                    int a = getMinv(1, n, root[0],
                                    id[top[x]], id[x]);
                    if(a <= key) {
                        flag = false;
                        break;
                    }
                    int b = getMaxv(1, n, root[1],
                                    id[top[x]], id[x]);
                    if(b >= key) {
                        flag = false;
                        break;
                    }
                    x = p[top[x]];
                }
                puts(flag ? "YES" : "NO");
            } break;
        }
    }
    return 0;
}
