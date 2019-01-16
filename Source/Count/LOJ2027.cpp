#include <cstdio>
#include <cstring>
#include <vector>
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
const int size = 17, mod = 1000000007;
typedef long long Int64;
Int64 inv(Int64 a) {
    Int64 res = 1;
    int k = mod - 2;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int n;
int count(int (&A)[size][size], bool flag) {
    for(int i = 1; i <= n; ++i) {
        int x = 0;
        for(int j = i; j <= n; ++j)
            if(A[j][i]) {
                x = j;
                break;
            }
        if(x == 0)
            return 0;
        if(x != i) {
            for(int j = i; j <= n; ++j)
                std::swap(A[i][j], A[x][j]);
            flag ^= 1;
        }
        Int64 invX = inv(A[i][i]);
        for(int j = i + 1; j <= n; ++j) {
            Int64 fac = invX * A[j][i] % mod;
            for(int k = i; k <= n; ++k)
                A[j][k] =
                    (A[j][k] - fac * A[i][k]) % mod;
        }
    }
    Int64 res = 1;
    for(int i = 1; i <= n; ++i)
        res = res * A[i][i] % mod;
    return flag ? -res : res;
}
typedef std::vector<std::pair<int, int> > Path;
Path E[size];
struct Mat {
    int A[size][size];
};
Int64 DFS(int cur, Mat mat, bool flag) {
    if(cur == 0)
        return count(mat.A, flag);
    else {
        Int64 res = DFS(cur - 1, mat, flag);
        Path& p = E[cur];
        for(int i = 0; i < p.size(); ++i) {
            int u = p[i].first, v = p[i].second;
            ++mat.A[u][u], --mat.A[u][v];
            ++mat.A[v][v], --mat.A[v][u];
        }
        return res + DFS(cur - 1, mat, flag ^ 1);
    }
}
int main() {
    n = read() - 1;
    for(int i = 1; i <= n; ++i) {
        int m = read();
        E[i].resize(m);
        for(int j = 0; j < m; ++j)
            E[i][j].first = read(),
            E[i][j].second = read();
    }
    Mat emat;
    memset(&emat, 0, sizeof(emat));
    printf("%lld\n",
           (DFS(n, emat, n & 1) % mod + mod) % mod);
    return 0;
}
