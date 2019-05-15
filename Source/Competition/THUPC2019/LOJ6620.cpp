#include <algorithm>
#include <cmath>
#include <cstdio>
namespace IO {
    char in[1 << 23];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
const int size = 500005;
typedef double FT;
FT A[size], B[size], rt[size], minv = 1e20;
FT apply(int n, FT rt) {
    FT res = 0.0;
    for(int i = 1; i <= n; ++i)
        res += fabs(A[i] * rt + B[i]);
    minv = std::min(minv, res);
    return res;
}
int main() {
    IO::init();
    int n = read(), rsiz = 1;
    rt[0] = 0.0;
    for(int i = 1; i <= n; ++i) {
        A[i] = read();
        B[i] = read();
        if(A[i])
            rt[rsiz++] = -B[i] / A[i];
    }
    std::sort(rt, rt + rsiz);
    int l = 0, r = rsiz - 1;
    while(r - l >= 3) {
        int lm = (l * 2 + r) / 3, rm = (l + r * 2) / 3;
        FT lv = apply(n, rt[lm]),
           rv = apply(n, rt[rm]);
        if(lv < rv)
            r = rm - 1;
        else
            l = lm + 1;
    }
    for(int i = l; i <= r; ++i)
        apply(n, rt[i]);
    printf("%.10lf\n", minv);
    return 0;
}
