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
const int size = 200005;
struct Seg {
    int l, r, t;
} T[size * 40];
int icnt = 0, timeStamp;
int cloneNode(int u) {
    if(T[u].t == timeStamp)
        return u;
    int id = ++icnt;
    T[id].l = T[u].l, T[id].r = T[u].r,
    T[id].t = timeStamp;
    return id;
}
int build(int l, int r) {
    int id = ++icnt;
    T[id].t = timeStamp;
    if(l != r) {
        int m = (l + r) >> 1;
        T[id].l = build(l, m);
        T[id].r = build(m + 1, r);
    } else {
        T[id].l = l;
        T[id].r = 1;
    }
    return id;
}
int n, p, v1, v2;
int modifyImpl(int l, int r, int src) {
    int id = cloneNode(src);
    if(l == r)
        T[id].l = v1, T[id].r = v2;
    else {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = modifyImpl(l, m, T[id].l);
        else
            T[id].r = modifyImpl(m + 1, r, T[id].r);
    }
    return id;
}
int modify(int rt, int u, int fu, int rk) {
    p = u, v1 = fu, v2 = rk;
    return modifyImpl(1, n, rt);
}
int query(int l, int r, int id, int p) {
    if(l == r)
        return id;
    else {
        int m = (l + r) >> 1;
        if(p <= m)
            return query(l, m, T[id].l, p);
        return query(m + 1, r, T[id].r, p);
    }
}
int find(int& rt, int x) {
    int fx = T[query(1, n, rt, x)].l;
    if(fx == x)
        return x;
    fx = find(rt, fx);
    rt = modify(rt, x, fx, 0);
    return fx;
}
void merge(int& rt, int u, int v) {
    u = find(rt, u), v = find(rt, v);
    if(u != v) {
        int ru = T[query(1, n, rt, u)].r,
            rv = T[query(1, n, rt, v)].r;
        if(ru < rv)
            rt = modify(rt, u, v, 0);
        else {
            rt = modify(rt, v, u, 0);
            if(ru == rv)
                rt = modify(rt, u, u, ru + 1);
        }
    }
}
int root[size];
int main() {
    n = read();
    root[0] = build(1, n);
    int m = read();
    for(int i = 1; i <= m; ++i)
        switch(read()) {
            case 1: {
                timeStamp = i;
                root[i] = root[i - 1];
                merge(root[i], read(), read());
                break;
            }
            case 2:
                root[i] = root[read()];
                break;
            case 3: {
                root[i] = root[i - 1];
                puts(find(root[i], read()) ==
                             find(root[i], read()) ?
                         "1" :
                         "0");
            } break;
        }
    return 0;
}
