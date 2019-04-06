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
const int size = 300005;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int C[size], d[size];
void DFS(int u, int p) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            d[v] = d[u] + 1;
            DFS(v, u);
            C[u] += C[v];
        }
    }
}
struct Node {
    int v, end, tag, son, bro;
} T[size];
int tcnt = 0;
void color(int u, int w) {
    T[u].v -= w, T[u].tag += w;
}
void pushDown(int u) {
    if(T[u].tag) {
        color(T[u].bro, T[u].tag);
        color(T[u].son, T[u].tag);
        T[u].tag = 0;
    }
}
int newNode(int val, int end) {
    int id = ++tcnt;
    T[id].v = val, T[id].end = end;
    return id;
}
int merge(int u, int v) {
    if(u && v) {
        pushDown(u);
        pushDown(v);
        if(T[u].v > T[v].v)
            std::swap(u, v);
        T[v].bro = T[u].son;
        T[u].son = v;
        return u;
    }
    return u | v;
}
int mergeBro(int u) {
    int a = T[u].bro, b = T[a].bro;
    if(u && a) {
        pushDown(u);
        pushDown(a);
        T[u].bro = T[a].bro = 0;
        return merge(merge(u, a), mergeBro(b));
    }
    return u;
}
int erase(int u) {
    return mergeBro(T[u].son);
}
int rt[size];
long long res;
void solve(int u, int p) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            solve(v, u);
            rt[u] = merge(rt[u], rt[v]);
        }
    }
    if(u != 1) {
        while(d[T[rt[u]].end] >= d[u])
            rt[u] = erase(rt[u]);
        int sub = T[rt[u]].v;
        color(rt[u], sub);
        res += sub;
    }
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        int c = read();
        ++C[u], --C[v];
        rt[u] = merge(rt[u], newNode(c, v));
    }
    DFS(1, 0);
    for(int i = 2; i <= n; ++i)
        if(C[i] == 0) {
            puts("-1");
            return 0;
        }
    solve(1, 0);
    printf("%lld\n", res);
    return 0;
}
