#include <algorithm>
#include <cstdio>
#include <map>
const int size = 100005, qsiz = 20005;
typedef unsigned int U32;
U32 p[size], sd[size], pw[size], psum[size], ord[size],
    mu[size];
bool flag[size];
bool cmp(U32 a, U32 b) {
    return sd[a] < sd[b];
}
void pre(U32 n) {
    sd[1] = mu[1] = 1;
    U32 pcnt = 0;
    for(U32 i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            sd[i] = psum[i] = i + 1, pw[i] = i;
            mu[i] = -1;
        }
        for(U32 j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            U32 val = i * p[j];
            flag[val] = true;
            if(i % p[j]) {
                sd[val] = sd[i] * (1 + p[j]);
                psum[val] = 1 + p[j], pw[val] = p[j];
                mu[val] = -mu[i];
            } else {
                pw[val] = pw[i] * p[j];
                psum[val] = psum[i] + pw[val];
                sd[val] = sd[i] / psum[i] * psum[val];
                break;
            }
        }
    }
    for(U32 i = 1; i <= n; ++i)
        ord[i] = i;
    std::sort(ord + 1, ord + n + 1, cmp);
    for(U32 i = 1; i <= n; ++i)
        mu[i] += mu[i - 1];
}
U32 S[size];
void add(U32 x, U32 n, U32 val) {
    while(x <= n) {
        S[x] += val;
        x += x & -x;
    }
}
U32 query(U32 x) {
    U32 res = 0;
    while(x) {
        res += S[x];
        x -= x & -x;
    }
    return res;
}
typedef std::map<std::pair<U32, U32>, U32> Cache;
Cache cache;
U32 queryS(U32 n, U32 m) {
    std::pair<U32, U32> key(n, m);
    Cache::iterator it = cache.find(key);
    if(it != cache.end())
        return it->second;
    U32 end = std::min(n, m), res = 0;
    for(U32 i = 1; i <= end;) {
        U32 dn = n / i, dm = m / i,
            j = std::min(n / dn, m / dm);
        res += (mu[j] - mu[i - 1]) * dn * dm;
        i = j + 1;
    }
    return cache[key] = res;
}
struct Query {
    U32 id, n, m, a;
    bool operator<(const Query& rhs) const {
        return a < rhs.a;
    }
} Q[qsiz];
U32 ans[qsiz];
int main() {
    U32 q;
    scanf("%d", &q);
    U32 preSiz = 0;
    for(U32 i = 0; i < q; ++i) {
        Q[i].id = i;
        scanf("%u%u%u", &Q[i].n, &Q[i].m, &Q[i].a);
        preSiz =
            std::max(preSiz, std::min(Q[i].n, Q[i].m));
    }
    std::sort(Q, Q + q);
    pre(preSiz);
    for(U32 t = 0, d = 1; t < q; ++t) {
        U32 n = Q[t].n, m = Q[t].m,
            end = std::min(n, m), a = Q[t].a;
        while(d <= preSiz && sd[ord[d]] <= a) {
            add(ord[d], preSiz, sd[ord[d]]);
            ++d;
        }
        U32 res = 0, last = 0;
        for(U32 i = 1; i <= end;) {
            U32 dn = n / i, dm = m / i,
                j = std::min(n / dn, m / dm);
            U32 cur = query(j);
            res += (cur - last) * queryS(dn, dm);
            last = cur;
            i = j + 1;
        }
        ans[Q[t].id] = res;
    }
    for(U32 i = 0; i < q; ++i)
        printf("%u\n", ans[i] & 2147483647);
    return 0;
}
