#include <algorithm>
#include <cstdio>
#include <vector>
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
const int size = 1000005;
typedef long long HashT;
HashT hashA[size], hashB[size], base[size];
void preHash(int* A, HashT* hash, int n) {
    for(int i = 1; i <= n; ++i)
        hash[i] = hash[i - 1] * 131 + A[i];
}
HashT hash(HashT* A, int l, int r) {
    int len = r - l + 1;
    return A[r] - A[l - 1] * base[len];
}
int A[size], B[size], nxt[size], len[size];
struct Range {
    int a, b, c, d;
    Range(int a, int b, int c, int d)
        : a(a), b(b), c(c), d(d) {}
    bool operator<(const Range& rhs) const {
        return a < rhs.a;
    }
    Range inv() const {
        return Range(c, d, a, b);
    }
    Range inv(int n) const {
        return Range(n + 1 - b, n + 1 - a, n + 1 - d,
                     n + 1 - c);
    }
};
void output(Range r1, Range r2, Range r3, int n,
            bool invA, bool invB) {
    if(invA)
        r1 = r1.inv(n), r2 = r2.inv(n), r3 = r3.inv(n);
    if(invB)
        r1 = r1.inv(), r2 = r2.inv(), r3 = r3.inv();
    Range r[3] = { r1, r2, r3 };
    std::sort(r, r + 3);
    puts("YES");
    for(int i = 0; i < 3; ++i)
        printf("%d %d\n", r[i].c, r[i].d);
}
bool check(int l, int r, int n, bool invA, bool invB) {
    int siz = r - l + 1;
    HashT lh = hash(hashB, 1, l - 1),
          rh = hash(hashB, r + 1, n);
    if(lh == hash(hashA, siz + 1, r) &&
       rh == hash(hashA, r + 1, n)) {
        output(Range(1, siz, l, r),
               Range(siz + 1, r, 1, l - 1),
               Range(r + 1, n, r + 1, n), n, invA,
               invB);
        return true;
    }
    if(lh == hash(hashA, n - l + 2, n) &&
       rh == hash(hashA, siz + 1, n - l + 1)) {
        output(Range(1, siz, l, r),
               Range(siz + 1, n - l + 1, r + 1, n),
               Range(n - l + 2, n, 1, l - 1), n, invA,
               invB);
        return true;
    }
    return false;
}
bool scan(int n, bool invA, bool invB,
          std::vector<int>* X) {
    preHash(A, hashA, n);
    preHash(B, hashB, n);
    if(hashA[n] == hashB[n]) {
        output(Range(1, 1, 1, 1),
               Range(2, n - 1, 2, n - 1),
               Range(n, n, n, n), n, invA, invB);
        return true;
    }
    {
        int p = 0;
        nxt[1] = 0;
        for(int i = 2; i <= n; ++i) {
            while(p && A[p + 1] != A[i])
                p = nxt[p];
            if(A[p + 1] == A[i])
                ++p;
            nxt[i] = p;
        }
    }
    {
        int p = 0;
        for(int i = 1; i < n; ++i) {
            while(p && A[p + 1] != B[i])
                p = nxt[p];
            if(A[p + 1] == B[i])
                ++p;
            int cp = p;
            while(cp) {
                if(cp != i &&
                   check(i - cp + 1, i, n, invA, invB))
                    return true;
                cp = nxt[cp];
            }
        }
        if(X) {
            while(p && A[p + 1] != B[n])
                p = nxt[p];
            if(A[p + 1] == B[n])
                ++p;
            while(p) {
                X->push_back(p);
                p = nxt[p];
            }
        }
    }
    return false;
}
void foo() {
    int n = read();
    int m = read();
    base[0] = 1;
    for(int i = 1; i <= n; ++i)
        base[i] = base[i - 1] * 131;
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    for(int i = 1; i <= n; ++i)
        B[i] = read();
    std::vector<int> X, Y;
    if(scan(n, false, false, &X))
        return;
    std::reverse(A + 1, A + n + 1);
    std::reverse(B + 1, B + n + 1);
    if(scan(n, true, false, &Y))
        return;
    for(int i = 0; i < X.size(); ++i) {
        int x = X[i], mx = n + 1 - x;
        for(int j = 0; j < Y.size(); ++j) {
            int y = Y[j], my = n + 1 - y;
            if(y + 1 <= mx - 1 &&
               hash(hashA, y + 1, mx - 1) ==
                   hash(hashB, x + 1, my - 1)) {
                output(Range(1, y, my, n),
                       Range(y + 1, mx - 1, x + 1,
                             my - 1),
                       Range(mx, n, 1, x), n, true,
                       false);
                return;
            }
        }
    }
    std::swap_ranges(A + 1, A + n + 1, B + 1);
    if(scan(n, true, true, 0))
        return;
    puts("NO");
}
int main() {
    int t = read();
    while(t--)
        foo();
    return 0;
}
