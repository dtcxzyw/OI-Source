#include <cstdio>
int main() {
    int n;
    scanf("%d", &n);
    int res = 0;
    for(int i = 1; i < n; ++i)
        if(i % 3 == 0 || i % 5 == 0)
            res += i;
    printf("%d\n", res);
    return 0;
}
