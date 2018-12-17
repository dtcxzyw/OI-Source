#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>
#include <random>
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
const int size = 505;
struct Edge {
    int u, v;
} E[130005];
int match[size], bak[size], bv = 0;
void save(int n, int cur) {
    if(cur > bv) {
        bv = cur;
        memcpy(bak + 1, match + 1, sizeof(int) * n);
    }
}
using REng = std::mt19937_64;
using Clock = std::chrono::high_resolution_clock;
using IntType = REng::result_type;
int main() {
    int n = read();
    int m = read();
    for(int i = 0; i < m; ++i) {
        E[i].u = read();
        E[i].v = read();
    }
    REng rnd(Clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> uid(0, m - 1);
    int mink = ceil(log(1e-5) / log(169.0 / 189.0));
    int k1 = 10 * ceil(log2(n)),
        ka = std::max(k1, mink), mp = n >> 1;
    IntType p = std::numeric_limits<IntType>::max() /
        ((IntType(1) << m) + 1);
    if((IntType(1) << m) == 0)
        p = 0;
    while(ka--) {
        memset(match + 1, 0, sizeof(int) * n);
        int k = k1 * m, cur = 0;
        int maxp = uid(rnd);
        while(maxp--) {
            int eid = uid(rnd);
            int u = E[eid].u, v = E[eid].v;
            if(match[u] == 0 && match[v] == 0) {
                match[u] = v, match[v] = u;
                ++cur;
            }
        }
        while(k--) {
            int eid = uid(rnd);
            int u = E[eid].u, v = E[eid].v;
            if(rnd() <= p) {
                if(match[u] == v) {
                    save(n, cur);
                    match[u] = match[v] = 0;
                    --cur;
                }
            } else {
                if(match[u] == 0 && match[v] == 0) {
                    match[u] = v, match[v] = u;
                    ++cur;
                    if(cur == mp)
                        break;
                }
            }
        }
        save(n, cur);
        if(bv == mp)
            break;
    }
    printf("%d\n", bv);
    for(int i = 1; i <= n; ++i)
        printf("%d ", bak[i]);
    return 0;
}
