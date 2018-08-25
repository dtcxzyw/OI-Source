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
int getAlpha() {
    int c;
    do
        c = getchar();
    while(c < 'a' || c > 'v');
    return c - 'a';
}
const int size = 500005, ninf = 0xc0c0c0c0;
struct Edge {
    int to, nxt;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int mask[size], L[size], R[size], id[size], icnt = 0, son[size],
                                            d[size];
int DFSA(int u, int p) {
    L[u] = ++icnt;
    id[icnt] = u;
    int siz = 1, mcs = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            mask[v] ^= mask[u];
            d[v] = d[u] + 1;
            int sizv = DFSA(v, u);
            siz += sizv;
            if(sizv > mcs)
                son[u] = v, mcs = sizv;
        }
    }
    R[u] = icnt;
    return siz;
}
int ans[size], maxd[1 << 22], cur = 0, offset;
void update(int u) {
    int k = maxd[mask[u]];
    for(int i = 0; i < 22; ++i)
        k = std::max(k, maxd[mask[u] ^ (1 << i)]);
    cur = std::max(cur, k + d[u] + offset);
}
void modify(int u) {
    int st = mask[u];
    maxd[st] = std::max(maxd[st], d[u]);
}
void DFSB(int u, int p, bool erase) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && v != son[u])
            DFSB(v, u, true);
    }
    if(son[u])
        DFSB(son[u], u, false);
    offset = -(d[u] << 1);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && v != son[u]) {
            for(int j = L[v]; j <= R[v]; ++j)
                update(id[j]);
            for(int j = L[v]; j <= R[v]; ++j)
                modify(id[j]);
        }
    }
    update(u);
    modify(u);
    ans[u] = cur;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p)
            ans[u] = std::max(ans[u], ans[v]);
    }
    if(erase) {
        for(int i = L[u]; i <= R[u]; ++i)
            maxd[mask[id[i]]] = ninf;
        cur = 0;
    }
}
int main() {
    int n = read();
    for(int i = 2; i <= n; ++i) {
        addEdge(read(), i);
        mask[i] = 1 << getAlpha();
    }
    DFSA(1, 0);
    memset(maxd, 0xc0, sizeof(maxd));
    DFSB(1, 0, false);
    for(int i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    putchar('\n');
    return 0;
}
