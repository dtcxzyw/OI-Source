#include <cstdio>
typedef unsigned long long Int64;
const Int64 fac = 131, size = 200005;
Int64 hash[size], base[size];
char buf[size];
Int64 calcImpl(int l, int r) {
    return hash[r] - hash[l - 1] * base[r - l + 1];
}
Int64 calc(int l, int r, int c) {
    if(l >= c)
        ++l;
    if(r >= c)
        ++r;
    if(c < l || c > r)
        return calcImpl(l, r);
    else {
        return calcImpl(l, c - 1) * base[r - c] +
            calcImpl(c + 1, r);
    }
}
bool check(int m, int n, int c) {
    return calc(1, n - m, c) == calc(1 + m, n, c);
}
int foo() {
    int n;
    scanf("%d%s", &n, buf + 1);
    for(int i = 1; i <= n; ++i)
        hash[i] = hash[i - 1] * fac + buf[i];
    base[0] = 1;
    for(int i = 1; i <= n; ++i)
        base[i] = base[i - 1] * fac;
    int ans = n - 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j < ans; ++j)
            if(check(j, n - 1, i)) {
                ans = j;
                break;
            }
    }
    return ans;
}
int main() {
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; ++i)
        printf("%d\n", foo());
    return 0;
}
