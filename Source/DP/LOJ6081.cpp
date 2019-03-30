#include <algorithm>
#include <cstdio>
#include <functional>
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
    char out[1 << 21], *S = out;
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
typedef long long Int64;
void print(Int64 x) {
    if(x >= 10)
        print(x / 10);
    IO::putc('0' + x % 10);
}
const int maxK = 100005, maxN = 1000005, maxW = 305;
Int64 dp[maxK], S[maxN];
std::vector<int> W[maxW];
int tp[maxK], ctrans;
const Int64 inf = 1LL << 62;
void solve(int l, int r, int b, int e) {
    if(l > r)
        return;
    int m = (l + r) >> 1, end = std::min(m, e),
        beg = std::max(b, m - ctrans), mtp = 0;
    Int64 dpv = -1;
    for(int i = beg; i <= end; ++i) {
        Int64 cdp = dp[tp[i]] + S[m - i];
        if(cdp > dpv)
            dpv = cdp, mtp = i;
    }
    solve(m + 1, r, mtp, e);
    solve(l, m - 1, b, mtp);
    dp[tp[m]] = dpv;
}
int main() {
    IO::init();
    int n = read();
    int K = read();
    for(int i = 0; i < n; ++i) {
        int w = read();
        W[w].push_back(read());
    }
    for(int i = 1; i <= 300; ++i)
        if(W[i].size()) {
            std::sort(W[i].begin(), W[i].end(),
                      std::greater<Int64>());
            for(int j = 0; j < W[i].size(); ++j)
                S[j + 1] = S[j] + W[i][j];
            ctrans = W[i].size();
            for(int j = 0; j < i; ++j) {
                int tcnt = 0;
                for(int k = j; k <= K; k += i)
                    tp[++tcnt] = k;
                solve(1, tcnt, 1, tcnt);
            }
        }
    for(int i = 1; i <= K; ++i) {
        print(dp[i]);
        IO::putc(' ');
    }
    IO::uninit();
    return 0;
}
