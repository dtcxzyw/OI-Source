#include <algorithm>
#include <cmath>
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
typedef double FT;
const FT eps = 1e-8;
const int size = 35, l = size, r = 2 * size * size,
          vsiz = l + r + 2, esiz = l + r + l * r,
          S = vsiz - 1, T = S - 1;
struct Edge {
    int to, nxt;
    FT f;
} E[esiz * 2];
int last[vsiz], cnt;
void addEdgeImpl(int u, int v, FT f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, FT f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
int d[vsiz], q[vsiz];
bool BFS(int siz) {
    memset(d, -1, sizeof(int) * siz);
    int b = 0, e = 1;
    q[b] = S;
    d[S] = 0, d[T] = -1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].f > eps && d[v] == -1) {
                d[v] = d[u] + 1;
                if(v == T)
                    return true;
                q[e++] = v;
            }
        }
    }
    return false;
}
int now[vsiz];
FT DFS(int u, FT f) {
    if(u == T || f < eps)
        return f;
    FT res = 0.0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] == d[u] + 1 &&
           (k = DFS(v, std::min(f, E[i].f))) > eps) {
            E[i].f -= k;
            E[i ^ 1].f += k;
            res += k;
            f -= k;
            if(f < eps)
                break;
        }
    }
    if(res < eps)
        d[u] = -1;
    return res;
}
FT dinic(int siz) {
    FT res = 0.0;
    while(BFS(siz)) {
        memcpy(now, last, sizeof(int) * siz);
        now[S] = last[S];
        res += DFS(S, 1e20);
    }
    return res;
}
struct Info {
    int p, b, e;
} A[size];
int s[size];
FT tp[size * 2];
bool cmpEq(FT a, FT b) {
    return fabs(a - b) < eps;
}
bool cmpLeq(FT a, FT b) {
    return a - eps < b;
}
bool check(int n, int m, FT dT, int tot) {
    memset(last, 0, sizeof(last));
    cnt = 1;
    int dcnt = 0;
    for(int i = 0; i < n; ++i) {
        addEdge(S, i, A[i].p);
        tp[dcnt++] = A[i].b;
        tp[dcnt++] = A[i].e + dT;
    }
    int cid = n;
    std::sort(tp, tp + dcnt);
    dcnt = std::unique(tp, tp + dcnt, cmpEq) - tp;
    for(int i = 1; i < dcnt; ++i) {
        FT delta = tp[i] - tp[i - 1];
        for(int j = 0; j < m; ++j) {
            int id = cid++;
            if(s[j]) {
                FT fac = delta * s[j];
                addEdge(id, T, fac * (j + 1));
                for(int k = 0; k < n; ++k)
                    if(cmpLeq(A[k].b, tp[i - 1]) &&
                       cmpLeq(tp[i], A[k].e + dT))
                        addEdge(k, id, fac);
            }
        }
    }
    return cmpEq(dinic(cid), tot);
}
bool cmpGe(int a, int b) {
    return a > b;
}
FT foo() {
    int n = read();
    int m = read();
    int tot = 0;
    for(int i = 0; i < n; ++i) {
        A[i].p = read();
        tot += A[i].p;
        A[i].b = read();
        A[i].e = read();
    }
    for(int i = 0; i < m; ++i)
        s[i] = read();
    s[m] = 0;
    std::sort(s, s + m, cmpGe);
    for(int i = 0; i < m; ++i)
        s[i] -= s[i + 1];
    FT l = 0.0, r = 3e6;
    while(r - l > eps) {
        FT mid = (l + r) * 0.5;
        if(check(n, m, mid, tot))
            r = mid;
        else
            l = mid;
    }
    return l;
}
int main() {
    int t = read();
    while(t--)
        printf("%.6lf\n", foo());
    return 0;
}
