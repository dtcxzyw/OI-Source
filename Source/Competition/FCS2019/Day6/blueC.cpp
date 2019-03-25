#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 200005;
char trans[30], S[size * 2], T[size];
int rcnt = 0, rsiz[30], rid[30], rpos[30];
// a->b
int dis(int a, int b) {
    int c = rsiz[rid[a]];
    int d = rpos[b] - rpos[a];
    if(d < 0)
        d += c;
    return d;
}
void calcCycle() {
    for(int i = 0; i < 26; ++i)
        if(!rid[i]) {
            int cid = ++rcnt, x = i;
            do {
                ++rsiz[cid];
                rpos[x] = rsiz[cid];
                rid[x] = cid;
                x = trans[x];
            } while(!rid[x]);
        }
}
int last[30];
void pre(const char* A, int n, int* B) {
    memset(last, -1, sizeof(last));
    for(int i = 1; i <= n; ++i) {
        int ch = A[i], id = rid[ch];
        B[i] = id << 5 |
            (last[id] == -1 ? 31 : dis(last[id], ch));
        last[id] = ch;
    }
}
bool equal(int sc, int tc) {
    int hs = sc >> 5, ls = sc & 31, ht = tc >> 5,
        lt = tc & 31;
    return hs == ht && (lt == 31 || ls == lt);
}
int SS[size * 2], TT[size], nxt[size], diff[30];
typedef long long Int64;
// x\equiv a\pmod{p}
struct Expr {
    Int64 a, p;
    Expr(Int64 a, Int64 p) : a(a), p(p) {}
};
void exgcd(Int64 a, Int64 b, Int64& d, Int64& x,
           Int64& y) {
    if(b) {
        exgcd(b, a % b, d, y, x);
        y -= a / b * x;
    } else
        d = a, x = 1, y = 0;
}
Expr makeExpr(int a, int b, int p) {
    Int64 d, x, y;
    exgcd(a, p, d, x, y);
    if(b % d)
        return Expr(0, 0);
    Int64 fac = b / d;
    int mod = p / d;
    if(x < 0)
        x += mod;
    return Expr(fac * x % mod, mod);
}
Expr merge(const Expr& a, const Expr& b) {
    Int64 da = b.a - a.a;
    Int64 d, x, y;
    exgcd(a.p, b.p, d, x, y);
    if(da % d)
        return Expr(0, 0);
    Int64 mod = a.p / d * b.p;
    if(x < 0)
        x += mod;
    Int64 fac = da / d;
    if(fac < 0)
        fac += mod;
    return Expr((a.a + x * fac % mod * a.p) % mod,
                mod);
}
const int inf = 1 << 30;
int solve(int offset, int a, int b, int n) {
    Expr res = makeExpr(a, offset, n);
    if(res.p == 0)
        return inf;
    for(int i = 1; i <= rcnt; ++i) {
        if(diff[i] != -1) {
            Expr cur = makeExpr(b, diff[i], rsiz[i]);
            if(cur.p == 0)
                return inf;
            res = merge(res, cur);
            if(res.p == 0)
                return inf;
        }
    }
    return res.a == 0 ? res.p : res.a;
}
int main() {
    int n, a, b;
    scanf("%d%d%d%s%s%s", &n, &a, &b, trans, S + 1,
          T + 1);
    for(int i = 0; i < 26; ++i)
        trans[i] -= 'a';
    for(int i = 1; i <= n; ++i) {
        S[i] -= 'a', T[i] -= 'a';
        S[i + n] = S[i];
    }
    calcCycle();
    pre(S, 2 * n, SS);
    pre(T, n, TT);
    nxt[1] = 0;
    for(int i = 2, j = 0; i <= n; ++i) {
        while(j && !equal(TT[i], TT[j + 1]))
            j = nxt[j];
        if(equal(TT[i], TT[j + 1]))
            ++j;
        nxt[i] = j;
    }
    memset(diff, -1, sizeof(diff));
    int res = inf;
    for(int i = 1, j = 0; i <= 2 * n; ++i) {
        while(j && !equal(SS[i], TT[j + 1]))
            j = nxt[j];
        if(equal(SS[i], TT[j + 1])) {
            ++j;
            diff[rid[S[i]]] = dis(S[i], T[j]);
        }
        if(j == n) {
            res = std::min(res, solve(i - n, a, b, n));
            j = nxt[j];
        }
    }
    if(res == inf)
        puts("-1");
    else
        printf("%d\n", res);
    return 0;
}
