#include <algorithm>
#include <cstdio>
#include <cstring>
bool getState() {
    int c;
    do
        c = getchar();
    while (c != '0' && c != '1');
    return c == '1';
}
const int maxn = 105;
class State {
   private:
    int val;

   public:
    State(int val) : val(val) {}
    State(int x, int y, int k) : val(((x << 7) | y) << 4 | k) {}
    bool haveKey(int id) const {
        return val & (1 << id);
    }
    int x() const {
        return val >> 11;
    }
    int y() const {
        return (val >> 4) & 127;
    }
    int k() const {
        return val & 15;
    }
    int id() const {
        return val;
    }
};
const int size = (((100 << 7) | 100) << 4) + 11;
int dis[size], q[size];
bool flag[size] = {};
bool map[maxn][maxn];
const int off[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
void tryUpdate(int v, int &e, int dv) {
    if (dis[v] > dv) {
        dis[v] = dv;
        if (!flag[v]) {
            flag[v] = true;
            q[e++] = v;
            if (e == size) e = 0;
        }
    }
}
int SPFA(State s, int n, int k, int wa, int wb, int wc) {
    memset(dis, 0x3f, sizeof(dis));
    int b = 0, e = 1;
    dis[s.id()] = 0, q[0] = s.id(), flag[s.id()] = true;
    int res = 1 << 30;
    while (b != e) {
        int u = q[b++];
        if (b == size) b = 0;
        State su(u);
        int x = su.x(), y = su.y(), ck = su.k();
        flag[u] = false;
        for (int i = 0; i < 4; ++i) {
            int cx = x + off[i][0], cy = y + off[i][1];
            if (1 <= cx && cx <= n && 1 <= cy && cy <= n && ck) {
                int cd = dis[u] + (i < 2 ? wb : 0);
                if (map[cx][cy])
                    tryUpdate(State(cx, cy, k).id(), e, cd + wa);
                else {
                    tryUpdate(State(cx, cy, ck - 1).id(), e, cd);
                    tryUpdate(State(cx, cy, k).id(), e, cd + wc);
                }
            }
        }
        if (x == n && y == n) res = std::min(res, dis[u]);
    }
    return res;
}
int main() {
    int n, k, a, b, c;
    scanf("%d%d%d%d%d", &n, &k, &a, &b, &c);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            map[i][j] = getState();
    printf("%d\n", SPFA(State(1, 1, k), n, k, a, b, a + c));
    return 0;
}
