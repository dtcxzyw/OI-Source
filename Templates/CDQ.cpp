// 3810
#include <algorithm>
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
const int size = 100005;
int A[2 * size], k;
void add(int x) {
    while(x <= k) {
        ++A[x];
        x += x & -x;
    }
}
void clear(int x) {
    while(x <= k && A[x]) {
        A[x] = 0;
        x += x & -x;
    }
}
int query(int x) {
    int res = 0;
    while(x) {
        res += A[x];
        x -= x & -x;
    }
    return res;
}
struct Pos {
    int x, y, z, ans;
} P[size], tmp[size];
bool cmpX(const Pos& a, const Pos& b) {
    return a.x < b.x;
}
int nxt(int p, int e, int k) {
    while(p < e && P[p].x != k)
        ++p;
    return p;
}
int cdq(int b, int e) {
    if(e - b <= 1)
        return P[b].z;
    int m = (b + e) >> 1;
    int key = P[m].x;
    k = std::max(cdq(b, m), cdq(m, e));
    // r->l
    {
        int lp = nxt(b, m, key), rp = nxt(m, e, key);
        while(lp < m && rp < e) {
            if(P[rp].y <= P[lp].y) {
                add(P[rp].z);
                rp = nxt(rp + 1, e, key);
            } else {
                P[lp].ans += query(P[lp].z);
                lp = nxt(lp + 1, m, key);
            }
        }
        while(lp < m) {
            P[lp].ans += query(P[lp].z);
            lp = nxt(lp + 1, m, key);
        }
        for(int i = nxt(m, rp, key); i < rp;
            i = nxt(i + 1, rp, key))
            clear(P[i].z);
    }
    // l->r
    {
        int lp = b, rp = m, cp = b;
        while(lp < m && rp < e) {
            if(P[lp].y <= P[rp].y) {
                add(P[lp].z);
                tmp[cp++] = P[lp++];
            } else {
                P[rp].ans += query(P[rp].z);
                tmp[cp++] = P[rp++];
            }
        }
        while(rp < e) {
            P[rp].ans += query(P[rp].z);
            tmp[cp++] = P[rp++];
        }
        for(int i = b; i < lp; ++i)
            clear(P[i].z);
        while(lp < m)
            tmp[cp++] = P[lp++];
        memcpy(P + b, tmp + b, sizeof(Pos) * (e - b));
    }
    return k;
}
int cnt[size];
int main() {
    int n = read();
    k = read();
    for(int i = 0; i < n; ++i) {
        P[i].x = read();
        P[i].y = read();
        P[i].z = read();
    }
    std::sort(P, P + n, cmpX);
    cdq(0, n);
    for(int i = 0; i < n; ++i)
        ++cnt[P[i].ans];
    for(int i = 0; i < n; ++i)
        printf("%d\n", cnt[i]);
    return 0;
}
