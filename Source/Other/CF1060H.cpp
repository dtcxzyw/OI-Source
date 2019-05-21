#include <cstdio>
#include <memory>
#include <set>
std::set<int> freeReg, dirReg;
int allocReg() {
    return dirReg.size() ? *dirReg.begin() :
                           *freeReg.begin();
}
class Value {
private:
    int mReg;

public:
    Value(int reg) : mReg(reg) {
        freeReg.erase(reg);
        dirReg.erase(reg);
    }
    Value() : Value(allocReg()) {}
    ~Value() {
        dirReg.insert(mReg);
    }
    int get() const {
        return mReg;
    }
};
using SV = std::shared_ptr<Value>;
SV makeValue(int reg) {
    return std::make_shared<Value>(reg);
}
SV newValue() {
    return makeValue(allocReg());
}
SV getOne() {
    return makeValue(*freeReg.begin());
}
SV operator+(SV a, SV b) {
    if(a && b) {
        SV c = newValue();
        printf("+ %d %d %d\n", a->get(), b->get(),
               c->get());
        return c;
    }
    return a ? a : b;
}
SV powv(SV a) {
    SV b = newValue();
    printf("^ %d %d\n", a->get(), b->get());
    return b;
}
void output(SV x) {
    printf("f %d\n", x->get());
}
int d, p;
SV mul(SV x, int k) {
    SV res;
    while(k) {
        if(k & 1)
            res = res + x;
        k >>= 1, x = x + x;
    }
    return res;
}
SV operator-(SV x) {
    return mul(x, p - 1);
}
SV operator-(SV a, SV b) {
    return a + (-b);
}
const int size = 15;
int M[size][size], A[size][size], B[size], C[size];
using Int64 = long long;
#define asInt64 static_cast<Int64>
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % p;
        k >>= 1, a = a * a % p;
    }
    return res;
}
void solve() {
    M[0][0] = 1;
    for(int i = 1; i <= d; ++i) {
        M[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            M[i][j] =
                (M[i - 1][j - 1] + M[i - 1][j]) % p;
    }
    for(int i = 0; i <= d; ++i) {
        Int64 pw = 1;
        for(int j = d; j >= 0; --j) {
            A[j][i] = M[d][j] * pw % p;
            pw = pw * i % p;
        }
    }
    B[2] = 1;
    for(int i = 0; i <= d; ++i) {
        int x = -1;
        for(int j = i; j <= d; ++j)
            if(A[j][i]) {
                x = j;
                break;
            }
        if(x == -1)
            throw;
        if(i != x) {
            std::swap(B[i], B[x]);
            for(int j = i; j <= d; ++j)
                std::swap(A[i][j], A[x][j]);
        }
        Int64 inv = powm(A[i][i], p - 2);
        for(int j = i + 1; j <= d; ++j) {
            Int64 fac = A[j][i] * inv % p;
            B[j] = (B[j] - B[i] * fac) % p;
            for(int k = i; k <= d; ++k)
                A[j][k] =
                    (A[j][k] - A[i][k] * fac) % p;
        }
    }
    for(int i = d; i >= 0; --i) {
        Int64 cur = B[i];
        for(int j = d; j > i; --j)
            cur = (cur - asInt64(C[j]) * A[i][j]) % p;
        C[i] = cur * powm(A[i][i], p - 2) % p;
        if(C[i] < 0)
            C[i] += p;
    }
}
SV one;
SV sqr(SV x) {
    if(d == 2)
        return powv(x);
    SV res;
    for(int i = 0; i <= d; ++i) {
        res = res + mul(powv(x), C[i]);
        x = x + one;
    }
    return res;
}
SV half(SV x) {
    int k = (p + 1) / 2;
    return mul(x, k);
}
int main() {
    dirReg.insert(1);
    dirReg.insert(2);
    for(int i = 3; i <= 5000; ++i)
        freeReg.insert(i);
    auto x = makeValue(1);
    auto y = makeValue(2);
    scanf("%d%d", &d, &p);
    one = getOne();
    solve();
    output(half(sqr(x + y) - (sqr(x) + sqr(y))));
    return 0;
}
