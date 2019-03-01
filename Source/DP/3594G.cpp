#include <algorithm>
#include <cstdio>
typedef long long Int64;
Int64 read() {
    Int64 res = 0;
    int c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 2000005;
const Int64 inf = 1LL << 60;
Int64 A[size];
int main() {
    int n = read();
    Int64 p = read(), csum = 0;
    int d = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    int l = 1, r = d, maxl = 0;
    while(r < n && csum + A[r + 1] <= p)
        csum += A[++r];
    maxl = r - l + 1;
    for(int dl = 2; dl + d - 1 <= n; ++dl) {
        int dr = dl + d - 1;
        csum += A[dl - 1];
        if(r >= dr)
            csum -= A[dr];
        else
            r = dr;
        while(csum > p) {
            Int64 lv = l < dl ? A[l] : 0;
            Int64 rv = r > dr ? A[r] : 0;
            if(lv > rv)
                csum -= lv, ++l;
            else
                csum -= rv, --r;
        }
        while(csum < p) {
            Int64 lv = l > 1 ? A[l - 1] : inf;
            Int64 rv = r < n ? A[r + 1] : inf;
            if(lv + csum > p && rv + csum > p)
                break;
            if(lv < rv)
                csum += lv, --l;
            else
                csum += rv, ++r;
        }
        maxl = std::max(maxl, r - l + 1);
    }
    printf("%d\n", maxl);
    return 0;
}
