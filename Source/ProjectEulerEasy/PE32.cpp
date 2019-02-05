#include <cstdio>
#include <set>
int main() {
    int n;
    scanf("%d", &n);
    std::set<long long> res;
    for(int i = 1; i <= n; ++i) {
        for(int j = i; j <= n; ++j) {
            bool use[10] = {};
            use[0] = true;
            long long ci = i, cj = j, ck = 1LL * i * j;
            while(ci) {
                int v = ci % 10;
                if(use[v])
                    goto err;
                use[v] = true;
                ci /= 10;
            }
            while(cj) {
                int v = cj % 10;
                if(use[v])
                    goto err;
                use[v] = true;
                cj /= 10;
            }
            while(ck) {
                int v = ck % 10;
                if(use[v])
                    goto err;
                use[v] = true;
                ck /= 10;
            }
            for(int i = 1; i < 10; ++i)
                if(!use[i])
                    goto err;
            printf("%d*%d=%lld\n", i, j, 1LL * i * j);
            res.insert(i * j);
        err : {}
        }
        printf("%d\n", i);
    }
    long long sum = 0;
    for(std::set<long long>::iterator it = res.begin();
        it != res.end(); ++it)
        sum += *it;
    printf("%lld\n", sum);
    return 0;
}
