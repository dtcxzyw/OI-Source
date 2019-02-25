#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
typedef double FT;
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
FT readFT() {
    char buf[32];
    int cnt = 0, c;
    do
        c = getchar();
    while(!isgraph(c));
    while(isgraph(c)) {
        buf[cnt++] = c;
        c = getchar();
    }
    buf[cnt] = '\0';
    return strtod(buf, 0);
}
int getOp() {
    int c;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    int res = c;
    while('a' <= c && c <= 'z')
        c = getchar();
    return res;
}
const int size = 100005, prec = 16;
struct Sin {};
struct Exp {};
struct Linear {};
struct Pow {};
struct Clear {};
struct Poly {
    FT k[prec];
    Poly() {}
    Poly(Clear) {
        memset(k, 0, sizeof(FT) * prec);
    }
    Poly(Linear, FT a, FT b) : Poly(Clear{}) {
        k[1] = a, k[0] = b;
    }
    Poly(Pow, FT a, FT b, int n) : Poly(Clear{}) {
        k[0] = 1.0;
        for(int i = 1; i <= n; ++i) {
            for(int j = prec - 1; j >= 1; --j)
                k[j] = k[j] * b + k[j - 1] * a;
            k[0] *= b;
        }
    }
    Poly(Sin, FT a, FT b) : Poly(Clear{}) {
        FT fac = 1.0;
        for(int i = 1; i < prec; i += 2) {
            Poly tmp(Pow{}, a, b, i);
            for(int j = 0; j <= i; ++j)
                k[j] += fac * tmp.k[j];
            fac = -fac / (i + 1) / (i + 2);
        }
    }
    Poly(Exp, FT a, FT b) : Poly(Clear{}) {
        FT fac = 1.0;
        for(int i = 0; i < prec; ++i) {
            if(i)
                fac /= i;
            Poly tmp(Pow{}, a, b, i);
            for(int j = 0; j <= i; ++j)
                k[j] += fac * tmp.k[j];
        }
    }
    Poly& operator+=(const Poly& rhs) {
        for(int i = 0; i < prec; ++i)
            k[i] += rhs.k[i];
        return *this;
    }
    Poly operator+(const Poly& rhs) const {
        Poly res(*this);
        return res += rhs;
    }
    Poly& operator-=(const Poly& rhs) {
        for(int i = 0; i < prec; ++i)
            k[i] -= rhs.k[i];
        return *this;
    }
    FT operator()(FT x) const {
        FT res = 0.0;
        for(int i = prec - 1; i >= 0; --i)
            res = res * x + k[i];
        return res;
    }
};
struct Node {
    int p, c[2];
    Poly val, sum;
    bool rev;
} T[size];
#define ls T[u].c[0]
#define rs T[u].c[1]
bool isRoot(int u) {
    int p = T[u].p;
    return T[p].c[0] != u && T[p].c[1] != u;
}
int getPos(int u) {
    int p = T[u].p;
    return T[p].c[1] == u;
}
void connect(int u, int p, int c) {
    T[u].p = p;
    T[p].c[c] = u;
}
void update(int u) {
    T[u].sum = T[ls].sum + T[u].val + T[rs].sum;
}
void rotate(int u) {
    int ku = getPos(u);
    int p = T[u].p;
    int kp = getPos(p);
    int pp = T[p].p;
    int t = T[u].c[ku ^ 1];
    T[u].p = pp;
    if(!isRoot(p))
        T[pp].c[kp] = u;
    connect(p, u, ku ^ 1);
    connect(t, p, ku);
    update(p);
    update(u);
}
void pushDown(int u) {
    if(T[u].rev) {
        std::swap(ls, rs);
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
    }
}
void push(int u) {
    if(!isRoot(u))
        push(T[u].p);
    pushDown(u);
}
void splay(int u) {
    push(u);
    while(!isRoot(u)) {
        int p = T[u].p;
        if(!isRoot(p))
            rotate(getPos(p) == getPos(u) ? p : u);
        rotate(u);
    }
}
void access(int u) {
    int v = 0;
    do {
        splay(u);
        rs = v;
        update(u);
        v = u;
        u = T[u].p;
    } while(u);
}
void makeRoot(int u) {
    access(u);
    splay(u);
    T[u].rev ^= 1;
    pushDown(u);
}
void split(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
}
void link(int u, int v) {
    split(u, v);
    T[u].p = v;
}
void cut(int u, int v) {
    split(u, v);
    T[v].c[0] = T[u].p = 0;
    update(v);
}
bool test(int u, int v) {
    split(u, v);
    pushDown(v);
    while(T[v].c[0]) {
        v = T[v].c[0];
        pushDown(v);
    }
    splay(v);
    return u == v;
}
Poly genPoly(int t, FT a, FT b) {
    switch(t) {
        case 1:
            return Poly(Sin{}, a, b);
        case 2:
            return Poly(Exp{}, a, b);
        case 3:
            return Poly(Linear{}, a, b);
    }
}
int main() {
    int n, m;
    char str[20];
    scanf("%d%d%s", &n, &m, str);
    for(int i = 1; i <= n; ++i) {
        int t = read();
        FT a = readFT();
        FT b = readFT();
        T[i].sum = T[i].val = genPoly(t, a, b);
    }
    for(int i = 1; i <= m; ++i) {
        int op = getOp();
        int u = read() + 1;
        int v = read() + 1;
        switch(op) {
            case 'a':
                link(u, v);
                break;
            case 'd':
                cut(u, v);
                break;
            case 'm': {
                access(u);
                splay(u);
                FT a = readFT();
                FT b = readFT();
                T[u].val = genPoly(v - 1, a, b);
                update(u);
            } break;
            case 't': {
                if(test(u, v)) {
                    FT x = readFT();
                    printf("%.8e\n", T[u].sum(x));
                } else
                    puts("unreachable");
            } break;
        }
    }
    return 0;
}
