// SP12056
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
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
const int size = 305;
struct Edge {
    int to, nxt, w;
} E[100005];
int last[size], cnt;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int fa[size], nxt[size];
template <typename T>
void reset(T* arr, int siz) {
    memset(arr + 1, 0, sizeof(T) * siz);
}
void init(int n) {
    cnt = 0;
    reset(last, n);
    reset(fa, n);
    reset(nxt, n);
}
int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}
void merge(int u, int v) {
    int p = u;
    while(nxt[p])
        p = nxt[p];
    nxt[p] = v;
    fa[v] = u;
}
int w[size];
bool flag[size];
struct Info {
    int id, f;
    Info(int id) : id(id), f(w[id]) {}
    bool operator<(const Info& rhs) const {
        return f < rhs.f;
    }
};
int solveImpl(int n, int cnt, int& s, int& t) {
    reset(w, n);
    reset(flag, n);
    t = 1;
    std::priority_queue<Info> heap;
    while(cnt--) {
        s = t;
        flag[s] = true;
        for(int i = s; i; i = nxt[i]) {
            for(int j = last[i]; j; j = E[j].nxt) {
                int v = find(E[j].to);
                if(!flag[v]) {
                    w[v] += E[j].w;
                    heap.push(v);
                }
            }
        }
        t = 0;
        while(!t) {
            if(heap.empty())
                return 0;
            Info info = heap.top();
            heap.pop();
            if(w[info.id] == info.f)
                t = info.id;
        }
    }
    merge(s, t);
    return w[t];
}
int solve(int n) {
    int res = 1 << 30, s, t;
    for(int i = n - 1; i && res; --i)
        res = std::min(res, solveImpl(n, i, s, t));
    return res;
}
int main() {
    while(true) {
        int n = read();
        int m = read();
        read();
        if(n == 0)
            break;
        init(n);
        while(m--) {
            int u = read();
            int v = read();
            int w = read();
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        printf("%d\n", solve(n));
    }
    return 0;
}
