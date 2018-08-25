// CF600E
// TODO:judge
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
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int c[size], L[size], R[size], idc[size], icnt = 0, son[size];
int DFSA(int u, int p) {
    L[u] = ++icnt;
    idc[icnt] = c[u];
    int siz = 1, mcs = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            int sizv = DFSA(v, u);
            siz += sizv;
            if(sizv > mcs)
                son[u] = v, mcs = sizv;
        }
    }
    R[u] = icnt;
    return siz;
}
int ccnt[size], maxcnt = 0;
long long sum = 0, ans[size];
void add(int c) {
    ++ccnt[c];
    if(ccnt[c] > maxcnt) {
        maxcnt = ccnt[c];
        sum = 0;
    }
    if(ccnt[c] == maxcnt)
        sum += c;
}
void DFSB(int u, int p, bool erase) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && v != son[u])
            DFSB(v, u, true);
    }
    if(son[u])
        DFSB(son[u], u, false);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && v != son[u]) {
            for(int j = L[v]; j <= R[v]; ++j)
                add(idc[j]);
        }
    }
    add(c[u]);
    ans[u] = sum;
    if(erase) {
        for(int i = L[u]; i <= R[u]; ++i)
            --ccnt[idc[i]];
        maxcnt = sum = 0;
    }
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        c[i] = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    DFSA(1, 0);
    DFSB(1, 0, false);
    for(int i = 1; i <= n; ++i)
        printf("%lld ", ans[i]);
    putchar('\n');
    return 0;
}
