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
const int size = 75, inf = 1 << 30;
int A[size][size], B[size][size], C[size][size];
struct Vec {
    int x, y;
    Vec(int x, int y) : x(x), y(y) {}
    Vec operator-(const Vec& rhs) const {
        return Vec(x - rhs.x, y - rhs.y);
    }
};
int cross(const Vec& a, const Vec& b) {
    return a.x * b.y - b.x * a.y;
}
bool FL[size], FR[size];
int HL[size], HR[size], pair[size], slack[size];
int ans, n;
template <typename T>
void reset(T* arr, int bit = 0) {
    memset(arr + 1, bit, sizeof(T) * n);
}
bool DFS(int u) {
    FL[u] = true;
    for(int v = 1; v <= n; ++v) {
        if(!FR[v]) {
            int del = HL[u] + HR[v] - C[u][v];
            if(del)
                slack[v] = std::min(slack[v], del);
            else {
                FR[v] = true;
                if(!pair[v] || DFS(pair[v])) {
                    pair[v] = u;
                    return true;
                }
            }
        }
    }
    return false;
}
Vec calcKM(int ka, int kb) {
    for(int i = 1; i <= n; ++i) {
        int maxh = -inf;
        for(int j = 1; j <= n; ++j) {
            C[i][j] = ka * A[i][j] + kb * B[i][j];
            maxh = std::max(maxh, C[i][j]);
        }
        HL[i] = maxh;
    }
    reset(HR);
    reset(pair);
    for(int i = 1; i <= n; ++i) {
        reset(slack, 0x3f);
        while(true) {
            reset(FL);
            reset(FR);
            if(DFS(i))
                break;
            int del = inf;
            for(int j = 1; j <= n; ++j)
                if(!FR[j])
                    del = std::min(del, slack[j]);
            for(int j = 1; j <= n; ++j) {
                if(FL[j])
                    HL[j] -= del;
                if(FR[j])
                    HR[j] += del;
                else
                    slack[j] -= del;
            }
        }
    }
    int sx = 0, sy = 0;
    for(int i = 1; i <= n; ++i) {
        sx += A[pair[i]][i];
        sy += B[pair[i]][i];
    }
    ans = std::min(ans, sx * sy);
    return Vec(sx, sy);
}
void quickHull(const Vec& a, const Vec& b) {
    Vec c = calcKM(b.y - a.y, a.x - b.x);
    if(cross(c - a, b - a) > 0) {
        quickHull(a, c);
        quickHull(c, b);
    }
}
int foo() {
    n = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            A[i][j] = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            B[i][j] = read();
    ans = inf;
    quickHull(calcKM(-1, 0), calcKM(0, -1));
    return ans;
}
int main() {
    int t = read();
    while(t--)
        printf("%d\n", foo());
    return 0;
}
