#include <cstdio>
#include <set>
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
const int size = 100005;
typedef std::set<int>::iterator IterT;
struct Node {
    int l, r, siz;
} T[size * 50];
int tcnt = 0;
int insert(int l, int r, int p) {
    int id = ++tcnt;
    T[id].siz = 1;
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = insert(l, m, p);
        else
            T[id].r = insert(m + 1, r, p);
    }
    return id;
}
int query(int l, int r, int id) {
    if(l == r)
        return l;
    int m = (l + r) >> 1;
    return T[T[id].l].siz ? query(l, m, T[id].l) :
                            query(m + 1, r, T[id].r);
}
int merge(int a, int b) {
    if(a && b) {
        T[a].siz += T[b].siz;
        T[a].l = merge(T[a].l, T[b].l);
        T[a].r = merge(T[a].r, T[b].r);
        return a;
    }
    return a | b;
}
int split(int src, int k, int d) {
    if(T[src].siz == k)
        return 0;
    int id = ++tcnt;
    T[id].siz = T[src].siz - k;
    T[src].siz = k;
    if(d) {
        int rsiz = T[T[src].r].siz;
        if(rsiz >= k) {
            T[id].r = split(T[src].r, k, d);
            T[id].l = T[src].l;
            T[src].l = 0;
        } else
            T[id].l = split(T[src].l, k - rsiz, d);
    } else {
        int lsiz = T[T[src].l].siz;
        if(lsiz >= k) {
            T[id].l = split(T[src].l, k, d);
            T[id].r = T[src].r;
            T[src].r = 0;
        } else
            T[id].r = split(T[src].r, k - lsiz, d);
    }
    return id;
}
int rt[size], dir[size];
std::set<int> interval;
//[pos,)
IterT split(int pos) {
    IterT it = interval.lower_bound(pos);
    if(*it == pos)
        return it;
    --it;
    rt[pos] = split(rt[*it], pos - *it, dir[*it]);
    dir[pos] = dir[*it];
    return interval.insert(pos).first;
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        rt[i] = insert(1, n, read());
        interval.insert(i);
    }
    interval.insert(n + 1);
    for(int i = 1; i <= m; ++i) {
        int d = read();
        int l = read();
        int r = read();
        IterT beg = split(l);
        IterT end = split(r + 1);
        int crt = 0;
        for(IterT it = beg; it != end; ++it)
            crt = merge(crt, rt[*it]);
        rt[l] = crt;
        dir[l] = d;
        interval.erase(++beg, end);
    }
    int q = read();
    split(q);
    split(q + 1);
    printf("%d\n", query(1, n, rt[q]));
    return 0;
}
