#include <algorithm>
#include <cstdio>
#include <cstdlib>
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
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int siz[size], son[size], p[size];
void buildTree(int u) {
    siz[u] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u]) {
            p[v] = u;
            buildTree(v);
            siz[u] += siz[v];
            if(siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}
int top[size], id[size], icnt = 0;
void buildChain(int u) {
    id[u] = ++icnt;
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!id[v]) {
            top[v] = v;
            buildChain(v);
        }
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
    srand(19240817);
    int rt = rand() * 3257 % n + 1;
    buildTree(rt);
    top[rt] = rt;
    buildChain(rt);
    return 0;
}
