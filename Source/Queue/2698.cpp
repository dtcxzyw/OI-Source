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
const int size = 100005, end = size * 10;
struct Point {
    int x, minh, maxh;
} P[size];
struct Info {
    int t, v;
    Info() {}
    Info(int t, int v) : t(t), v(v) {}
};
typedef bool (*CmpFunc)(Info a, Info b);
bool cmpLe(Info a, Info b) {
    return a.v < b.v;
}
bool cmpGe(Info a, Info b) {
    return a.v > b.v;
}
template <CmpFunc cmp, int inf>
class Queue {
private:
    Info q[size];
    int b, e;

public:
    Queue() : b(0), e(0) {}
    void push(Info x) {
        while(b < e && cmp(x, q[e - 1]))
            --e;
        q[e++] = x;
    }
    void pop(int t) {
        while(b < e && q[b].t <= t)
            ++b;
    }
    int front() const {
        return b < e ? q[b].v : inf;
    }
};
Queue<cmpLe, 1 << 30> minQ;
Queue<cmpGe, -(1 << 30)> maxQ;
int minh[end], maxh[end];
int main() {
    int n = read();
    int d = read();
    memset(minh, 0x3f, sizeof(minh));
    int minx = 1 << 30, maxx = 0, miny = 1 << 30,
        maxy = 0;
    for(int i = 1; i <= n; ++i) {
        int x = read();
        int y = read();
        minx = std::min(minx, x);
        maxx = std::max(maxx, x);
        miny = std::min(miny, y);
        maxy = std::max(maxy, y);
        minh[x] = std::min(minh[x], y);
        maxh[x] = std::max(maxh[x], y);
    }
    if(maxy - miny >= d) {
        int cnt = 0;
        for(int i = minx; i <= maxx; ++i)
            if(minh[i] != 0x3f3f3f3f) {
                P[cnt].x = i;
                P[cnt].minh = minh[i];
                P[cnt].maxh = maxh[i];
                ++cnt;
            }
        int ans = 1 << 30, r = 0;
        for(int l = 0; l < cnt; ++l) {
            while(r + 1 < cnt &&
                  maxQ.front() - minQ.front() < d) {
                ++r;
                minQ.push(Info(r, P[r].minh));
                maxQ.push(Info(r, P[r].maxh));
            }
            if(maxQ.front() - minQ.front() >= d)
                ans = std::min(ans, P[r].x - P[l].x);
            else
                break;
            minQ.pop(l);
            maxQ.pop(l);
        }
        if(ans == 1 << 30)
            puts("-1");
        else
            printf("%d\n", ans);
    } else
        puts("-1");
    return 0;
}
