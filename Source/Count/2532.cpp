#include <cstdio>
const int mod = 1000000;
class Integer {
private:
    int siz, A[60];

public:
    Integer(int x) : siz(1) {
        A[1] = x;
        for(int i = 2; i < 60; ++i)
            A[i] = 0;
    }
    void operator*=(const int k) {
        for(int i = 1; i <= siz; ++i)
            A[i] *= k;
        for(int i = 1; i <= siz; ++i) {
            A[i + 1] += A[i] / mod;
            A[i] %= mod;
        }
        if(A[siz + 1])
            ++siz;
    }
    void operator/=(const int k) {
        for(int i = siz; i >= 1; --i) {
            A[i - 1] += A[i] % k * mod;
            A[i] /= k;
        }
        if(!A[siz])
            --siz;
    }
    void print() const {
        printf("%d", A[siz]);
        for(int i = siz - 1; i >= 1; --i)
            printf("%06d", A[i]);
        putchar('\n');
    }
};
int main() {
    int n;
    scanf("%d", &n);
    Integer cur(1);
    for(int i = 1; i <= n; ++i) {
        cur *= 4 * i - 2;
        cur /= i + 1;
    }
    cur.print();
    return 0;
}
