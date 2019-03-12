#include <algorithm>
#include <cmath>
#include <cstdio>
const int sqsiz = 50005;
int p[sqsiz], mu[sqsiz];
bool flag[sqsiz];
void pre(int n) {
    mu[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j])
                mu[val] = -mu[i];
            else
                break;
        }
    }
}
int calc(int n) {
    int res = 0, end = sqrt(n);
    for(int i = 1; i <= end; ++i) {
        int div = n / i / i;
        res += div * mu[i];
    }
    return res;
}
struct Query {
    int id, p;
} Q[55];
int ans[55];
void solve(int l, int r, int b, int e) {
    if(b > e)
        return;
    if(l == r) {
        for(int i = b; i <= e; ++i)
            ans[Q[i].id] = l;
    } else {
        int m = l + ((r - l) >> 1), num = calc(m);
        int end = b;
        for(int i = b; i <= e; ++i)
            if(Q[i].p <= num)
                std::swap(Q[i], Q[end++]);
        solve(l, m, b, end - 1);
        solve(m + 1, r, end, e);
    }
}
int main() {
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; ++i) {
        Q[i].id = i;
        scanf("%d", &Q[i].p);
    }
    const int end = 1644934081;
    pre(sqrt(end));
    solve(1, end, 1, t);
    for(int i = 1; i <= t; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
