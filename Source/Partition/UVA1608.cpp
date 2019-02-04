#include <algorithm>
#include <csetjmp>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 200005;
int A[size], B[size], pre[size], nxt[size];
jmp_buf buf;
void solve(int l, int r) {
    if(l >= r)
        return;
    for(int lp = l, rp = r; lp <= rp; ++lp, --rp) {
        if(pre[lp] < l && r < nxt[lp]) {
            solve(l, lp - 1);
            solve(lp + 1, r);
            return;
        }
        if(pre[rp] < l && r < nxt[rp]) {
            solve(l, rp - 1);
            solve(rp + 1, r);
            return;
        }
    }
    longjmp(buf, 1);
}
bool foo() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    memcpy(B + 1, A + 1, sizeof(int) * n);
    std::sort(B + 1, B + n + 1);
    int siz = std::unique(B + 1, B + n + 1) - (B + 1);
    for(int i = 1; i <= n; ++i)
        A[i] = std::lower_bound(B + 1, B + siz + 1,
                                A[i]) -
            B;
    for(int i = 1; i <= siz; ++i)
        B[i] = 0;
    for(int i = 1; i <= n; ++i) {
        pre[i] = B[A[i]];
        B[A[i]] = i;
    }
    int end = n + 1;
    for(int i = 1; i <= siz; ++i)
        B[i] = end;
    for(int i = n; i >= 1; --i) {
        nxt[i] = B[A[i]];
        B[A[i]] = i;
    }
    if(setjmp(buf))
        return false;
    else
        solve(1, n);
    return true;
}
int main() {
    int t = read();
    for(int i = 1; i <= t; ++i)
        puts(foo() ? "non-boring" : "boring");
    return 0;
}
