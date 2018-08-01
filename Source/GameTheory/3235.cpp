#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 100005;
int sg[size];
int getSg(int n) {
    if (sg[n] == -1) {
        int vis = 0;
        for (int i = 2; i <= n;) {
            int a = n / i, b = n % i;
            {
                int res = 0;
                if (b & 1) res ^= getSg(a + 1);
                if ((i - b) & 1) res ^= getSg(a);
                vis |= 1 << res;
            }
            if (b >= a) {
                int res = 0;
                int b2 = b - a;
                if (b2 & 1) res ^= getSg(a + 1);
                if ((i + 1 - b2) & 1) res ^= getSg(a);
                vis |= 1 << res;
            }
            i = n / a + 1;
        }
        sg[n] = __builtin_ctz(~vis);
    }
    return sg[n];
}
bool foo() {
    int n = read(), res = 0;
    while (n--) res ^= getSg(read());
    return res;
}
int main() {
    int t = read();
    int f = read();
    memset(sg, -1, sizeof(sg));
    memset(sg, 0, sizeof(int) * f);
    while (t--) {
        putchar(foo() ? '1' : '0');
        putchar(' ');
    }
    return 0;
}
