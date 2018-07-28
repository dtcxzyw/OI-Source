#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 500005, maxS = size * 2;
struct SAM {
    struct State {
        int len, link, pos, nxt[26];
    } st[maxS];
    int siz, last;
    SAM() {
        siz = last = 1;
    }
    void reset() {
        memset(st + 1, 0, sizeof(State) * siz);
        siz = last = 1;
    }
    void extend(int c) {
        int id = ++siz;
        memset(st + id, 0, sizeof(State));
        st[id].pos = st[id].len = st[last].len + 1;
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
        last = id;
    }
} samA, samB;
struct Edge {
    int to, nxt;
} E[maxS];
int last[maxS] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int p[maxS][20], L[maxS], R[maxS], id[maxS], icnt = 0;
void DFS(int u) {
    L[u] = ++icnt;
    id[icnt] = u;
    for (int i = 1; i < 20; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];
    for (int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        p[v][0] = u;
        DFS(v);
    }
    R[u] = icnt;
}
struct Node {
    int ls, rs, siz;
} T[maxS * 20];
int ncnt = 0;
int insert(int l, int r, int src, int p) {
    int id = ++ncnt;
    T[id] = T[src];
    ++T[id].siz;
    if (l != r) {
        int m = (l + r) >> 1;
        if (p <= m)
            T[id].ls = insert(l, m, T[id].ls, p);
        else
            T[id].rs = insert(m + 1, r, T[id].rs, p);
    }
    return id;
}
bool query(int l, int r, int a, int b, int nl, int nr) {
    int delta = T[a].siz - T[b].siz;
    if (delta == 0) return false;
    if (nl <= l && r <= nr) return delta;
    int m = (l + r) >> 1;
    return (nl <= m && query(l, m, T[a].ls, T[b].ls, nl, nr)) || (m < nr && query(m + 1, r, T[a].rs, T[b].rs, nl, nr));
}
int root[maxS] = {}, pid[size], len[maxS], limit[size];
char buf[size];
int main() {
    scanf("%s", buf);
    int n = 0;
    for (int i = 0; buf[i]; ++i) {
        samA.extend(buf[i] - 'a');
        pid[i + 1] = samA.last;
        n = len[samA.last] = i + 1;
    }
    for (int i = 2; i <= samA.siz; ++i) addEdge(samA.st[i].link, i);
    DFS(1);
    for (int i = 1; i <= samA.siz; ++i) {
        root[i] = root[i - 1];
        if (len[id[i]]) root[i] = insert(1, n, root[i], len[id[i]]);
    }
    int t;
    scanf("%d", &t);
    while (t--) {
        samB.reset();
        int l, r;
        scanf("%s%d%d", buf, &l, &r);
        int clen = 0, p = 1;
        for (int i = 0; buf[i]; ++i) {
            int c = buf[i] - 'a';
            samB.extend(c);
            while (true) {
                int nxt = samA.st[p].nxt[c];
                if (nxt && query(1, n, root[R[nxt]], root[L[nxt] - 1], l + clen, r)) {
                    ++clen;
                    p = nxt;
                    break;
                }
                if (clen == 0) break;
                int fa = samA.st[p].link;
                if (--clen == samA.st[fa].len) p = fa;
            }
            limit[i + 1] = clen;
        }
        long long ans = 0;
        for (int i = 2; i <= samB.siz; ++i) {
            int fa = samB.st[i].link;
            int pos = samB.st[i].pos;
            ans += std::max(0, samB.st[i].len - std::max(samB.st[fa].len, limit[pos]));
        }
        printf("%lld\n", ans);
    }
    return 0;
}
