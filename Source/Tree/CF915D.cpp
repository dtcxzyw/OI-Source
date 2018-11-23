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
const int size = 505, esiz = 100005;
struct Edge {
    int to, nxt;
} E[esiz];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int q[size];
bool topSort(int n, int* in) {
    int qcnt = 0;
    for(int i = 1; i <= n; ++i)
        if(!in[i])
            q[++qcnt] = i;
    for(int i = 1; i <= qcnt; ++i) {
        int u = q[i];
        for(int j = last[u]; j; j = E[j].nxt) {
            int v = E[j].to;
            if(--in[v] == 0)
                q[++qcnt] = v;
        }
    }
    return qcnt == n;
}
int in[size], tmp[size];
bool solve(int n) {
    for(int i = 1; i <= n; ++i)
        if(in[i]) {
            memcpy(tmp + 1, in + 1, sizeof(int) * n);
            --tmp[i];
            if(topSort(n, tmp))
                return true;
        }
    return false;
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        ++in[v];
    }
    puts(solve(n) ? "YES" : "NO");
    return 0;
}
