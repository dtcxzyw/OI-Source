#include <climits>
#include <cstdio>
#include <cstring>
const int ls = 105, size = 55, mod = 1000000007;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
struct Node {
    int nxt[26], fail;
    bool flag;
} T[ls];
int icnt = 0;
void insert() {
    int p = 0, c;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        int& v = T[p].nxt[c - 'a'];
        if(v == 0)
            v = ++icnt;
        p = v;
        c = getchar();
    }
    T[p].flag = true;
}
int q[ls];
void cook() {
    int b = 0, e = 0;
    for(int i = 0; i < 26; ++i)
        if(T[0].nxt[i])
            q[e++] = T[0].nxt[i];
    while(b != e) {
        int u = q[b++];
        for(int i = 0; i < 26; ++i) {
            int& v = T[u].nxt[i];
            if(v) {
                T[v].fail = T[T[u].fail].nxt[i];
                T[v].flag |= T[T[v].fail].flag;
                q[e++] = v;
            } else
                v = T[T[u].fail].nxt[i];
        }
    }
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
const Int64 end =
    LLONG_MAX - asInt64(mod - 1) * (mod - 1);
struct Mat {
    int A[205][205], n, m;
    Mat(int n, int m, bool init = true) : n(n), m(m) {
        if(init)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j)
                    A[i][j] = 0;
    }
    int* operator[](int id) {
        return A[id];
    }
    const int* operator[](int id) const {
        return A[id];
    }
    Mat operator*(const Mat& rhs) const {
        Mat res(n, rhs.m, false);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < rhs.m; ++j) {
                Int64 sum = 0;
                for(int k = 0; k < m; ++k) {
                    sum +=
                        asInt64(A[i][k]) * rhs[k][j];
                    if(sum > end)
                        sum %= mod;
                }
                res[i][j] = sum % mod;
            }
        return res;
    }
};
int dp[ls][ls], len[size], jmp[size][ls], siz;
char A[size][ls];
int jump(int p, int i) {
    for(int k = 0; k < len[i]; ++k) {
        int c = A[i][k] - 'a';
        p = T[p].nxt[c];
        if(T[p].flag)
            return siz;
    }
    return p;
}
int main() {
    int n, m, l;
    scanf("%d%d%d", &n, &m, &l);
    for(int i = 1; i <= n; ++i) {
        scanf("%s", A[i]);
        len[i] = strlen(A[i]);
    }
    while(m--)
        insert();
    cook();
    siz = icnt + 1;
    if(l <= 100) {
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= icnt; ++j)
                if(!T[j].flag) {
                    int p = jump(j, i);
                    jmp[i][j] = p;
                } else
                    jmp[i][j] = siz;
        }
        dp[0][0] = 1;
        for(int i = 1; i <= l; ++i) {
            for(int j = 1; j <= n; ++j) {
                int src = i - len[j];
                if(src < 0)
                    continue;
                for(int k = 0; k <= icnt; ++k) {
                    int dst = jmp[j][k];
                    dp[i][dst] =
                        add(dp[i][dst], dp[src][k]);
                }
            }
        }
        int res = 0;
        for(int i = 0; i <= icnt; ++i)
            res = add(res, dp[l][i]);
        printf("%d\n", res);
    } else {
        int msiz = 2 * siz;
        Mat res(1, msiz), trans(msiz, msiz);
        res[0][0] = 1;
        for(int i = 0; i <= icnt; ++i)
            trans[i + siz][i] = 1;
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= icnt; ++j)
                if(!T[j].flag) {
                    int p = jump(j, i);
                    if(p != siz) {
                        if(len[i] == 1)
                            ++trans[j][p];
                        else
                            ++trans[j][p + siz];
                    }
                }
        }
        while(l) {
            if(l & 1)
                res = res * trans;
            l >>= 1, trans = trans * trans;
        }
        int ans = 0;
        for(int i = 0; i <= icnt; ++i)
            ans = add(ans, res[0][i]);
        printf("%d\n", ans);
    }
    return 0;
}
