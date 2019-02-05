#include <algorithm>
#include <cstdio>
#include <set>
int f(int x) {
    return x * (3 * x - 1) / 2;
}
int main() {
    int n;
    scanf("%d", &n);
    std::set<int> A;
    for(int i = 1; i <= n; ++i)
        A.insert(f(i));
    int res = 1 << 30;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j) {
            if(A.count(f(i) + f(j)) &&
               A.count(f(i) - f(j)))
                res = std::min(res, f(i) - f(j));
        }
    printf("%d\n", res);
    return 0;
}
