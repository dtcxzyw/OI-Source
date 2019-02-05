#include <algorithm>
const int size = 1000005;
bool flag[size];
int main() {
    flag[1] = true;
    int n;
    scanf("%d", &n);
    for(int i = 2; i <= n; ++i)
        if(!flag[i])
            for(int j = i * 2; j <= n; j += i)
                flag[j] = true;
    int cnt = 0, res = 0;
    for(int i = 10; i <= n; ++i)
        if(!flag[i]) {
            int ci = i;
            for(int j = 1000000; j > 1; j /= 10) {
                ci %= j;
                if(flag[ci])
                    goto err;
            }
            ci = i;
            while(ci) {
                if(flag[ci])
                    goto err;
                ci /= 10;
            }
            printf("%d\n", i);
            res += i, ++cnt;
        err : {}
        }
    printf("%d %d\n", cnt, res);
    return 0;
}
