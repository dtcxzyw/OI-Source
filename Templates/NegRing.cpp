#include <csetjmp>
#include <cstdio>
#include <cstring>
#include <ctime>
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
const int maxn = 2005, maxm = 8005;
struct Edge {
    int to, nxt, w;
} E[maxm];
int cnt, last[maxn];
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int dis[maxn], limit;
bool flag[maxn];
jmp_buf buf;
void DFS(int u) {
    if(clock() > limit)
        longjmp(buf, 1);
    int cd = dis[u];
    flag[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to, nd = cd + E[i].w;
        if(dis[v] > nd) {
            dis[v] = nd;
            if(flag[v])
                longjmp(buf, 2);
            else
                DFS(v);
        }
    }
    flag[u] = false;
}
int q[maxn], vis[maxn];
bool BFS(int n) {
    memset(dis, 0x3f, sizeof(int) * (n + 1));
    memset(vis, 0, sizeof(int) * (n + 1));
    memset(flag, 0, sizeof(bool) * (n + 1));
    int b = 0, e = 1;
    q[b] = 0, dis[0] = 0, flag[0] = true;
    while(b != e) {
        int u = q[b++];
        if(b == maxn)
            b = 0;
        flag[u] = false;
        int cd = dis[u];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to, nd = cd + E[i].w;
            if(dis[v] > nd) {
                dis[v] = nd;
                if(!flag[v]) {
                    if(++vis[v] >= n)
                        return true;
                    flag[v] = true;
                    q[e++] = v;
                    if(e == maxn)
                        e = 0;
                }
            }
        }
    }
    return false;
}
bool foo() {
    int n = read();
    int m = read();
    memset(last, 0, sizeof(int) * (n + 1));
    memset(dis, 0, sizeof(int) * (n + 1));
    memset(flag, 0, sizeof(bool) * (n + 1));
    cnt = 0;
    while(m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        if(w >= 0)
            addEdge(v, u, w);
    }
    for(int i = 1; i <= n; ++i)
        addEdge(0, i, -1);
    limit = clock() + CLOCKS_PER_SEC / 20;
    switch(setjmp(buf)) {
        case 0:
            DFS(0);
            break;
        case 1:
            return BFS(n);
        case 2:
            return true;
    }
    return false;
}
int main() {
    freopen("testdata.in", "r", stdin);
    int t = read();
    while(t--)
        puts(foo() ? "YE5" : "N0");
    return 0;
}
