#include <cstdio>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 100005, maxS = size * 2;
struct SAM {
    struct State {
        int len, link, nxt[10];
    } st[maxS * 20];
    int siz;
    SAM() {
        siz = 1;
    }
    int extend(int c, int last) {
        int id = ++siz;
        st[id].len = st[last].len + 1;
        int p = last;
        while (p && !st[p].nxt[c]) {
            st[p].nxt[c] = id;
            p = st[p].link;
        }
        if (p) {
            int q = st[p].nxt[c];
            if (st[p].len + 1 == st[q].len)
                st[id].link = q;
            else {
                int cq = ++siz;
                st[cq] = st[q];
                st[cq].len = st[p].len + 1;
                while (p && st[p].nxt[c] == q) {
                    st[p].nxt[c] = cq;
                    p = st[p].link;
                }
                st[q].link = st[id].link = cq;
            }
        } else
            st[id].link = 1;
        return id;
    }
    long long count() const {
        long long res = 0;
        for (int i = 1; i <= siz; ++i) res += st[i].len - st[st[i].link].len;
        return res;
    }
} sam;
struct Edge {
    int to, next;
} E[size * 2];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u];
    last[u] = cnt;
}
char val[size];
void DFS(int u, int p, int src) {
    int id = sam.extend(val[u], src);
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (v != p) DFS(v, u, id);
    }
}
int in[size] = {};
int main() {
    int n = read();
    int c = read();
    for (int i = 1; i <= n; ++i) {
        val[i] = getchar() - '0';
        getchar();
    }
    for (int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
        ++in[u], ++in[v];
    }
    for (int i = 1; i <= n; ++i)
        if (in[i] == 1)
            DFS(i, 0, 1);
    printf("%lld\n", sam.count());
    return 0;
}
