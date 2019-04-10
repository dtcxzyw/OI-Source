#include <cstdio>
namespace IO {
    char in[1 << 22];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
}
typedef unsigned int U32;
U32 read() {
    U32 res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
const U32 maxn = 1000000, sqn = 1000;
U32 p[maxn + 5], gcdv[sqn + 5][sqn + 5];
bool flag[maxn + 5];
U32& choose(U32& a, U32& b) {
    return a < b ? a : b;
}
struct Div {
    U32 a, b, c;
    void extend(U32 d) {
        choose(a, choose(b, c)) *= d;
    }
} D[maxn + 5];
void pre() {
    U32 pcnt = 0;
    D[1].a = D[1].b = D[1].c = 1;
    for(U32 i = 2; i <= maxn; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            D[i].a = i, D[i].b = D[i].c = 1;
        }
        for(U32 j = 1; j <= pcnt && i * p[j] <= maxn;
            ++j) {
            U32 val = i * p[j];
            flag[val] = true;
            D[val] = D[i];
            D[val].extend(p[j]);
            if(i % p[j] == 0)
                break;
        }
    }
    for(U32 i = 1; i <= sqn; ++i)
        gcdv[0][i] = gcdv[i][0] = i;
    for(U32 i = 1; i <= sqn; ++i)
        for(U32 j = 1; j <= i; ++j)
            gcdv[i][j] = gcdv[j][i] = gcdv[i - j][j];
}
U32 tmp[4], c;
U32 gcd(U32 a, U32 b) {
    if(a && b) {
        U32 old = b, d;
        for(U32 i = 1; i <= c && b != 1; ++i) {
            if(tmp[i] <= sqn)
                d = gcdv[tmp[i]][b % tmp[i]];
            else
                d = (b % tmp[i] ? 1 : tmp[i]);
            b /= d;
        }
        return old / b;
    }
    return a | b;
}
const U32 maxq = 2005;
U32 A[maxq];
U32 foo() {
    U32 n = read();
    U32 m = read();
    for(U32 i = 0; i < n; ++i)
        A[i] = read();
    U32 res = 0;
    for(U32 i = 0; i < m; ++i) {
        U32 x = read();
        c = 0;
        if(D[x].a != 1)
            tmp[++c] = D[x].a;
        if(D[x].b != 1)
            tmp[++c] = D[x].b;
        if(D[x].c != 1)
            tmp[++c] = D[x].c;
        for(U32 j = 0; j < n; ++j)
            res += gcd(x, A[j]) ^ i ^ j;
    }
    return res;
}
int main() {
    IO::init();
    pre();
    U32 t = read();
    for(U32 i = 1; i <= t; ++i)
        printf("%u\n", foo());
    return 0;
}
