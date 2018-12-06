#include <cstdio>
const int size = 3005, mod = 1000000007;
#define asInt64(x) static_cast<long long>(x)
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
char A[size][size];
struct Pair {
    int a, b;
    Pair() {}
    Pair(int a, int b) : a(a), b(b) {}
    Pair operator+(const Pair& rhs) const {
        return Pair(add(a, rhs.a), add(b, rhs.b));
    }
} count[size][size];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%s", A[i] + 1);
    {
        int cp = 2;
        while(A[1][cp] == '.') {
            count[1][cp] = Pair(1, 0);
            ++cp;
        }
    }
    {
        int cp = 2;
        while(A[cp][1] == '.') {
            count[cp][1] = Pair(0, 1);
            ++cp;
        }
    }
    for(int i = 2; i <= n; ++i)
        for(int j = 2; j <= m; ++j)
            if(A[i][j] == '.')
                count[i][j] =
                    count[i - 1][j] + count[i][j - 1];
    Pair a = count[n - 1][m], b = count[n][m - 1];
    int res =
        ((asInt64(a.a) * b.b - asInt64(a.b) * b.a) %
             mod +
         mod) %
        mod;
    printf("%d\n", res);
    return 0;
}
