#include <cstdio>
int getRandom() {
    static int seed = 2351432;
    return seed = seed * 48271LL % 2147483647;
}
int main() {
    const int size = 1 << 27;
    freopen("data/IO1.in", "w", stdout);
    printf("%d\n", size);
    for(int i = 1; i <= size; ++i)
        printf("%d\n", getRandom());
    return 0;
}
