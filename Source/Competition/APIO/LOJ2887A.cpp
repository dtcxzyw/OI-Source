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
const int size = 30005;
struct Edge {
    int to, nxt;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
const int modu = 14000029, modv = 13999981;
int val[modu], dis[modu];
bool flag[modu];
void init() {
    memset(val, -1, sizeof(val));
}
int load(int k) {
    int ha = k % modu, hb = 1 + k % modv, cur = ha;
    while(true) {
        if(val[cur] == -1) {
            val[cur] = k;
            dis[cur] = 0x3f3f3f3f;
        }
        if(val[cur] == k)
            return cur;
        cur += hb;
        if(cur >= modu)
            cur -= modu;
    }
}
const int maxq = size;
int q[maxq], b, e;
void trans(int X, int Y, int du, int w) {
    int v = X << 15 | Y;
    int idv = load(v);
    if(dis[idv] > du + w) {
        dis[idv] = du + w;
        if(w) {
            q[e++] = v;
            if(e == maxq)
                e = 0;
        } else {
            if(--b == -1)
                b = maxq - 1;
            q[b] = v;
        }
    }
}
int SSSP(int n, int s, int t) {
    init();
    b = 0, e = 1;
    q[0] = s << 15;
    dis[load(s << 15)] = 0;
    while(b != e) {
        int u = q[b++];
        if(b == maxq)
            b = 0;
        int idu = load(u);
        if(flag[idu])
            continue;
        flag[idu] = true;
        int X = u >> 15, Y = u & 32767, du = dis[idu];
        if(X == t)
            return du;
        if(Y) {
            if(X >= Y)
                trans(X - Y, Y, du, 1);
            if(X + Y < n)
                trans(X + Y, Y, du, 1);
            trans(X, 0, du, 0);
        } else {
            for(int i = last[X]; i; i = E[i].nxt) {
                int Z = E[i].to;
                trans(X, Z, du, 0);
            }
        }
    }
    return -1;
}
int main() {
    int n = read();
    int m = read(), s, t;
    for(int i = 0; i < m; ++i) {
        int b = read();
        int p = read();
        if(i == 0)
            s = b;
        if(i == 1)
            t = b;
        addEdge(b, p);
    }
    printf("%d\n", SSSP(n, s, t));
    return 0;
}
