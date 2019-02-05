#include <cstdio>
int main() {
    for(int i = 1; i < 100000; ++i) {
        bool use[10] = {};
        use[0] = true;
        int uc = 0;
        for(int j = 1; j <= 9; ++j) {
            long long val = 1LL * i * j;
            while(val) {
                int v = val % 10;
                if(use[v])
                    goto err;
                use[v] = true, ++uc;
                val /= 10;
            }
            if(uc == 9 && j > 1)
                break;
        }
        printf("%d\n", i);
    err : {}
    }
    return 0;
}
