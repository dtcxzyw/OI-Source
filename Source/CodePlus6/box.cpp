#include <algorithm>
#include <cstdio>
#include <vector>
typedef double FT;
double foo() {
    int n, m, t, k, p;
    scanf("%d%d%d%d%d", &n, &m, &t, &k, &p);
    std::vector<int> P;
    for(int i = 1; i <= n; ++i)
        P.push_back(0);
    for(int i = 1; i <= m; ++i) {
        std::sort(P.begin(), P.end());
        int sumA = 0;
        if(t <= n) {
            for(int j = 0; j < t; ++j)
                sumA += std::min(100, p + j) - P[j];
        }
        int sumB = 0;
        if(k <= n) {
            for(int j = 0; j < k; ++j)
                sumB += p - P[j];
        }
        if(sumA > sumB) {
            for(int j = 0; j < t; ++j)
                P[j] = std::min(100, p + j);
        } else {
            for(int j = 0; j < k; ++j)
                P[j] = p;
        }
    }
    int sum = 0;
    for(int i = 0; i < n; ++i)
        sum += P[i];
    return sum / 100.0;
}
int main() {
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; ++i)
        printf("%.5lf\n", foo());
    return 0;
}
