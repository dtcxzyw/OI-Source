#include <cstdio>
int sg[2005];
void calcSG(int x) {
    bool use[2005] = {};
    for (int y = 1; y < x; ++y)
        if ((x ^ y) < x && (x ^ y) >= 1)
            use[sg[x ^ y]] = true;
    for (int z = 0;; ++z)
        if (!use[z]) {
            sg[x] = z;
            return;
        }
}
int sgo1(int x) {
    return x - (1 << (31 - __builtin_clz(x)));
}
int main() {
    for (int i = 1; i <= 2000; ++i) {
        calcSG(i);
        printf("%d %d %d\n", i, sg[i], sgo1(i));
        if (sg[i] != sgo1(i))
            throw;
    }
    return 0;
}
