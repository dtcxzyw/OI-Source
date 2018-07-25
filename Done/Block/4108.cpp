#include <algorithm>
#include <cmath>
#include <cstdio>
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
Int64 read() {
    Int64 res = 0;
    int c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
int getOp() {
    int c;
    do
        c = getchar();
    while (c != 'M' && c != 'Q');
    return c;
}
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
const int size = 100005, blockSize = 320;
int A[size], bgv[blockSize], pbgv[blockSize], pbxv[blockSize];
std::pair<int, int> xorv[size];
void rebuild(int beg, int end, int &cg, int &cx) {
    cg = cx = 0;
    for (int i = beg; i < end; ++i) {
        cg = gcd(cg, A[i]);
        cx ^= A[i];
        xorv[i] = std::make_pair(cx, i);
    }
    std::sort(xorv + beg, xorv + end);
}
int find(int beg, int end, int key) {
    int pos = std::lower_bound(xorv + beg, xorv + end, std::make_pair(key, 0)) - xorv;
    if (pos != end && xorv[pos].first == key) return xorv[pos].second;
    return -1;
}
int main() {
    int n = read();
    for (int i = 0; i < n; ++i)
        A[i] = read();
    int bsiz = sqrt(n);
    int bcnt = n / bsiz;
    for (int i = 0; i <= bcnt; ++i) {
        int beg = i * bsiz;
        int end = std::min((i + 1) * bsiz, n);
        rebuild(beg, end, bgv[i], pbxv[i]);
    }
    pbgv[0] = bgv[0];
    for (int i = 1; i <= bcnt; ++i) {
        pbgv[i] = gcd(pbgv[i - 1], bgv[i]);
        pbxv[i] ^= pbxv[i - 1];
    }
    int q = read();
    while (q--) {
        int op = getOp();
        if (op == 'M') {
            int id = read();
            int old = A[id];
            A[id] = read();
            int bid = id / bsiz;
            int beg = bid * bsiz;
            int end = std::min((bid + 1) * bsiz, n);
            int cx;
            rebuild(beg, end, bgv[bid], cx);

            for (int i = bid; i <= bcnt; ++i) {
                int cpbgv = i ? pbgv[i - 1] : 0;
                pbgv[i] = gcd(cpbgv, bgv[i]);
            }
            int delta = A[id] ^ old;
            for (int i = bid; i <= bcnt; ++i)
                pbxv[i] ^= delta;
        } else {
            Int64 x = read();
            int res = -1;
            for (int i = 0; i <= bcnt && res == -1; ++i) {
                int cpbgv = i ? pbgv[i - 1] : 0;
                int cpbxv = i ? pbxv[i - 1] : 0;
                int beg = i * bsiz;
                int end = std::min((i + 1) * bsiz, n);
                if (cpbgv == pbgv[i]) {
                    Int64 val = (x / cpbgv) ^ cpbxv;
                    if (val <= 2147483647)
                        res = find(beg, end, val);
                } else {
                    for (int j = beg; j < end; ++j) {
                        cpbgv = gcd(cpbgv, A[j]);
                        cpbxv ^= A[j];
                        if (asInt64(cpbgv) * cpbxv == x) {
                            res = j;
                            break;
                        }
                    }
                }
            }
            if (res >= 0)
                printf("%d\n", res);
            else
                puts("no");
        }
    }
    return 0;
}
