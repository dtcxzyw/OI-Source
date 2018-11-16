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
const int size = 1205, esiz = size * 100;
struct Edge {
    int to, nxt, f;
} E[esiz * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
int q[size], d[size], S, T, endPos;
bool BFS(int siz) {
    memset(d + 1, -1, sizeof(int) * siz);
    d[S] = 0, q[0] = S;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i > endPos;
            i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].f && d[v] == -1) {
                d[v] = d[u] + 1;
                if(v == T)
                    return true;
                q[e++] = v;
            }
        }
    }
    return false;
}
int now[size], neg[esiz * 2];
int DFS(int u, int mf) {
    if(u == T || mf == 0)
        return mf;
    int res = 0, k;
    for(int& i = now[u]; i > endPos; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] == d[u] + 1 &&
           (k = DFS(v, std::min(mf, E[i].f)))) {
            E[i].f -= k, E[neg[i]].f += k;
            res += k, mf -= k;
            if(mf == 0)
                break;
        }
    }
    if(res == 0)
        d[u] = -1;
    return res;
}
int res = 0;
void dinic(int siz) {
    while(BFS(siz)) {
        memcpy(now + 1, last + 1, sizeof(int) * siz);
        res += DFS(S, 2147483647);
    }
}
struct Info {
    int u, v, w;
    bool operator<(const Info& rhs) const {
        return w < rhs.w;
    }
} A[esiz];
int ep[2][35];
int main() {
    int n = read();
    int m = read();
    S = read();
    T = read();
    for(int i = 0; i < m; ++i) {
        A[i].u = read();
        A[i].v = read();
        A[i].w = read();
    }
    std::sort(A, A + m);
    for(int t = 1; t >= 0; --t) {
        for(int c = 0, i = 0; c <= 30; ++c) {
            ep[t][c] = cnt;
            while(i < m && (A[i].w >> (c + 1)) == 0) {
                if(t) {
                    addEdge(A[i].v, A[i].u, 0);
                    neg[cnt] = cnt + m;
                } else {
                    addEdge(A[i].u, A[i].v, A[i].w);
                    neg[cnt] = cnt - m;
                }
                ++i;
            }
        }
    }
    int lep = 1 << 30;
    for(int t = 0; t <= 1; ++t) {
        for(int c = 30; c >= 0; --c) {
            endPos = ep[t][c];
            if(lep != endPos) {
                dinic(n);
                lep = endPos;
            }
        }
    }
    printf("%d\n", res);
    return 0;
}
