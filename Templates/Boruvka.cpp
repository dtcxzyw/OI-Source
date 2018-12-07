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
struct Node {
    int mini, maxi, c[2];
    void update(int id) {
        if(id < mini)
            mini = id;
        else if(id > maxi)
            maxi = id;
    }
} T[size * 30];
int tsiz;
int alloc(int pid) {
    int id = ++tsiz;
    T[id].maxi = T[id].mini = pid;
    T[id].c[0] = T[id].c[1] = 0;
    return id;
}
void insert(int p, int id, int val) {
    T[p].update(id);
    for(int i = 29; i >= 0; --i) {
        int& c = T[p].c[(val >> i) & 1];
        if(!c)
            c = alloc(id);
        else
            T[c].update(id);
        p = c;
    }
}
struct Res {
    int v, w;
    Res() {}
    Res(int v, int w) : v(v), w(w) {}
};
Res query(int p, int id, int val) {
    Res res(0, 0);
    for(int i = 29; i >= 0; --i) {
        int mask = (val >> i) & 1;
        int u = T[p].c[mask];
        if(u &&
           !(T[u].maxi == T[u].mini &&
             T[u].maxi == id))
            p = u;
        else
            p = T[p].c[mask ^ 1], res.w |= 1 << i;
    }
    res.v = (T[p].mini == id ? T[p].maxi : T[p].mini);
    return res;
}
int fa[size];
int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}
int A[size];
int rebuild(int n) {
    tsiz = 0;
    int rt = alloc(0);
    T[rt].maxi = n + 1;
    for(int i = 1; i <= n; ++i)
        insert(rt, find(i), A[i]);
    return rt;
}
Res sol[size];
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    int bcnt = n;
    long long ans = 0;
    while(bcnt > 1) {
        int rt = rebuild(n);
        for(int i = 1; i <= n; ++i)
            sol[i] = Res(0, 1 << 30);
        for(int i = 1; i <= n; ++i) {
            int fi = find(i);
            Res csol = query(rt, fi, A[i]);
            if(sol[fi].w > csol.w)
                sol[fi] = csol;
        }
        for(int i = 1; i <= n; ++i)
            if(find(i) == i) {
                int fv = find(sol[i].v);
                if(fv != i) {
                    fa[i] = fv;
                    ans += sol[i].w;
                    if(--bcnt == 1)
                        break;
                }
            }
    }
    printf("%lld\n", ans);
    return 0;
}
