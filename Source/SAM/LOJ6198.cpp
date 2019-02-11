#include <algorithm>
#include <cstdio>
const int size = 100005, maxS = 2 * size;
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
struct SAM {
    struct Node {
        int c[26], len, link;
    } T[maxS];
    int siz, last;
    SAM() : siz(1), last(1) {}
    int extend(int ch) {
        int id = ++siz;
        T[id].len = T[last].len + 1;
        int p = last;
        while(p && !T[p].c[ch]) {
            T[p].c[ch] = id;
            p = T[p].link;
        }
        if(p) {
            int q = T[p].c[ch];
            if(T[q].len == T[p].len + 1)
                T[id].link = q;
            else {
                int cq = ++siz;
                T[cq] = T[q];
                T[cq].len = T[p].len + 1;
                while(p && T[p].c[ch] == q) {
                    T[p].c[ch] = cq;
                    p = T[p].link;
                }
                T[q].link = T[id].link = cq;
            }
        } else
            T[id].link = 1;
        last = id;
        return id;
    }
} sam;
struct Node {
    int c[2];
} T[maxS * 20];
int icnt = 0;
int insert(int val, int d) {
    int id = ++icnt;
    if(d >= 0) {
        int& v = T[id].c[(val >> d) & 1];
        v = insert(val, d - 1);
    }
    return id;
}
int merge(int u, int v) {
    if(u && v) {
        T[u].c[0] = merge(T[u].c[0], T[v].c[0]);
        T[u].c[1] = merge(T[u].c[1], T[v].c[1]);
        return u;
    }
    return u | v;
}
int query(int u, int v, int res, int d) {
    if(u && v && d >= 0) {
        if((2 << d) <= res)
            return 0;
        if(T[u].c[0] && T[v].c[1])
            res =
                std::max(res,
                         query(T[u].c[0], T[v].c[1],
                               res - (1 << d), d - 1) |
                             1 << d);
        if(T[u].c[1] && T[v].c[0])
            res =
                std::max(res,
                         query(T[u].c[1], T[v].c[0],
                               res - (1 << d), d - 1) |
                             1 << d);
        if(T[u].c[0] && T[v].c[0])
            res = std::max(res,
                           query(T[u].c[0], T[v].c[0],
                                 res, d - 1));
        if(T[u].c[1] && T[v].c[1])
            res = std::max(res,
                           query(T[u].c[1], T[v].c[1],
                                 res, d - 1));
        return res;
    }
    return 0;
}
int id[size], root[maxS];
char str[size];
struct Edge {
    int to, nxt;
} E[maxS];
int last[maxS], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int ans = 0, maxd = 0;
void DFS(int u) {
    int base = sam.T[u].len;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        DFS(v);
        ans = std::max(ans,
                       base +
                           query(root[u], root[v],
                                 ans - base, maxd));
        root[u] = merge(root[u], root[v]);
    }
}
int main() {
    int n;
    scanf("%d%s", &n, str);
    for(int i = n - 1; i >= 0; --i)
        id[i] = sam.extend(str[i] - 'a');
    while((2 << maxd) < n)
        ++maxd;
    for(int i = 0; i < n; ++i)
        root[id[i]] = insert(read(), maxd);
    for(int i = 2; i <= sam.siz; ++i)
        addEdge(sam.T[i].link, i);
    DFS(1);
    printf("%d\n", ans);
    return 0;
}
