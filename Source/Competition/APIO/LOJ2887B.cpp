//%%% HeRaNO
#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 30005, maxE = size * 25,
          maxS = size * 2;
struct Edge {
    int to, nxt, w;
} E[maxE];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
struct Node {
    int u, d, son, bro;
} T[maxS];
int tcnt = 0;
int merge(int u, int v) {
    if(u && v) {
        if(T[u].d > T[v].d)
            std::swap(u, v);
        T[v].bro = T[u].son;
        T[u].son = v;
        return u;
    }
    return u | v;
}
int insert(int rt, int u, int d) {
    int id = ++tcnt;
    T[id].u = u, T[id].d = d;
    return merge(rt, id);
}
int mergeBro(int u) {
    if(u && T[u].bro) {
        int a = T[u].bro, b = T[a].bro;
        T[u].bro = T[a].bro = 0;
        return merge(merge(u, a), mergeBro(b));
    }
    return u;
}
int erase(int rt) {
    return mergeBro(T[rt].son);
}
int dis[size];
int SSSP(int n, int s, int t) {
    memset(dis, 0x3f, sizeof(int) * n);
    dis[s] = 0;
    int rt = 0;
    rt = insert(rt, s, 0);
    while(rt) {
        int u = T[rt].u;
        int du = T[rt].d;
        rt = erase(rt);
        if(dis[u] != du)
            continue;
        if(u == t)
            return du;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to, dv = du + E[i].w;
            if(dis[v] > dv) {
                dis[v] = dv;
                rt = insert(rt, v, dv);
            }
        }
    }
    return -1;
}
struct Info {
    int b, p;
} A[size];
bool cmpL(const Info& a, const Info& b) {
    return a.p == b.p ? a.b < b.b : a.p < b.p;
}
bool cmpR(const Info& a, const Info& b) {
    return a.p == b.p ? a.b > b.b : a.p < b.p;
}
bool flag[size];
int lp[size];
int main() {
    int n = read();
    int m = read();
    for(int i = 0; i < m; ++i) {
        A[i].b = read();
        A[i].p = read();
        flag[A[i].b] = true;
    }
    int s = A[0].b, t = A[1].b;
    std::sort(A, A + m, cmpL);
    for(int i = 0; i < m; ++i) {
        int b = A[i].b, p = A[i].p;
        if(lp[b] == p)
            continue;
        lp[b] = p;
        for(int j = 1, k = b - p; k >= 0; ++j, k -= p)
            if(flag[k]) {
                addEdge(b, k, j);
                if(lp[k] == p)
                    break;
            }
    }
    memset(lp, 0, sizeof(int) * n);
    std::sort(A, A + m, cmpR);
    for(int i = 0; i < m; ++i) {
        int b = A[i].b, p = A[i].p;
        if(lp[b] == p)
            continue;
        lp[b] = p;
        for(int j = 1, k = b + p; k < n; ++j, k += p)
            if(flag[k]) {
                addEdge(b, k, j);
                if(lp[k] == p)
                    break;
            }
    }
    printf("%d\n", SSSP(n, s, t));
    fprintf(stderr, "%d %d\n", cnt, tcnt);
    return 0;
}
