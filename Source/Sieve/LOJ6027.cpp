#include <cmath>
#include <cstdio>
typedef long long Int64;
struct Complex {
    int a, b;
    Complex() {}
    explicit Complex(int x)
        : a((x & 3) == 1), b((x & 3) == 3) {}
    Complex(int a, int b) : a(a), b(b) {}
    Complex operator+(const Complex& rhs) const {
        return Complex(a + rhs.a, b + rhs.b);
    }
    Complex operator-(const Complex& rhs) const {
        return Complex(a - rhs.a, b - rhs.b);
    }
};
const int sqsiz = 200005;
int p[sqsiz], psiz = 0;
Complex sumf[sqsiz];
bool flag[sqsiz];
void pre(int n) {
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++psiz] = i;
            sumf[psiz] = sumf[psiz - 1] + Complex(i);
        }
        for(int j = 1; j <= psiz && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j] == 0)
                break;
        }
    }
}
Complex G[2][sqsiz];
Int64 sqr, n;
Complex& getG(Int64 x) {
    if(x <= sqr)
        return G[0][x];
    return G[1][n / x];
}
Int64 q[sqsiz * 2];
int main() {
    scanf("%lld", &n);
    sqr = sqrt(n);
    pre(sqr);
    int m = 0;
    Int64 dv = 1;
    while(dv <= n) {
        Int64 val = n / dv;
        getG(val) = Complex(
            ((val >> 2) + ((val & 3) >= 1) - 1),
            ((val >> 2) + ((val & 3) >= 3)));
        q[++m] = val;
        dv = n / val + 1;
    }
    for(int i = 2; i <= psiz; ++i) {
        Int64 cp = p[i], cp2 = cp * cp, mask = cp & 3;
        for(int j = 1; j <= m && cp2 <= q[j]; ++j) {
            Int64 x = q[j];
            Complex& val = getG(x);
            Complex delta = getG(x / cp) - sumf[i - 1];
            if(mask == 1)
                val.a -= delta.a, val.b -= delta.b;
            else
                val.a -= delta.b, val.b -= delta.a;
        }
    }
    printf("%d\n", getG(n).a);
    return 0;
}
