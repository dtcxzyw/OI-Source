#include <cstdio>
#include <cstring>
const int size = 100005;
int add(int a, int b, int p) {
    a += b;
    return a < p ? a : a - p;
}
int pos[size], fa[size];
int find(int u) {
    return fa[u] == u ? u : fa[u] = find(fa[u]);
}
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u != v)
        fa[u] = v;
}
bool flag[size];
int foo() {
    int n, s, q, p, m, d;
    scanf("%d%d%d%d%d%d", &n, &s, &q, &p, &m, &d);
    for(int i = 0; i < n; ++i)
        fa[i] = i;
    memset(flag, 0, n);
    pos[0] = s;
    flag[s] = true;
    d %= n;
    merge(s, add(s, d, n));
    long long c = 0;
    for(int i = 1; i < n; ++i) {
        c = (c * q + p) % m;
        int now = c % n;
        while(flag[find(now)]) {
            ++now;
            if(now == n)
                now = 0;
        }
        int x = find(now);
        flag[x] = true;
        pos[i] = x;
        merge(x, add(x, d, n));
    }
    memset(flag, 0, n);
    int ans = 0;
    for(int i = 0; i < n; ++i)
        if(!flag[i]) {
            int c = i, cnt = 0;
            bool old = flag[0];
            while(!flag[c]) {
                flag[c] = true;
                ++cnt;
                c = pos[c];
            }
            if(cnt > 1)
                ans += cnt + (flag[0] == old ? 1 : -1);
        }
    return ans;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--)
        printf("%d\n", foo());
    return 0;
}
