#include <cstdio>
#include <set>
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
const int size = 200005;
struct Edge {
    int to, nxt;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
typedef std::multiset<int> Info;
typedef Info::iterator Iter;
void merge(Info& a, Info& b) {
    if(a.size() < b.size())
        a.swap(b);
    a.insert(b.begin(), b.end());
    b.clear();
}
Info dp[size];
int A[size];
void DFS(int u) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        DFS(v);
        merge(dp[u], dp[v]);
    }
    Iter it = dp[u].upper_bound(A[u]);
    if(it != dp[u].end())
        dp[u].erase(it);
    dp[u].insert(A[u]);
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = -read();
    for(int i = 2; i <= n; ++i)
        addEdge(read(), i);
    DFS(1);
    int res = dp[1].size();
    printf("%d\n", res);
    return 0;
}
