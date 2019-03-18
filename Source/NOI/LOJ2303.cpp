#include <algorithm>
#include <cstdio>
#include <cstring>
namespace IO {
    const int size = 1 << 24;
    char in[size];
    void init() {
        fread(in, 1, size, stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[size], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
int getChar() {
    int c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    return c;
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

void write(int x) {
    if(x >= 10)
        write(x / 10);
    IO::putc('0' + x % 10);
}
typedef unsigned long long Int64;
const int fac = 7, mod = 998244353;
struct HashTable {
    static const int modu = 400009, modv = 399989;
    Int64 key[modu];
    int cnt[modu];
    template <int op>
    void modify(Int64 k) {
        int ha = k % modu, hb = k % modv + 1, cur = ha;
        while(true) {
            if(key[cur] == 0)
                key[cur] = k;
            if(key[cur] == k) {
                cnt[cur] += op;
                return;
            }
            cur += hb;
            if(cur >= modu)
                cur -= modu;
        }
    }
    int find(Int64 k) {
        int ha = k % modu, hb = k % modv + 1, cur = ha;
        while(true) {
            if(key[cur] == 0)
                return 0;
            if(key[cur] == k)
                return cnt[cur];
            cur += hb;
            if(cur >= modu)
                cur -= modu;
        }
    }
} LUT[51];
const int size = 200005;
char A[size];
int nxt[size], pre[size], maxk = 0;
Int64 tmp[55], base[55];
template <int op>
void calc(int b) {
    int clen = 1, cp = b;
    Int64 cur = A[b];
    while(clen < maxk && pre[cp]) {
        cp = pre[cp];
        cur += base[clen] * A[cp];
        tmp[++clen] = cur;
    }
    for(int i = clen; i >= 2; --i) {
        Int64 now = tmp[i];
        int nlen = i, np = b;
        while(true) {
            LUT[nlen].modify<op>(now);
            if(nlen < maxk && nxt[np]) {
                np = nxt[np];
                ++nlen;
                now = now * fac + A[np];
            } else
                break;
        }
    }
}
char buf[10500005];
struct Op {
    int t, u, v;
} P[500005];
int main() {
    IO::init();
    base[0] = 1;
    for(int i = 1; i <= 50; ++i)
        base[i] = base[i - 1] * fac;
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        A[i] = getChar();
        LUT[1].modify<1>(A[i]);
    }
    int beg = 0;
    for(int t = 1; t <= m; ++t) {
        P[t].t = read();
        switch(P[t].t) {
            case 1: {
                P[t].u = read();
                P[t].v = read();
            } break;
            case 2: {
                P[t].u = read();
            } break;
            case 3: {
                P[t].u = beg;
                int c;
                do
                    c = IO::getc();
                while(c < '0' || c > '9');
                while('0' <= c && c <= '9') {
                    buf[beg++] = c;
                    c = IO::getc();
                }
                buf[beg++] = '\0';
                P[t].v = read();
                maxk = std::max(maxk, P[t].v);
            } break;
        }
    }
    for(int t = 1; t <= m; ++t) {
        switch(P[t].t) {
            case 1: {
                int u = P[t].u, v = P[t].v;
                nxt[u] = v, pre[v] = u;
                calc<1>(v);
            } break;
            case 2: {
                int u = P[t].u, v = nxt[u];
                calc<-1>(v);
                nxt[u] = pre[v] = 0;
            } break;
            case 3: {
                int k = P[t].v;
                Int64 cur = 0, ans = 1;
                for(int l = P[t].u, r = P[t].u,
                        clen = 0;
                    ; ++l) {
                    while(buf[r] && clen < k)
                        cur = cur * fac + buf[r++],
                        ++clen;
                    if(clen == k) {
                        ans = ans * LUT[k].find(cur) %
                            mod;
                        if(ans == 0)
                            break;
                        cur -= buf[l] * base[k - 1],
                            --clen;
                    } else
                        break;
                }
                write(ans);
                IO::putc('\n');
            } break;
        }
    }
    IO::uninit();
    return 0;
}
