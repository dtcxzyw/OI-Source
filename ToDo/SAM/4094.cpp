#include <algorithm>
#include <cstdio>
const int size = 100005, maxS = size * 2;
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
struct SAM {
    struct State {
        int len, link, nxt[26];
    } st[maxS];
    int siz, last;
    SAM() {
        siz = last = 1;
    }
    void extend(int c) {
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
        last = id;
    }
} sam;
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
int find(int u, int len) {
    for (int i = 19; i >= 0; --i) {
        int v = p[u][i];
        if (sam.st[v].len >= len)
            u = v;
    }
    return u;
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
int root[maxS] = {}, pid[size], len[maxS];
bool check(int end, int len, int a, int b, int n) {
    int p = find(pid[end], len);
    return query(1, n, root[R[p]], root[L[p] - 1], a + len - 1, b);
}
char buf[size];
int main() {
    int n = read();
    int m = read();
    scanf("%s", buf);
    for (int i = 1; i <= n; ++i) {
        sam.extend(buf[n - i] - 'a');
        int l = sam.st[sam.last].len;
        pid[l] = sam.last;
        len[sam.last] = l;
    }
    for (int i = 2; i <= sam.siz; ++i) addEdge(sam.st[i].link, i);
    DFS(1);
    for (int i = 1; i <= sam.siz; ++i) {
        root[i] = root[i - 1];
        if (len[id[i]]) root[i] = insert(1, n, root[i], len[id[i]]);
    }
    int inv = n + 1;
    while (m--) {
        int b = inv - read();
        int a = inv - read();
        int d = inv - read();
        int c = inv - read();
        int l = 1, r = std::min(b - a, d - c) + 1, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(d, mid, a, b, n))
                l = mid + 1, ans = mid;
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
