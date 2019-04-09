#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
int m;
std::vector<int> A[10];
int calc() {
    int res = 0;
    for(int i = 0; i < m; ++i) {
        int sum = 0;
        for(int j = 0; j < A[i].size(); ++j)
            sum += A[i][j];
        res += sum * sum;
    }
    return res;
}
typedef double FT;
int getRandom() {
    static int seed = 3435;
    return seed = seed * 48271LL % 2147483647;
}
int main() {
    int n;
    scanf("%d%d", &n, &m);
    int sum = 0;
    for(int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        sum += x;
        A[getRandom() % m].push_back(x);
    }
    int minv = calc(), cur = minv;
    for(int i = 0; i < 2000; ++i) {
        FT T = 1e5;
        while(T >= 1e-8) {
            int x = getRandom() % m;
            while(A[x].empty())
                x = getRandom() % m;
            int pos = getRandom() % A[x].size();
            int y = getRandom() % m;
            while(x == y)
                y = getRandom() % m;
            A[y].push_back(A[x][pos]);
            A[x].erase(A[x].begin() + pos);
            int now = calc();
            if(now < cur) {
                cur = now;
                if(now < minv)
                    minv = now;
            } else if(exp((cur - now) / T) *
                          2147483647.0 >=
                      getRandom()) {
                cur = now;
            } else {
                A[x].push_back(A[y].back());
                A[y].pop_back();
            }
            T *= 0.9;
        }
    }
    FT tot = m, avg = sum / tot;
    printf("%.2lf\n",
           sqrt(std::max(
               0.0, (minv - tot * avg * avg) / tot)));
    return 0;
}
