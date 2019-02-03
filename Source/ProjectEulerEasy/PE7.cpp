#include <cstdio>
const int n = 1000000;
bool flag[n + 5];
int main() {
    int pcnt = 0;
    for(int i = 2; i <= n; ++i)
        if(!flag[i]) {
            if(++pcnt == 10001) {
                printf("%d\n", i);
                break;
            }
            for(int j = i * 2; j <= n; j += i)
                flag[j] = true;
        }
    return 0;
}
