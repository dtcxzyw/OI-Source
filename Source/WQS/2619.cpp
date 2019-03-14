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
const int size = 50005;
struct Edge {
    int u, v, w, c, rw;
    bool operator<(const Edge& rhs) const {
        return rw != rhs.rw ? rw < rhs.rw : c < rhs.c;
    }
} E[2 * size];
int fa[size];
int find(int x) {
    return fa[x] != -1 ? fa[x] = find(fa[x]) : x;
}
std::pair<int, int> solve(int n, int m, int k) {
    memset(fa, -1, sizeof(int) * n);
    for(int i = 0; i < m; ++i)
        E[i].rw = E[i].w + (E[i].c ? 0 : k);
    std::sort(E, E + m);
    int sumw = 0, wcnt = 0;
    for(int i = 0; i < m; ++i) {
        int u = find(E[i].u), v = find(E[i].v);
        if(u != v) {
            sumw += E[i].rw;
            wcnt += (E[i].c == 0);
            fa[u] = v;
        }
    }
    return std::make_pair(wcnt, sumw);
}
int main() {
    int n = read();
    int m = read();
    int c = read();
    for(int i = 0; i < m; ++i) {
        E[i].u = read();
        E[i].v = read();
        E[i].w = read();
        E[i].c = read();
    }
    const int range = 100;
    int l = -range, r = range, ans;
    while(l <= r) {
        int mid = (l + r) >> 1;
        std::pair<int, int> res = solve(n, m, mid);
        if(res.first >= c)
            l = mid + 1, ans = res.second - mid * c;
        else
            r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}
