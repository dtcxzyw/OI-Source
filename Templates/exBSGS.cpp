#include <cmath>
#include <cstdio>
#include <unordered_map>
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
Int64 powm(Int64 a, int k, Int64 p) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % p;
        k >>= 1, a = a * a % p;
    }
    return res;
}
typedef std::unordered_map<int, int> Hash;
typedef Hash::iterator IterT;
int foo(int a, int p, int b) {
    a %= p, b %= p;
    int A = 1, B = 0;
    while(true) {
        int d = gcd(a, p);
        if(d == 1)
            break;
        if(b % d) {
            if(a == b)
                return B;
            return -1;
        } else
            ++B, b /= d, p /= d,
                A = asInt64(A) * (a / d) % p;
    }
    Int64 cur = 1;
    for(int i = 0; i < B; ++i) {
        if(cur == b)
            return i;
        cur = cur * a % p;
    }
    int m = sqrt(p) + 1;
    cur = b;
    Hash hash;
    for(int i = 1; i <= m; ++i) {
        cur = cur * a % p;
        hash[cur] = i;
    }
    Int64 base = powm(a, m, p);
    cur = A;
    for(int i = 1; i <= m; ++i) {
        cur = cur * base % p;
        IterT it = hash.find(cur);
        if(it != hash.end())
            return i * m - it->second + B;
    }
    return -1;
}
int main() {
    int a, p, b;
    while(true) {
        scanf("%d%d%d", &a, &p, &b);
        if(a | p | b) {
            int res = foo(a, p, b);
            if(res >= 0)
                printf("%d\n", res);
            else
                puts("No Solution");
        } else
            break;
    }
    return 0;
}
