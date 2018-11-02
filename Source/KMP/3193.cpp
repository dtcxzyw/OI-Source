#include <cstdio>
#include <cstring>
#include <limits>
typedef long long Int64;
Int64 end, mod;
struct Mat {
private:
    int n, m;
    Int64 A[20][20];

public:
    Mat(int n, int m) : n(n), m(m) {
        memset(A, 0, sizeof(A));
    }
    Int64* operator[](int idx) {
        return A[idx];
    }
    const Int64* operator[](int idx) const {
        return A[idx];
    }
    Mat operator*(const Mat& rhs) const {
        Mat res(n, rhs.m);
        for(int i = 0; i < n; ++i)
            for(int k = 0; k < m; ++k) {
                Int64 aik = A[i][k];
                for(int j = 0; j < rhs.m; ++j) {
                    Int64& dst = res[i][j];
                    dst += aik * rhs[k][j];
                    if(dst >= end)
                        dst %= mod;
                }
            }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < rhs.m; ++j)
                res[i][j] %= mod;
        return res;
    }
};
char buf[25];
int nxt[25];
void initTrans(Mat& trans, int m) {
    nxt[1] = 0;
    for(int i = 1, j = 0; i < m; ++i) {
        while(j && buf[i] != buf[j])
            j = nxt[j];
        if(buf[i] == buf[j])
            ++j;
        nxt[i + 1] = j;
    }
    for(int i = 0; i < m; ++i) {
        for(char c = '0'; c <= '9'; ++c) {
            int p = i;
            while(p && buf[p] != c)
                p = nxt[p];
            if(buf[p] == c)
                ++p;
            ++trans[i][p];
        }
    }
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j)
            trans[i][j] %= mod;
}
int main() {
    int n, m;
    scanf("%d%d%lld%s", &n, &m, &mod, buf);
    end = std::numeric_limits<Int64>::max() -
        (mod - 1) * (mod - 1);
    Mat res(1, m), trans(m, m);
    res[0][0] = 1;
    initTrans(trans, m);
    while(n) {
        if(n & 1)
            res = res * trans;
        n >>= 1, trans = trans * trans;
    }
    int ans = 0;
    for(int i = 0; i < m; ++i)
        ans = (ans + res[0][i]) % mod;
    printf("%d\n", ans);
    return 0;
}
