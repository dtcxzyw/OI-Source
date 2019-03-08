#include <algorithm>
#include <cstdio>
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
const int size = 100005;
typedef long long Int64;
#define asInt64 static_cast<Int64>
int siz[size << 2], h[size];
struct Slope {
    int X, Y;
    Slope() : X(1), Y(0) {}
    Slope(int X, int Y) : X(X), Y(Y) {}
    bool operator<(const Slope& rhs) const {
        return asInt64(X) * rhs.Y > asInt64(rhs.X) * Y;
    }
    bool operator<=(const Slope& rhs) const {
        return asInt64(X) * rhs.Y >=
            asInt64(rhs.X) * Y;
    }
} slope[size << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
int split(int l, int r, int id, Slope k) {
    if(slope[id] <= k)
        return 0;
    if(l == r)
        return 1;
    if(k < Slope(l, h[l]))
        return siz[id];
    int m = (l + r) >> 1;
    if(slope[id << 1] < k)
        return split(rs, k);
    return split(ls, k) + siz[id] - siz[id << 1];
}
void insert(int l, int r, int id, Slope k) {
    if(l == r)
        slope[id] = k, siz[id] = 1;
    else {
        int m = (l + r) >> 1;
        if(k.X <= m)
            insert(ls, k);
        else
            insert(rs, k);
        slope[id] = std::max(slope[id << 1],
                             slope[id << 1 | 1]);
        siz[id] =
            siz[id << 1] + split(rs, slope[id << 1]);
    }
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= m; ++i) {
        int x = read();
        int y = read();
        h[x] = y;
        insert(1, n, 1, Slope(x, y));
        printf("%d\n", siz[1]);
    }
    return 0;
}
