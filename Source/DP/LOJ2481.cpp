#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
typedef double FT;
FT readFT() {
    char buf[32];
    int cnt = 0, c;
    do
        c = getchar();
    while(!isgraph(c));
    while(isgraph(c)) {
        buf[cnt++] = c;
        c = getchar();
    }
    buf[cnt] = '\0';
    return strtod(buf, 0);
}
const int size = 100005;
FT A[size], B[size];
bool cmp(FT a, FT b) {
    return a > b;
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        A[i] = readFT();
        B[i] = readFT();
    }
    std::sort(A + 1, A + n + 1, cmp);
    std::sort(B + 1, B + n + 1, cmp);
    int lp = 1, rp = 1, cnt = 0, end = 2 * n;
    FT ls = 0.0, rs = 0.0, res = 0.0;
    while(cnt < end) {
        if(lp <= n && rp <= n) {
            if(ls < rs)
                ls += A[lp++];
            else
                rs += B[rp++];
        } else if(lp <= n)
            ls += A[lp++];
        else
            rs += B[rp++];
        ++cnt;
        res = std::max(res, std::min(ls, rs) - cnt);
    }
    printf("%.4lf\n", res);
    return 0;
}
