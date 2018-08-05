#include <algorithm>
#include <cstdio>
#include <cstring>
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
class State {
   private:
    int val;

   public:
    State(int val) : val(val) {}
    State(int x, int y, int s) : val(((x << 4) | y) << 10 | s) {}
    bool haveKey(int id) const {
        return val & (1 << id);
    }
    int x() const {
        return val >> 14;
    }
    int y() const {
        return (val >> 10) & 15;
    }
    int s() const {
        return val & ((1 << 10) - 1);
    }
    int id() const {
        return val;
    }
};
const int size = (((10 << 4) | 10) << 10) + (1 << 10);
int dis[size], q[size];
bool flag[size] = {};
int map[15][15][4], key[15][15];
const int off[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
int SPFA(State s, int n, int m) {
    memset(dis, 0x3f, sizeof(dis));
    int b = 0, e = 1;
    dis[s.id()] = 0, q[0] = s.id(), flag[s.id()] = true;
    int res = 1 << 30;
    while (b != e) {
        int u = q[b++];
        if (b == size) b = 0;
        State su(u);
        int x = su.x(), y = su.y(), cs = su.s();
        flag[u] = false;
        for (int i = 0; i < 4; ++i) {
            int cx = x + off[i][0], cy = y + off[i][1];
            if (1 <= cx && cx <= n && 1 <= cy && cy <= m) {
                if (map[x][y][i] == 0 || su.haveKey(map[x][y][i] - 1)) {
                    int v = State(cx, cy, cs | key[cx][cy]).id();
                    if (dis[v] > dis[u] + 1) {
                        dis[v] = dis[u] + 1;
                        if (!flag[v]) {
                            flag[v] = true;
                            q[e++] = v;
                            if (e == size) e = 0;
                        }
                    }
                }
            }
        }
        if (x == n && y == m) res = std::min(res, dis[u]);
    }
    return res == (1 << 30) ? -1 : res;
}
int main() {
    int n = read();
    int m = read();
    int p = read();
    int k = read();
    while (k--) {
        int x1 = read();
        int y1 = read();
        int x2 = read();
        int y2 = read();
        int g = read();
        if (g == 0) g = 20;
        if (x1 == x2) {
            if (y1 > y2) std::swap(y1, y2);
            map[x1][y1][2] = map[x2][y2][3] = g;
        } else {
            if (x1 > x2) std::swap(x1, x2);
            map[x1][y1][1] = map[x2][y2][0] = g;
        }
    }
    int s = read();
    while (s--) {
        int x = read();
        int y = read();
        int q = read() - 1;
        key[x][y] |= 1 << q;
    }
    printf("%d\n", SPFA(State(1, 1, key[1][1]), n, m));
    return 0;
}
