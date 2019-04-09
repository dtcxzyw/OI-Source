#include <algorithm>
#include <cstdio>
#include <vector>
namespace IO {
    char in[1 << 24];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 20], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
void print(int x) {
    if(x >= 10)
        print(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 300005;
typedef long long Int64;
struct Info {
    int l, r, c;
} X[size];
int m;
Int64 S[size];
void add(int x, int op) {
    while(x <= m) {
        S[x] += op;
        x += x & -x;
    }
}
void addRange(int l, int r, int op) {
    if(l <= r)
        add(l, op), add(r + 1, -op);
    else {
        addRange(1, r, op);
        addRange(l, m, op);
    }
}
Int64 query(int x) {
    Int64 res = 0;
    while(x) {
        res += S[x];
        x -= x & -x;
    }
    return res;
}
std::vector<int> P[size];
const Int64 inf = 1LL << 35;
Int64 queryAll(int x) {
    Int64 res = 0;
    for(int i = 0; i < P[x].size(); ++i)
        res = std::min(inf, res + query(P[x][i]));
    return res;
}
struct Nation {
    int id, k;
} A[size];
int ans[size];
void solve(int l, int r, int b, int e) {
    if(b > e)
        return;
    if(l == r) {
        for(int i = b; i <= e; ++i)
            ans[A[i].id] = l;
    } else {
        int mid = (l + r) >> 1;
        for(int i = l; i <= mid; ++i)
            addRange(X[i].l, X[i].r, X[i].c);
        auto lambda = [](Nation& x) {
            Int64 c = queryAll(x.id);
            if(x.k > c) {
                x.k -= c;
                return false;
            }
            return true;
        };
        int pos =
            std::partition(A + b, A + e + 1, lambda) -
            A;
        for(int i = l; i <= mid; ++i)
            addRange(X[i].l, X[i].r, -X[i].c);
        solve(l, mid, b, pos - 1);
        solve(mid + 1, r, pos, e);
    }
}
int main() {
    IO::init();
    int n = read();
    m = read();
    for(int i = 1; i <= m; ++i)
        P[read()].push_back(i);
    for(int i = 1; i <= n; ++i) {
        A[i].id = i;
        A[i].k = read();
    }
    int k = read();
    for(int i = 1; i <= k; ++i) {
        X[i].l = read();
        X[i].r = read();
        X[i].c = read();
    }
    solve(1, k + 1, 1, n);
    for(int i = 1; i <= n; ++i) {
        if(ans[i] <= k)
            print(ans[i]);
        else {
            IO::putc('N');
            IO::putc('I');
            IO::putc('E');
        }
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
