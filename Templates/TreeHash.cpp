#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
const int size = 55;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int kp[size], kcnt, cmsiz, n;
int pre(int u, int p) {
    int siz = 1, mx = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            int sv = pre(v, u);
            mx = std::max(mx, sv);
            siz += sv;
        }
    }
    mx = std::max(n - siz, mx);
    if(mx < cmsiz) {
        kcnt = 0;
        cmsiz = mx;
    }
    if(mx == cmsiz)
        kp[kcnt++] = u;
    return siz;
}
int DFS(int u, int p) {
    int a = 1, b = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            int hv = DFS(v, u);
            a += hv, b *= hv;
        }
    }
    return a * b + a + b + (a ^ b);
}
int getHash() {
    cnt = 0;
    memset(last, 0, sizeof(last));
    scanf("%d", &n);
    int rt;
    for(int i = 1; i <= n; ++i) {
        int p;
        scanf("%d", &p);
        if(p) {
            addEdge(p, i);
            addEdge(i, p);
        } else
            rt = i;
    }
    kcnt = 0, cmsiz = 1 << 30;
    pre(rt, 0);
    return kcnt == 1 ?
        DFS(kp[0], 0) :
        std::min(DFS(kp[0], 0), DFS(kp[1], 0));
}
std::map<int, int> hashTable;
int main() {
    int m;
    scanf("%d", &m);
    for(int i = 1; i <= m; ++i) {
        int& hid = hashTable[getHash()];
        if(!hid)
            hid = i;
        printf("%d\n", hid);
    }
    return 0;
}
