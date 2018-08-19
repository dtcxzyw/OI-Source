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
template <typename T>
void memset(T* arr, int siz) {
    memset(arr + 1, 0, sizeof(T) * siz);
}
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = 500005, mod = 998244353;
int h[size];
int getH(int x) {
    static int cur = 1;
    while(cur < x) {
        ++cur;
        h[cur] = (h[cur - 1] + h[cur - 2] * asInt64(cur - 1)) % mod;
    }
    return h[x];
}
struct Edge {
    int to, nxt;
} E[size << 2];
int last[size], cnt;
void initGraph(int n) {
    memset(last, n);
    cnt = 1;
}
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
bool flag[size];
int p[size], d[size], id[size], icnt;
void DFS(int u) {
    id[++icnt] = u;
    flag[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!flag[v]) {
            d[v] = d[u] + 1;
            p[v] = u;
            DFS(v);
        }
    }
}
int tag[size];
bool graph2Forest(int n) {
    icnt = 0;
    memset(flag, n);
    DFS(1);
    memset(tag, n);
    for(int i = 1; i <= cnt; i += 2) {
        int u = E[i].to, v = E[i ^ 1].to;
        if(d[u] < d[v])
            std::swap(u, v);
        if(p[u] != v)
            ++tag[u], --tag[v];
    }
    initGraph(n);
    for(int i = n; i >= 1; --i) {
        int u = id[i];
        tag[p[u]] += tag[u];
        if(tag[u] == 0) {
            if(p[u]) {
                addEdge(u, p[u]);
                addEdge(p[u], u);
            }
        } else if(tag[u] > 1)
            return false;
    }
    return true;
}
Int64 solve(int u, int p) {
    flag[u] = false;
    Int64 res = 1;
    int siz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            res = res * solve(v, u) % mod;
            ++siz;
        }
    }
    return res * getH(p ? siz + 1 : siz) % mod;
}
int foo() {
    int n = read();
    int m = read();
    initGraph(n);
    while(m--) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    if(!graph2Forest(n))
        return 0;
    Int64 res = 1;
    for(int i = 1; i <= n; ++i)
        if(flag[i])
            res = res * solve(i, 0) % mod;
    return res;
}
int main() {
    h[0] = h[1] = 1;
    int t = read();
    while(t--)
        printf("%d\n", foo());
    return 0;
}
