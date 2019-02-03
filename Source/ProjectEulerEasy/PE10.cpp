#include <cstdio>
const int n = 2000000;
bool flag[n + 5];
int main() {
    int pcnt = 0;
    long long sum = 0;
    for(int i = 2; i <= n; ++i)
        if(!flag[i]) {
            sum += i;
            for(int j = i * 2; j <= n; j += i)
                flag[j] = true;
        }
    printf("%lld\n", sum);
    return 0;
}
