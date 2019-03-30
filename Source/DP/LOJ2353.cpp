#include <algorithm>
#include <cstdio>
#include <cstdlib>
typedef double FT;
namespace IO {
    char in[1 << 23], *S = in;
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    int readInt() {
        return strtol(S, &S, 10);
    }
    FT readFT() {
        return strtod(S, &S);
    }
}
const int size = 100005;
FT A[size], B[size], R[size], ans;
struct Pos {
    int id;
    FT k;
    bool operator<(const Pos& rhs) const {
        return k > rhs.k;
    }
} P[size];
struct Vec {
    FT x, y;
    bool operator<(const Vec& rhs) const {
        return x < rhs.x;
    }
} C[size], CC[size];
FT dp[size];
FT slope(const Vec& a, const Vec& b) {
    return (a.y - b.y) / (a.x - b.x);
}
void solve(int l, int r) {
    if(l == r) {
        ans = std::max(ans, dp[l]);
        FT div = A[l] * R[l] + B[l];
        C[l].y = ans / div;
        C[l].x = C[l].y * R[l];
    } else {
        int m = (l + r) >> 1;
        std::stable_partition(
            P + l, P + r + 1,
            [m](const Pos& p) { return p.id <= m; });
        solve(l, m);
        int top = 0;
        for(int i = l; i <= m; ++i) {
            while(top >= 2 &&
                  (CC[top - 1].y - CC[top].y) *
                          (CC[top].x - C[i].x) <=
                      (CC[top].y - C[i].y) *
                          (CC[top - 1].x - CC[top].x))
                --top;
            CC[++top] = C[i];
        }
        for(int i = m + 1, j = 1; i <= r; ++i) {
            while(j < top &&
                  (CC[j].y - CC[j + 1].y) <=
                      P[i].k * (CC[j].x - CC[j + 1].x))
                ++j;
            int id = P[i].id;
            FT a = A[id], b = B[id];
            dp[id] = std::max(dp[id], a * CC[j].x +
                                  b * CC[j].y);
        }
        solve(m + 1, r);
        std::inplace_merge(C + l, C + m + 1,
                           C + r + 1);
    }
}
int main() {
    IO::init();
    int n = IO::readInt();
    ans = IO::readInt();
    for(int i = 1; i <= n; ++i) {
        A[i] = IO::readFT();
        B[i] = IO::readFT();
        R[i] = IO::readFT();
        P[i].id = i, P[i].k = -A[i] / B[i];
    }
    std::sort(P + 1, P + n + 1);
    solve(1, n);
    printf("%.3lf\n", ans);
    return 0;
}
