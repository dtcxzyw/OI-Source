#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unordered_map>
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
const int maxv = 1 << 19, maxe = 1 << 21;
struct Edge {
    int to, nxt;
} E[maxe];
int last[maxv], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v << 1 | w, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int dis[maxv], q[maxe];
bool flag[maxv];
int SSSP(int n, int s, int t) {
    memset(dis, 0x3f, sizeof(int) * n);
    dis[s] = 0;
    int b = 0, e = 1;
    q[0] = s;
    while(b != e) {
        int u = q[b++];
        if(b == maxe)
            b = 0;
        if(flag[u])
            continue;
        flag[u] = true;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to >> 1;
            int dv = dis[u] + (E[i].to & 1);
            if(dis[v] > dv) {
                dis[v] = dv;
                if(E[i].to & 1) {
                    q[e++] = v;
                    if(e == maxe)
                        e = 0;
                } else {
                    if(--b == -1)
                        b = maxe - 1;
                    q[b] = v;
                }
            }
        }
    }
    return dis[t] == 0x3f3f3f3f ? -1 : dis[t];
}
std::unordered_map<int, int> pid[30005];
int pcnt, n;
int load(int b, int p) {
    int& id = pid[b][p];
    if(!id) {
        for(int i = b % p; i < n; i += p) {
            pid[i][p] = pcnt++;
            addEdge(pid[i][p], i, 0);
            if(i >= p) {
                addEdge(pid[i][p], pid[i - p][p], 1);
                addEdge(pid[i - p][p], pid[i][p], 1);
            }
        }
    }
    return id;
}
int main() {
    n = read();
    int m = read(), s, t;
    pcnt = n;
    for(int i = 0; i < m; ++i) {
        int b = read();
        if(i == 0)
            s = b;
        if(i == 1)
            t = b;
        int p = read();
        int id = load(b, p);
        addEdge(b, id, 0);
    }
    printf("%d\n", SSSP(pcnt, s, t));
    std::cerr << pcnt << " " << cnt << std::endl;
    std::ifstream input("/proc/self/status");
    std::cerr << input.rdbuf() << std::endl;
    return 0;
}
