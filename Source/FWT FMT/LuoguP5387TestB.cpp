#include <cstdio>
int sg(int x) {
    return x - (1 << (31 - __builtin_clz(x)));
}
int cnt = 0;
void DFS(int v, int m, int xorv) {
    if (v) {
        for (int i = 1; i <= m; ++i)
            DFS(v - 1, m, xorv ^ sg(i));
    } else
        cnt += (xorv != 0);
}
int main() {
    int v, m;
    scanf("%d%d", &v, &m);
    DFS(v, m, 0);
    printf("%d\n", cnt);
    return 0;
}
