#include <csetjmp>
#include <cstdio>
#include <cstring>
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
const int maxn = 2005, maxm = 6005;
struct Edge {
    int to, nxt, w;
} E[maxm];
int cnt, last[maxn];
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int dis[maxn], n;
bool flag[maxn];
jmp_buf buf;
bool pre(int u) {
    int cd = dis[u];
    flag[u] = true;
    bool res = false;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to, nd = cd + E[i].w;
        if(dis[v] > nd) {
            if(flag[v])
                longjmp(buf, 1);
            dis[v] = nd;
            pre(v);
            res = true;
            break;
        }
    }
    flag[u] = false;
    return res;
}
void DFS(int u, int d) {
    if(d) {
        flag[u] = true;
        int cd = dis[u];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to, nd = cd + E[i].w;
            if(dis[v] > nd) {
                if(flag[v])
                    longjmp(buf, 1);
                dis[v] = nd;
                DFS(v, d - 1);
            }
        }
        flag[u] = false;
    }
}
bool vis[maxn];
void color(int u) {
    vis[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v])
            color(v);
    }
}
bool foo() {
    n = read();
    int m = read();
    memset(last, 0, sizeof(int) * (n + 1));
    memset(dis, 0, sizeof(int) * (n + 1));
    memset(flag, 0, sizeof(bool) * (n + 1));
    memset(vis, 0, sizeof(bool) * (n + 1));
    cnt = 0;
    while(m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        if(w >= 0)
            addEdge(v, u, w);
    }
    color(1);
    switch(setjmp(buf)) {
        case 0: {
            for(int i = 1; i <= n; ++i)
                if(vis[i])
                    while(pre(i))
                        ;
            for(int k = 1; k <= n * 2; k <<= 1)
                for(int i = 1; i <= n; ++i)
                    if(vis[i])
                        DFS(i, k);
        } break;
        case 1:
            return true;
    }
    return false;
}
int main() {
    int t = read();
    while(t--)
        puts(foo() ? "YE5" : "N0");
    return 0;
}
