#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
namespace IO {
    char in[1 << 19], *S;
    void init() {
        fread(in, 1, sizeof(in), stdin);
        S = in;
    }
    int scanInt() {
        return strtol(S, &S, 10);
    }
    void scanMat(char* out, int n, int m) {
        for(int i = 0; i < n; ++i) {
            S += (*S == '\r' ? 2 : 1);
            memcpy(out, S, m);
            out += m, S += m;
        }
    }
}
const int size = 100005;
struct Edge {
    int to, nxt, f;
} E[size * 8];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v) {
    addEdgeImpl(u, v, 1);
    addEdgeImpl(v, u, 0);
}
int d[size], q[size], S, T;
bool BFS(int siz) {
    memset(d + 1, -1, sizeof(int) * siz);
    d[S] = 0, q[0] = S;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
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
int now[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] == d[u] + 1 &&
           (k = DFS(v, std::min(f, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, f -= k;
            if(f == 0)
                break;
        }
    }
    if(res == 0)
        d[u] = -1;
    return res;
}
int dinic(int siz) {
    int res = 0;
    while(BFS(siz)) {
        memcpy(now + 1, last + 1, sizeof(int) * siz);
        res += DFS(S, 1 << 30);
    }
    return res;
}
char map[size];
int id[size];
int main() {
    IO::init();
    int n = IO::scanInt();
    int m = IO::scanInt();
    IO::scanMat(map, n, m);
    int siz = n * m, res = 0, icnt = 0;
    for(int i = 0; i < siz; ++i) {
        if(map[i] == '2')
            ++res;
        else if(map[i] != '*')
            id[i] = ++icnt;
    }
    S = ++icnt;
    T = ++icnt;
    for(int i = 0, p = 0; i < n; ++i)
        for(int j = 0; j < m; ++j, ++p) {
            char cu = map[p];
            if(!(cu & 1))
                continue;
            int cid = id[p];
            if(cu == '1')
                addEdge(S, cid);
            else
                addEdge(cid, T);
            if(cu == '1') {
                if(j && map[p - 1] == '3')
                    addEdge(cid, id[p - 1]);
                if(j != m - 1 && map[p + 1] == '3')
                    addEdge(cid, id[p + 1]);
                if(i && map[p - m] == '3')
                    addEdge(cid, id[p - m]);
                if(i != n - 1 && map[p + m] == '3')
                    addEdge(cid, id[p + m]);
            }
        }
    printf("%d\n", res + dinic(icnt));
    return 0;
}
