#include <algorithm>
#include <cstdio>
#include <cstring>
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
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = IO::getc();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return flag ? -res : res;
}
void write(int x) {
    if(x >= 10)
        write(x / 10);
    IO::putc('0' + x % 10);
}
int iabs(int x) {
    return x >= 0 ? x : -x;
}
struct Base {
    int A[31], cnt;
    void insert(int x) {
        for(int i = 30; i >= 0; --i)
            if(x & (1 << i)) {
                if(A[i])
                    x ^= A[i];
                else {
                    A[i] = x;
                    ++cnt;
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
Base merge(const Base& A, const Base& B) {
    Base res = A.cnt > B.cnt ? A : B;
    const Base& val = A.cnt > B.cnt ? B : A;
    for(int i = 0; i < 31; ++i)
        if(val.A[i])
            res.insert(val.A[i]);
    return res;
}
const int size = 500005;
Base T[size << 2];
int op[size], P[size];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void insert(int l, int r, int id, int p) {
    T[id].insert(P[p - 1]);
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            insert(ls, p);
        else
            insert(rs, p);
    }
}
void erase(int l, int r, int id, int p) {
    if(l == r)
        memset(&T[id], 0, sizeof(Base));
    else {
        int m = (l + r) >> 1;
        if(p <= m)
            erase(ls, p);
        else
            erase(rs, p);
        T[id] = merge(T[id << 1], T[id << 1 | 1]);
    }
}
int main() {
    IO::init();
    int n = read();
    for(int i = 0; i < n; ++i)
        op[i] = read();
    for(int i = 0; i < n; ++i)
        P[i] = iabs(op[i]);
    std::sort(P, P + n);
    int siz = std::unique(P, P + n) - P;
    for(int i = 0; i < n; ++i) {
        int x = op[i],
            pos =
                std::lower_bound(P, P + siz, iabs(x)) -
            P + 1;
        if(x > 0)
            insert(1, siz, 1, pos);
        else
            erase(1, siz, 1, pos);
        write(T[1].query());
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
