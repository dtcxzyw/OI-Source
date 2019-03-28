#include <algorithm>
#include <cstdio>
const int size = 90, mod = 2009;
struct Mat {
    int A[size][size], n, m;
    Mat(int n, int m) : n(n), m(m) {
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                A[i][j] = 0;
    }
    Mat operator*(const Mat& rhs) const {
        Mat res(n, rhs.m);
        for(int i = 0; i < n; ++i)
            for(int k = 0; k < m; ++k) {
                int val = A[i][k];
                if(val == 0)
                    continue;
                for(int j = 0; j < rhs.m; ++j)
                    res.A[i][j] += val * rhs.A[k][j];
            }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                res.A[i][j] %= mod;
        return res;
    }
};
char buf[15][15];
int maxt[15], id[15][15];
int main() {
    int n, T;
    scanf("%d%d", &n, &T);
    for(int i = 0; i < n; ++i) {
        scanf("%s", buf[i]);
        for(int j = 0; j < n; ++j) {
            int t = buf[i][j] - '0';
            maxt[j] = std::max(maxt[j], t);
        }
    }
    int ncnt = n;
    for(int i = 0; i < n; ++i) {
        id[i][0] = i;
        for(int j = 1; j < maxt[i]; ++j)
            id[i][j] = ncnt++;
    }
    Mat res(1, ncnt), trans(ncnt, ncnt);
    for(int i = 0; i < n; ++i) {
        for(int j = 1; j < maxt[i]; ++j) {
            int s = id[i][j], d = id[i][j - 1];
            trans.A[s][d] = 1;
        }
        for(int j = 0; j < n; ++j) {
            int t = buf[i][j] - '0';
            if(t)
                ++trans.A[i][id[j][t - 1]];
        }
    }
    res.A[0][0] = 1;
    while(T) {
        if(T & 1)
            res = res * trans;
        T >>= 1, trans = trans * trans;
    }
    printf("%d\n", res.A[0][n - 1]);
    return 0;
}
