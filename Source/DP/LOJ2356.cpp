#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long Int64;
const int maxk = 60, mod = 65521;
struct Mat {
    Int64 A[maxk][maxk];
    int n, m;
    Mat(int n, int m) : n(n), m(m) {
        memset(A, 0, sizeof(A));
    }
    Int64* operator[](int id) {
        return A[id];
    }
    const Int64* operator[](int id) const {
        return A[id];
    }
    Mat operator*(const Mat& rhs) const {
        Mat res(n, rhs.m);
        for(int i = 0; i < n; ++i)
            for(int k = 0; k < m; ++k)
                for(int j = 0; j < rhs.m; ++j)
                    res[i][j] += A[i][k] * rhs[k][j];
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < rhs.m; ++j)
                res[i][j] %= mod;
        return res;
    }
};
int B[7];
int find(int x) {
    return B[x] == x ? x : B[x] = find(B[x]);
}
bool merge(int u, int v) {
    u = find(u), v = find(v);
    if(u != v) {
        B[u] = v;
        return true;
    }
    return false;
}
int k;
struct State {
    int A[7], code;
    State() : code(0) {
        memset(A, 0, sizeof(A));
    }
    int move(int s, bool check) const {
        int rt[8] = {};
        for(int i = 1; i <= k; ++i) {
            int& x = rt[A[i]];
            if(!x)
                x = i;
            B[i] = x;
        }
        B[k + 1] = k + 1;
        for(int i = 1; i <= k; ++i)
            if(s & (1 << (k - i)))
                if(!merge(i, k + 1))
                    return -1;
        if(check) {
            bool flag = false;
            for(int i = 2; i <= k + 1; ++i)
                if(find(1) == find(i)) {
                    flag = true;
                    break;
                }
            if(!flag)
                return -1;
        }
        int id[8] = {}, cid = 0, dc = 0;
        for(int i = 2; i <= k + 1; ++i) {
            int& x = id[find(i)];
            if(!x)
                x = ++cid;
            dc = dc * 10 + x;
        }
        return dc;
    }
} S[maxk];
int scnt = 0;
void DFS(int u, int c, State s) {
    if(u == k + 1)
        S[scnt++] = s;
    else {
        for(int i = 1; i <= c + 1; ++i) {
            State cur = s;
            cur.A[u] = i;
            cur.code = s.code * 10 + i;
            DFS(u + 1, std::max(i, c), cur);
        }
    }
}
int getId(int code) {
    int l = 0, r = scnt - 1;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(S[m].code == code)
            return m;
        if(S[m].code < code)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}
int main() {
    Int64 n;
    scanf("%d%lld", &k, &n);
    if(k > n)
        k = n;
    DFS(1, 0, State());
    int end = 1 << k;
    Mat move(scnt, scnt);
    for(int i = 0; i < end; ++i)
        for(int j = 0; j < scnt; ++j) {
            int dst = S[j].move(i, true);
            if(dst != -1)
                ++move[j][getId(dst)];
        }
    Mat res(1, scnt);
    res[0][scnt - 1] = 1;
    for(int i = 2; i <= k; ++i) {
        Mat cur(1, scnt);
        int cend = 1 << (i - 1);
        for(int j = 0; j < scnt; ++j)
            if(res[0][j]) {
                for(int x = 0; x < cend; ++x) {
                    int dst = S[j].move(x, false);
                    if(dst != -1) {
                        dst = getId(dst);
                        cur[0][dst] =
                            (cur[0][dst] + res[0][j]) %
                            mod;
                    }
                }
            }
        res = cur;
    }
    n -= k;
    while(n) {
        if(n & 1)
            res = res * move;
        n >>= 1, move = move * move;
    }
    printf("%lld\n", res[0][0]);
    return 0;
}
