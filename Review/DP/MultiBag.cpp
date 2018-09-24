#include <algorithm>
#include <cstdio>
const int size = 40005;
int dp[size];
typedef std::pair<int, int> Info;
Info q[size];
void update(int V, int w, int v, int c) {
    for(int b = 0; b < v; ++b) {
        Info *beg = q, *end = q;
        for(int i = b, a = 0; i <= V; i += v, ++a) {
            while(beg < end && a - beg->first > c)
                ++beg;
            int delta = a * w;
            Info val =
                std::make_pair(a, dp[i] - delta);
            while(beg < end &&
                  (end - 1)->second <= val.second)
                --end;
            *(end++) = val;
            dp[i] = beg->second + delta;
        }
    }
}
int main() {
    int n, V;
    scanf("%d%d", &n, &V);
    for(int i = 0; i < n; ++i) {
        int w, v, c;
        scanf("%d%d%d", &w, &v, &c);
        if(c != 1) {
            if((c + 1LL) * v <= V) {
                update(V, w, v, c);
            } else {
                for(int i = v; i <= V; ++i)
                    dp[i] =
                        std::max(dp[i], dp[i - v] + w);
            }
        } else {
            for(int i = V; i >= v; --i)
                dp[i] = std::max(dp[i], dp[i - v] + w);
        }
    }
    printf("%d\n", dp[V]);
    return 0;
}
