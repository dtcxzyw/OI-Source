#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
namespace IO {
    void init() {
        assert(setvbuf(stdin, 0, _IONBF, 0) == 0);
        assert(setvbuf(stdout, 0, _IONBF, 0) == 0);
    }
    const int size = 1 << 24;
    char in[size];
    char getc() {
        static char *S = in, *T = in;
        if(S == T)
            S = in, T = in + fread(in, 1, size, stdin);
        return S == T ? EOF : *S++;
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
const int size = 100005;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int crt, msiz, tsiz, siz[size];
bool vis[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int csiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            csiz = std::max(csiz, siz[v]);
        }
    }
    csiz = std::max(csiz, tsiz - siz[u]);
    if(csiz < msiz)
        msiz = csiz, crt = u;
}
int getRoot(int u, int usiz) {
    msiz = 1 << 30, tsiz = usiz;
    getRootImpl(u, 0);
    return crt;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int modu = 2003, modv = 1999, fac = 131;
struct HashValue {
    int HA, HB;
    HashValue() {}
    explicit HashValue(int ch)
        : HA(ch % modu), HB(ch % modv) {}
    bool operator==(HashValue& rhs) const {
        return HA == rhs.HA && HB == rhs.HB;
    }
    HashValue extend(int ch) const {
        HashValue res;
        res.HA = (HA * fac + ch) % modu;
        res.HB = (HB * fac + ch) % modv;
        return res;
    }
};
struct HashTable {
    HashValue A[modu];
    void reset() {
        memset(A, 0, sizeof(A));
    }
    int find(HashValue val) {
        int ha = val.HA, hb = 1 + val.HB, cur = ha;
        while(true) {
            if(A[cur] == val)
                return cur;
            if(A[cur].HA == 0 && A[cur].HB == 0)
                return -1;
            cur += hb;
            if(cur >= modu)
                cur -= modu;
        }
    }
    int insert(HashValue val) {
        int ha = val.HA, hb = 1 + val.HB, cur = ha;
        while(true) {
            if(A[cur].HA == 0 && A[cur].HB == 0) {
                A[cur] = val;
                return cur;
            }
            cur += hb;
            if(cur >= modu)
                cur -= modu;
        }
    }
} HA, HB, HC, HD;
Int64 ans;
int m, end;
char S[size], P[size];
void reset(int n) {
    cnt = 0;
    memset(last + 1, 0, sizeof(int) * n);
    memset(vis + 1, 0, sizeof(bool) * n);
    HA.reset();
    HB.reset();
    HC.reset();
    HD.reset();
}
int posA[modu], posB[modu];
HashValue remapA[modu], remapB[modu];
int A[size], LA, B[size], LB, C[size], LC, D[size], LD;
void DFSA(int u, int p, int len, HashValue val) {
    {
        int id = HB.find(val);
        if(id != -1) {
            val = remapA[id];
            len -= m;
        } else if(len > end)
            return;
        id = HA.find(val);
        if(id != -1) {
            id = posA[id];
            ++C[id];
            LC = std::max(LC, id);
        }
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v])
            DFSA(v, u, len + 1, val.extend(S[v]));
    }
}
void DFSB(int u, int p, int len, HashValue val) {
    {
        int id = HD.find(val);
        if(id != -1) {
            val = remapB[id];
            len -= m;
        } else if(len > end)
            return;
        id = HC.find(val);
        if(id != -1) {
            id = posB[id];
            ++D[id];
            LD = std::max(LD, id);
        }
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v])
            DFSB(v, u, len + 1, val.extend(S[v]));
    }
}
bool flag = false;
void solve(int u) {
    LA = LB = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            LC = LD = 0;
            DFSA(v, u, 2,
                 HashValue(S[u]).extend(S[v]));
            DFSB(v, u, 1, HashValue(S[v]));
            for(int j = 1; j <= LC; ++j) {
                int rev = m == j ? m : m - j;
                ans += asInt64(C[j]) * B[rev];
            }
            if(flag) {
                for(int j = 1; j <= LD; ++j) {
                    int rev = m == j ? m : m - j;
                    ans += asInt64(D[j]) * A[rev];
                }
            }
            for(int j = 1; j <= LC; ++j) {
                A[j] += C[j];
                C[j] = 0;
            }
            LA = std::max(LA, LC);
            for(int j = 1; j <= LD; ++j) {
                B[j] += D[j];
                D[j] = 0;
            }
            LB = std::max(LB, LD);
        }
    }
    if(flag)
        ans += A[m];
    if(S[u] == P[m])
        ans += B[m - 1];
    memset(A + 1, 0, sizeof(int) * LA);
    memset(B + 1, 0, sizeof(int) * LB);
}
void divide(int u) {
    vis[u] = true;
    solve(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int nrt = getRoot(v, siz[v]);
            divide(nrt);
        }
    }
}
HashValue tmp[size];
Int64 foo() {
    int n = read();
    reset(n);
    m = read();
    end = 2 * m;
    for(int i = 1; i <= n; ++i) {
        int c;
        do
            c = IO::getc();
        while(c < 'A' || c > 'Z');
        S[i] = c;
    }
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    for(int i = 1; i <= m; ++i) {
        int c;
        do
            c = IO::getc();
        while(c < 'A' || c > 'Z');
        P[i] = c;
    }
    flag = false;
    for(int i = 1; i <= m; ++i)
        if(P[i] != P[m + 1 - i]) {
            flag = true;
            break;
        }
    {
        int bu = 1, vu = 0, bv = 1, vv = 0;
        for(int i = m; i >= 1; --i) {
            vu = (vu + bu * P[i]) % modu;
            bu = bu * fac % modu;
            vv = (vv + bv * P[i]) % modv;
            bv = bv * fac % modv;
            HashValue val;
            val.HA = vu;
            val.HB = vv;
            posA[HA.insert(val)] = m + 1 - i;
            tmp[i] = val;
        }
        for(int i = m; i >= 1; --i) {
            vu = (vu + bu * P[i]) % modu;
            bu = bu * fac % modu;
            vv = (vv + bv * P[i]) % modv;
            bv = bv * fac % modv;
            HashValue val;
            val.HA = vu;
            val.HB = vv;
            remapA[HB.insert(val)] = tmp[i];
        }
    }
    {
        int bu = 1, vu = 0, bv = 1, vv = 0;
        for(int i = 1; i <= m; ++i) {
            vu = (vu + bu * P[i]) % modu;
            bu = bu * fac % modu;
            vv = (vv + bv * P[i]) % modv;
            bv = bv * fac % modv;
            HashValue val;
            val.HA = vu;
            val.HB = vv;
            posB[HC.insert(val)] = i;
            tmp[i] = val;
        }
        for(int i = 1; i <= m; ++i) {
            vu = (vu + bu * P[i]) % modu;
            bu = bu * fac % modu;
            vv = (vv + bv * P[i]) % modv;
            bv = bv * fac % modv;
            HashValue val;
            val.HA = vu;
            val.HB = vv;
            remapB[HD.insert(val)] = tmp[i];
        }
    }
    ans = 0;
    divide(getRoot(1, n));
    return flag ? ans : ans * 2;
}
int main() {
    IO::init();
    int t = read();
    for(int i = 0; i < t; ++i)
        printf("%llu\n", foo());
    return 0;
}
