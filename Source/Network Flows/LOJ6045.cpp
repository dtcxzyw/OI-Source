#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 305, inf = 1 << 30;
namespace Match {
    struct Edge {
        int to, nxt;
    } E[size * size];
    int last[size], cnt = 0;
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
    int pair[size], flag[size], ts = 0;
    bool match(int u) {
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(flag[v] != ts) {
                flag[v] = ts;
                if(!pair[v] || match(pair[v])) {
                    pair[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    void calcMatch(int n) {
        for(int i = 1; i <= n; ++i) {
            ++ts;
            match(i);
        }
    }
}
struct Edge {
    int to, nxt, f;
} E[size * size * 2];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
int S, T, gap[size], d[size], q[size];
void BFS() {
    q[0] = T, gap[1] = 1, d[T] = 1;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(!d[v]) {
                d[v] = d[u] + 1;
                ++gap[d[v]];
                q[e++] = v;
            }
        }
    }
}
int now[size];
int mini(int a, int b) {
    return a < b ? a : b;
}
int aug(int u, int mf) {
    if(u == T || mf == 0)
        return mf;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[u] == d[v] + 1 &&
           (k = aug(v, mini(mf, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, mf -= k;
            if(!mf)
                return res;
        }
    }
    if(--gap[d[u]] == 0)
        d[S] = T + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int ISAP() {
    BFS();
    memcpy(now + 1, last + 1, sizeof(int) * T);
    int res = 0;
    while(d[S] <= T)
        res += aug(S, inf);
    return res;
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i) {
        int t = read();
        while(t--) {
            int v = read();
            Match::addEdge(i, v);
        }
    }
    Match::calcMatch(n);
    S = n + 1, T = S + 1;
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = Match::last[i]; j;
            j = Match::E[j].nxt) {
            int v = Match::E[j].to;
            addEdge(i, Match::pair[v], inf);
        }
        int w = read();
        if(w < 0) {
            addEdge(S, i, -w);
            res -= w;
        } else
            addEdge(i, T, w);
    }
    printf("%d\n", -(res - ISAP()));
    return 0;
}
