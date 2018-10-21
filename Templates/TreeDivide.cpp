// P2325
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
const int size = 1005;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int B, st[size], top = 0, ccnt = 0, rt[size],
                 col[size];
void DFS(int u, int p) {
    int pos = top;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            DFS(v, u);
            if(top - pos >= B) {
                rt[++ccnt] = u;
                while(top != pos)
                    col[st[top--]] = ccnt;
            }
        }
    }
    st[++top] = u;
}
int main() {
    int n = read();
    B = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    DFS(1, 0);
    while(top)
        col[st[top--]] = ccnt;
    printf("%d\n", ccnt);
    for(int i = 1; i <= n; ++i)
        printf("%d ", col[i]);
    puts("");
    for(int i = 1; i <= ccnt; ++i)
        printf("%d ", rt[i]);
    puts("");
    return 0;
}
