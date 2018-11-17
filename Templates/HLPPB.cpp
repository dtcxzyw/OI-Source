#include <cstdio>
#include <cstring>
#include <set>
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
const int size = 1205;
struct Edge {
    int to, nxt, w;
} E[240005];
int last[size], cnt = 1;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
const int inf = 2147483647;
std::set<int> dl[size << 1];
std::vector<int> heap[size << 1];
typedef std::multiset<int>::iterator Iter;
int highest = 0, highestInHeap = -1, h[size], f[size],
    q[size];
bool flag[size];
void pre(int n, int t) {
    memset(h, 0x3f, sizeof(h));
    h[t] = 0, flag[t] = true, q[0] = t;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i ^ 1].w && h[v] > h[u] + 1) {
                h[v] = h[u] + 1;
                q[e++] = v;
                if(e == size)
                    e = 0;
            }
        }
    }
}
int push(int u, int v, int id, int fu) {
    int w = std::min(fu, E[id].w);
    f[u] -= w, f[v] += w, E[id].w -= w,
        E[id ^ 1].w += w;
    return w;
}
int HLPP(int n, int s, int t) {
    f[s] = inf;
    pre(n, t);
    if(h[s] == 0x3f3f3f3f)
        return 0;
    h[s] = n;
    for(int i = 1; i <= n; ++i)
        if(i != s && h[i] != 0x3f3f3f3f) {
            dl[h[i]].insert(i);
            highest = std::max(highest, h[i]);
        }
    flag[s] = flag[t] = true;
    for(int i = last[s]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(push(s, v, i, inf) && !flag[v]) {
            heap[h[v]].push_back(v);
            flag[v] = true;
            highestInHeap =
                std::max(highestInHeap, h[v]);
        }
    }
    while(highestInHeap >= 0) {
        if(heap[highestInHeap].size()) {
            int u = heap[highestInHeap].back();
            heap[highestInHeap].pop_back();
            flag[u] = false;
            int minh = inf;
            for(int i = last[u]; i && f[u];
                i = E[i].nxt) {
                int v = E[i].to;
                if(h[u] == h[v] + 1) {
                    if(push(u, v, i, f[u]) &&
                       !flag[v]) {
                        heap[h[v]].push_back(v);
                        flag[v] = true;
                        highestInHeap = std::max(
                            highestInHeap, h[v]);
                    }
                } else if(E[i].w)
                    minh = std::min(minh, h[v] + 1);
            }
            if(f[u]) {
                if(dl[highestInHeap].size() == 1) {
                    for(int i = highestInHeap;
                        i <= highest; ++i) {
                        for(Iter it = dl[i].begin();
                            it != dl[i].end(); ++it)
                            h[*it] = n + 1;
                        dl[highestInHeap].clear();
                    }
                    highest = highestInHeap - 1;
                } else
                    dl[highestInHeap].erase(u);

                h[u] = minh;
                heap[minh].push_back(u);
                dl[minh].insert(u);
                flag[u] = true;
                highestInHeap =
                    std::max(highestInHeap, minh);
                highest = std::max(highest, minh);
            }
        } else
            --highestInHeap;
    }
    return f[t];
}
int main() {
    int n = read();
    int m = read();
    int s = read();
    int t = read();
    while(m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, 0);
    }
    printf("%d\n", HLPP(n, s, t));
    return 0;
}
