#include <cstdio>
#include <cstring>
#include <utility>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
int getMask() {
    int c;
    do
        c = getchar();
    while (c != '+' && c != '-' && c != '0');
    return c;
}
std::pair<int, int> scan(int n) {
    int a = 0, b = 0;
    for (int i = 0; i < n; ++i) {
        a <<= 1, b <<= 1;
        int mask = getMask();
        if (mask == '+')
            a |= 1;
        else if (mask == '-')
            b |= 1;
    }
    return std::make_pair(a, b);
}
const int size = (1 << 20) + 5;
std::pair<int, int> B[105], F[105];
int dis[size], q[size], w[105];
bool flag[size] = {};
int SPFA(int n, int m) {
    memset(dis, 0x3f, sizeof(int) * (1 << n));
    int s = (1 << n) - 1;
    dis[s] = 0, q[0] = s, flag[s] = true;
    int b = 0, e = 1;
    while (b != e) {
        int u = q[b++];
        flag[u] = false;
        if (b == size) b = 0;
        for (int i = 0; i < m; ++i)
            if ((u & B[i].first) == B[i].first && (u & B[i].second) == 0) {
                int v = (u & (~F[i].second)) | F[i].first;
                int cd = dis[u] + w[i];
                if (dis[v] > cd) {
                    dis[v] = cd;
                    if (!flag[v]) {
                        flag[v] = true;
                        q[e++] = v;
                        if (e == size) e = 0;
                    }
                }
            }
    }
    return dis[0] == 0x3f3f3f3f ? 0 : dis[0];
}
int main() {
    int n = read();
    int m = read();
    for (int i = 0; i < m; ++i) {
        w[i] = read();
        B[i] = scan(n);
        F[i] = scan(n);
    }
    printf("%d\n", SPFA(n, m));
    return 0;
}
