#include <algorithm>
#include <cstdio>
#include <unordered_set>
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
typedef unsigned long long HashT;
#define asInt(x) static_cast<int>(x)
const int size = 200005, fac = 1313131;
HashT L[size], R[size], P[size];
int res[size], siz = 0, ans = 0, A[size];
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    for(int i = 1; i <= n; ++i)
        L[i] = L[i - 1] * fac + A[i];
    for(int i = n; i >= 1; --i)
        R[i] = R[i + 1] * fac + A[i];
    P[0] = 1;
    for(int i = 1; i <= n; ++i)
        P[i] = P[i - 1] * fac;
    for(int i = 1; i * std::max(ans, 1) <= n; ++i) {
        std::unordered_set<HashT> hash;
        int end = n - i + 1, limit = ans - n / i;
        for(int j = 1; j <= end && asInt(hash.size()) >= limit;
            j += i) {
            int l = j, r = j + i - 1;
            HashT hashL = L[r] - L[l - 1] * P[i];
            HashT hashR = R[l] - R[r + 1] * P[i];
            hash.insert(hashL * hashR);
            ++limit;
        }
        int cur = hash.size();
        if(cur > ans) {
            ans = cur;
            siz = 0;
        }
        if(cur == ans)
            res[++siz] = i;
    }
    printf("%d %d\n", ans, siz);
    for(int i = 1; i <= siz; ++i)
        printf("%d ", res[i]);
    putchar('\n');
    return 0;
}
