#include <algorithm>
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
int id[size], d[size];
namespace Graph {
    struct Edge {
        int to, nxt;
    } E[size * 2];
    int last[size], cnt = 0;
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
    int p[size], son[size];
    int buildTree(int u) {
        int siz = 1, msiz = 0;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(v != p[u]) {
                d[v] = d[u] + 1;
                p[v] = u;
                int vsiz = buildTree(v);
                siz += vsiz;
                if(vsiz > msiz)
                    son[u] = v, msiz = vsiz;
            }
        }
        return siz;
    }
    int top[size], icnt = 0;
    void buildChain(int u) {
        id[u] = ++icnt;
        if(son[u]) {
            top[son[u]] = top[u];
            buildChain(son[u]);
        }
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(!top[v]) {
                top[v] = v;
                buildChain(v);
            }
        }
    }
    int getLCA(int u, int v) {
        while(top[u] != top[v]) {
            int& x = d[top[u]] > d[top[v]] ? u : v;
            x = p[top[x]];
        }
        return d[u] < d[v] ? u : v;
    }
    void init() {
        int n = read();
        for(int i = 1; i < n; ++i) {
            int u = read();
            int v = read();
            addEdge(u, v);
            addEdge(v, u);
        }
        buildTree(1);
        top[1] = 1;
        buildChain(1);
    }
}
struct Edge {
    int to, nxt;
} E[size];
int last[size], lts[size], cnt, ts = 0;
int getLast(int u) {
    if(lts[u] != ts)
        lts[u] = ts, last[u] = 0;
    return last[u];
}
bool mark, flag[size];
void addEdge(int u, int v) {
    if(flag[u] && flag[v] && d[u] + 1 == d[v])
        mark = false;
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = getLast(u);
    last[u] = cnt;
}
int ncnt;
bool DFS(int u) {
    if(flag[u]) {
        for(int i = getLast(u); i; i = E[i].nxt) {
            int v = E[i].to;
            if(DFS(v))
                ++ncnt;
        }
        return true;
    } else {
        int scnt = 0;
        for(int i = getLast(u); i; i = E[i].nxt) {
            int v = E[i].to;
            scnt += DFS(v);
        }
        if(scnt >= 2) {
            ++ncnt;
            return false;
        }
        return scnt;
    }
}
bool cmp(int a, int b) {
    return id[a] < id[b];
}
int A[size], st[size];
int foo() {
    int n = read();
    for(int i = 1; i <= n; ++i) {
        A[i] = read();
        flag[A[i]] = true;
    }
    std::sort(A + 1, A + n + 1, cmp);
    cnt = 0, ++ts, mark = true;
    int top = 1;
    st[top] = A[1];
    for(int i = 2; i <= n && mark; ++i) {
        int u = A[i], lca = Graph::getLCA(u, st[top]);
        while(top > 1 && d[st[top - 1]] > d[lca]) {
            addEdge(st[top - 1], st[top]);
            --top;
        }
        if(d[st[top]] > d[lca]) {
            addEdge(lca, st[top]);
            --top;
        }
        if(top == 0 || d[st[top]] < d[lca])
            st[++top] = lca;
        st[++top] = u;
    }
    while(top > 1 && mark) {
        addEdge(st[top - 1], st[top]);
        --top;
    }
    if(mark) {
        ncnt = 0;
        DFS(st[1]);
    }
    for(int i = 1; i <= n; ++i)
        flag[A[i]] = false;
    return mark ? ncnt : -1;
}
int main() {
    Graph::init();
    int q = read();
    while(q--)
        printf("%d\n", foo());
    return 0;
}
