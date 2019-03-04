#include <cstdio>
#include <cstring>
#include <vector>
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
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int crt, msiz, tsiz, siz[size];
bool vis[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int csiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            csiz = std::max(csiz, siz[v]);
        }
    }
    csiz = std::max(csiz, tsiz - siz[u]);
    if(csiz < msiz)
        msiz = csiz, crt = u;
}
int getRoot(int u, int usiz) {
    msiz = 1 << 30, tsiz = usiz;
    getRootImpl(u, 0);
    return crt;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 ans;
int m;
char S[size], P[size];
typedef std::vector<int> Arr;
void extend(Arr& arr, int siz) {
    if(arr.size() < siz)
        arr.resize(siz);
}
void reduce(Arr& arr) {
    while(arr.size() && arr.back() == 0)
        arr.pop_back();
}
Arr cacheA[size], cacheB[size];
int cacheASiz[size], cacheBSiz[size], rsiz[size];
void reset(int n) {
    cnt = 0;
    memset(last + 1, 0, sizeof(int) * n);
    memset(vis + 1, 0, sizeof(bool) * n);
    memset(cacheASiz + 1, 0, sizeof(int) * n);
    memset(cacheBSiz + 1, 0, sizeof(int) * n);
}
const Arr& DFSA(int u, int p) {
    Arr& cur = cacheA[u];
    if(cacheASiz[u] == rsiz[u])
        return cur;
    cur.clear();
    cacheASiz[u] = rsiz[u];
    if(S[u] == P[1]) {
        extend(cur, 2);
        cur[1] = 1;
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            const Arr& av = DFSA(v, u);
            extend(cur, std::min(m, static_cast<int>(
                                        av.size())) +
                       1);
            for(int j = 1; j < av.size(); ++j) {
                int nxt = j == m ? 1 : j + 1;
                if(av[j] && S[u] == P[nxt])
                    cur[nxt] += av[j];
            }
        }
    }
    reduce(cur);
    return cur;
}
const Arr& DFSB(int u, int p) {
    Arr& cur = cacheB[u];
    if(cacheBSiz[u] == rsiz[u])
        return cur;
    cur.clear();
    cacheBSiz[u] = rsiz[u];
    if(S[u] == P[m]) {
        cur.resize(2);
        cur[1] = 1;
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            const Arr& av = DFSB(v, u);
            extend(cur, std::min(m, static_cast<int>(
                                        av.size())) +
                       1);
            for(int j = 1; j < av.size(); ++j) {
                int nxt = j == m ? 1 : j + 1;
                if(av[j] && S[u] == P[m + 1 - nxt])
                    cur[nxt] += av[j];
            }
        }
    }
    reduce(cur);
    return cur;
}
int prev(int x) {
    --x;
    return x ? x : m;
}
int next(int x) {
    ++x;
    return x <= m ? x : 1;
}
void calcSiz(int u, int p) {
    rsiz[u] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            calcSiz(v, u);
            rsiz[u] += rsiz[v];
        }
    }
}
void solve(int u) {
    calcSiz(u, 0);
    std::vector<Arr> arrs;
    Arr sum;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            const Arr& ca = DFSA(v, u);
            arrs.push_back(ca);
            extend(sum, ca.size());
            for(int j = 1; j < ca.size(); ++j)
                sum[j] += ca[j];
        }
    }
    if(sum.size() >= m && P[m] == S[u])
        ans += sum[m - 1];
    for(int i = last[u], cur = 0; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            const Arr& cb = DFSB(v, u);
            const Arr& now = arrs[cur++];
            if(cb.size() >= m && P[1] == S[u])
                ans += cb[m - 1];
            for(int j = 1; j < now.size(); ++j)
                sum[j] -= now[j];
            for(int j = 1, k = prev(prev(m));
                j < cb.size(); ++j, k = prev(k)) {
                if(S[u] == P[next(k)] &&
                   k < sum.size())
                    ans += asInt64(cb[j]) * sum[k];
            }
            for(int j = 1; j < now.size(); ++j)
                sum[j] += now[j];
        }
    }
}
void divide(int u) {
    vis[u] = true;
    solve(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int nrt = getRoot(v, siz[v]);
            divide(nrt);
        }
    }
}
Int64 foo() {
    int n = read();
    reset(n);
    m = read();
    scanf("%s", S + 1);
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    scanf("%s", P + 1);
    ans = 0;
    divide(getRoot(1, n));
    return ans;
}
int main() {
    int t = read();
    for(int i = 0; i < t; ++i)
        printf("%lld\n", foo());
    return 0;
}
