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
int getRandom() {
    static int seed = 145325231;
    return seed = seed * 48271LL % 2147483647;
}
const int size = 100005, inf = 1 << 30,
          magic = 0xc0c0c0c0;
int X[size];
struct Node {
    int l, r, siz, val, minv, maxv, pri;
} T[size * 2];
int tcnt = 0;
#define ls T[id].l
#define rs T[id].r
void update(int id) {
    T[id].siz = T[ls].siz + T[rs].siz + 1;
    T[id].minv = std::min(T[ls].minv, T[rs].minv);
    T[id].maxv = std::max(T[ls].maxv, T[rs].maxv);
    if(T[id].val != magic) {
        T[id].minv = std::min(T[id].minv, T[id].val);
        T[id].maxv = std::max(T[id].maxv, T[id].val);
    }
}
int build(int l, int r) {
    if(l > r)
        return 0;
    int m = (l + r) >> 1;
    int id = ++tcnt;
    T[id].val = X[m];
    T[id].pri = getRandom();
    T[id].l = build(l, m - 1);
    T[id].r = build(m + 1, r);
    update(id);
    return id;
}
int merge(int u, int v) {
    if(u && v) {
        if(T[u].pri < T[v].pri) {
            T[u].r = merge(T[u].r, v);
            update(u);
            return u;
        } else {
            T[v].l = merge(u, T[v].l);
            update(v);
            return v;
        }
    }
    return u | v;
}
// x=[1,siz]
void split(int id, int siz, int& x, int& y) {
    if(id) {
        int lsiz = T[ls].siz;
        if(lsiz + 1 <= siz) {
            x = id;
            split(T[x].r, siz - lsiz - 1, T[x].r, y);
        } else {
            y = id;
            split(T[y].l, siz, x, T[y].l);
        }
        update(id);
    } else
        x = y = 0;
}
void split(int u, int l, int r, int& a, int& b,
           int& c) {
    split(u, l - 1, a, b);
    split(b, r - l + 1, b, c);
}
int merge(int a, int b, int c) {
    return merge(merge(a, b), c);
}
int getMaxv(int& rt, int l, int r) {
    int a, b, c;
    split(rt, l, r, a, b, c);
    int res = T[b].maxv;
    rt = merge(a, b, c);
    return res;
}
int getMinv(int& rt, int l, int r) {
    int a, b, c;
    split(rt, l, r, a, b, c);
    int res = T[b].minv;
    rt = merge(a, b, c);
    return res;
}
bool set(int& rt, int p, int val) {
    int a, b, c;
    split(rt, p, p, a, b, c);
    bool res = false;
    if(T[b].val != magic) {
        T[b].val = val;
        res = true;
        update(b);
    }
    rt = merge(a, b, c);
    return res;
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
                    if(!set(root[0], id[v], y))
                        set(root[1], id[v], y);
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
                    int a = getMinv(root[0],
                                    id[top[x]], id[x]);
                    if(a <= key) {
                        flag = false;
                        break;
                    }
                    int b = getMaxv(root[1],
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
