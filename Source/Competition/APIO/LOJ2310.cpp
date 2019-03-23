#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 200005;
struct Node {
    int l, r, siz;
} T[size * 60];
int tcnt = 0;
int insert(int l, int r, int src, int p) {
    int id = ++tcnt;
    T[id] = T[src];
    ++T[id].siz;
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = insert(l, m, T[id].l, p);
        else
            T[id].r = insert(m + 1, r, T[id].r, p);
    }
    return id;
}
int query(int l, int r, int a, int b, int nl, int nr) {
    if(T[a].siz == T[b].siz)
        return 0;
    if(nl <= l && r <= nr)
        return T[b].siz - T[a].siz;
    int m = (l + r) >> 1, res = 0;
    if(nl <= m)
        res += query(l, m, T[a].l, T[b].l, nl, nr);
    if(m < nr)
        res += query(m + 1, r, T[a].r, T[b].r, nl, nr);
    return res;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
const Int64 mask = (1LL << 32) - 1;
void build(int r, int c, int* rt,
           std::vector<Int64>& P) {
    std::sort(P.begin(), P.end());
    for(int i = 1, cur = 0; i <= r; ++i) {
        rt[i] = rt[i - 1];
        while(cur < P.size() && P[cur] >> 32 == i) {
            rt[i] = insert(1, c, rt[i], P[cur] & mask);
            ++cur;
        }
    }
}
Int64 query(int c, int x1, int y1, int x2, int y2,
            int* rt) {
    if(x1 > x2 || y1 > y2)
        return 0;
    Int64 tot = asInt64(x2 - x1 + 1) * (y2 - y1 + 1);
    int sub = query(1, c, rt[x1 - 1], rt[x2], y1, y2);
    return tot - sub;
}
struct HashTable {
    static const int modu = 400009, modv = 399989;
    Int64 key[modu];
    std::vector<Int64> P;
    HashTable& operator=(const HashTable& rhs) {
        memcpy(key, rhs.key, sizeof(key));
        P.resize(rhs.P.size());
        memcpy(P.data(), rhs.P.data(),
               sizeof(Int64) * P.size());
        return *this;
    }
    void insert(Int64 x, Int64 y) {
        if(x <= 0 || y <= 0)
            return;
        Int64 k = x << 32 | y;
        int ha = k % modu, hb = 1 + k % modv, cur = ha;
        while(true) {
            if(key[cur] == 0) {
                key[cur] = k;
                P.push_back(k);
            }
            if(key[cur] == k)
                return;
            cur += hb;
            if(cur >= modu)
                cur -= modu;
        }
    }
} LUT[3];
int rtA[size];
void solve11(int r, int c) {
    build(r, c, rtA, LUT[0].P);
}
int rtB[size];
void solve12(int r, int c) {
    const std::vector<Int64>& P = LUT[0].P;
    LUT[1] = LUT[0];
    for(int i = 0; i < P.size(); ++i) {
        Int64 x = P[i] >> 32, y = P[i] & mask;
        LUT[1].insert(x, y - 1);
    }
    build(r, c, rtB, LUT[1].P);
}
int rtC[size];
void solve21(int r, int c) {
    const std::vector<Int64>& P = LUT[0].P;
    LUT[2] = LUT[0];
    for(int i = 0; i < P.size(); ++i) {
        Int64 x = P[i] >> 32, y = P[i] & mask;
        LUT[2].insert(x - 1, y);
    }
    build(r, c, rtC, LUT[2].P);
}
int rtD[size];
void solve22(int r, int c) {
    const std::vector<Int64>& P = LUT[0].P;
    for(int i = 0; i < P.size(); ++i) {
        Int64 x = P[i] >> 32, y = P[i] & mask;
        LUT[1].insert(x - 1, y);
        LUT[1].insert(x - 1, y - 1);
    }
    build(r, c, rtD, LUT[1].P);
}
char buf[size];
int main() {
    int r = read();
    int c = read();
    int m = read();
    int q = read();
    int x = read();
    int y = read();
    if(m)
        scanf("%s", buf + 1);
    LUT[0].insert(x, y);
    int L = y, R = y, T = x, B = x;
    for(int i = 1; i <= m; ++i) {
        switch(buf[i]) {
            case 'N':
                --x;
                break;
            case 'S':
                ++x;
                break;
            case 'E':
                ++y;
                break;
            case 'W':
                --y;
                break;
        }
        LUT[0].insert(x, y);
        L = std::min(L, y);
        R = std::max(R, y);
        T = std::min(T, x);
        B = std::max(B, x);
    }
    solve11(r, c);
    solve12(r, c);
    solve21(r, c);
    solve22(r, c);
    for(int t = 1; t <= q; ++t) {
        int x1 = read();
        int y1 = read();
        int x2 = read();
        int y2 = read();
        Int64 res = query(c, x1, y1, x2, y2, rtA) -
            query(c, x1, y1, x2, y2 - 1, rtB) -
            query(c, x1, y1, x2 - 1, y2, rtC) +
            query(c, x1, y1, x2 - 1, y2 - 1, rtD);
        if(x1 < T && y1 < L && x2 > B && y2 > R)
            ++res;
        printf("%lld\n", res);
    }
    fprintf(stderr, "%d\n", tcnt);
    for(int i = 0; i < 3; ++i)
        fprintf(stderr, "%d\n",
                static_cast<int>(LUT[i].P.size()));
    return 0;
}
