#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
namespace IO {
    char in[1 << 23];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 23], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
int read(bool& flag) {
    flag = false;
    int res = 0, c;
    do {
        c = IO::getc();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
void write(int x) {
    if(x >= 10)
        write(x / 10);
    IO::putc('0' + x % 10);
}
struct Base {
    int A[31];
    void insert(int x) {
        for(int i = 30; i >= 0; --i)
            if(x & (1 << i)) {
                if(A[i])
                    x ^= A[i];
                else {
                    A[i] = x;
                    return;
                }
            }
    }
    int query() {
        int res = 0;
        for(int i = 30; i >= 0; --i)
            res = std::max(res, res ^ A[i]);
        return res;
    }
};
const int size = 500005;
std::vector<int> T[size << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void solve(int l, int r, int id, const Base& src) {
    Base cur = src;
    for(int i = 0; i < T[id].size(); ++i)
        cur.insert(T[id][i]);
    if(l == r) {
        write(cur.query());
        IO::putc('\n');
    } else {
        int m = (l + r) >> 1;
        solve(ls, cur);
        solve(rs, cur);
    }
}
void insert(int l, int r, int id, int nl, int nr,
            int val) {
    if(nl <= l && r <= nr)
        T[id].push_back(val);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            insert(ls, nl, nr, val);
        if(m < nr)
            insert(rs, nl, nr, val);
    }
}
const int modu = 1000003, modv = 999983;
int LUT[modu], beg[modu], cnt[modu], n;
void insert(int k, int t) {
    int ha = k % modu, hb = 1 + k % modv, cur = ha;
    while(true) {
        if(LUT[cur] == 0) {
            LUT[cur] = k;
            beg[cur] = t;
        }
        if(LUT[cur] == k) {
            ++cnt[cur];
            return;
        }
        cur += hb;
        if(cur >= modu)
            cur -= modu;
    }
}
void erase(int k, int t) {
    int ha = k % modu, hb = 1 + k % modv, cur = ha;
    while(true) {
        if(LUT[cur] == k) {
            if(--cnt[cur] == 0) {
                insert(1, n, 1, beg[cur], t - 1, k);
                LUT[cur] = 0;
            }
            return;
        }
        cur += hb;
        if(cur >= modu)
            cur -= modu;
    }
}
int main() {
    IO::init();
    bool flag;
    n = read(flag);
    memset(beg, 0x3f, sizeof(beg));
    for(int i = 1; i <= n; ++i) {
        int x = read(flag);
        if(flag)
            erase(x, i);
        else
            insert(x, i);
    }
    for(int i = 0; i < modu; ++i)
        if(cnt[i])
            insert(1, n, 1, beg[i], n, LUT[i]);
    Base empty;
    memset(&empty, 0, sizeof(Base));
    solve(1, n, 1, empty);
    IO::uninit();
    return 0;
}
