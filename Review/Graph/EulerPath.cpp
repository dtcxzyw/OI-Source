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
const int size = 100005;
struct Edge {
    int to, nxt;
} E[size * 4];
int last[size], cnt;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int q[size * 2], qcnt = 0;
void DFS1(int u) {
    for(int& i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v) {
            E[i].to = E[i ^ 1].to = 0;
            int eid = i;
            DFS1(v);
            int reid = eid >> 1;
            q[++qcnt] = (eid & 1 ? reid : -reid);
        }
    }
}
int in[size], out[size];
bool foo1(int n, int m) {
    cnt = 1;
    for(int i = 0; i < m; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
        ++in[v], ++in[u];
    }
    for(int i = 1; i <= n; ++i)
        if(in[i] & 1)
            return false;
    for(int i = 1; i <= n; ++i)
        if(in[i]) {
            DFS1(i);
            break;
        }
    if(qcnt != m)
        return false;
    puts("YES");
    for(int i = 1; i <= m; ++i)
        printf("%d ", q[i]);
    return true;
}
void DFS2(int u) {
    for(int& i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v) {
            E[i].to = 0;
            int eid = i;
            DFS2(v);
            q[++qcnt] = eid;
        }
    }
}
bool foo2(int n, int m) {
    cnt = 0;
    for(int i = 0; i < m; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        ++out[u], ++in[v];
    }
    for(int i = 1; i <= n; ++i)
        if(in[i] != out[i])
            return false;
    for(int i = 1; i <= n; ++i)
        if(in[i]) {
            DFS2(i);
            break;
        }
    if(qcnt != m)
        return false;
    puts("YES");
    for(int i = m; i >= 1; --i)
        printf("%d ", q[i]);
    return true;
}
int main() {
    int t = read();
    int n = read();
    int m = read();
    if(!(t == 1 ? foo1(n, m) : foo2(n, m)))
        puts("NO");
    puts("");
    return 0;
}
