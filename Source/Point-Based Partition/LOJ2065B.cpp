// TOFIX
#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 1000005;
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
typedef unsigned long long Int64;
#define asInt64 static_cast<Int64>
const int modu = 2000003, modv = 1999993, fac = 131;
struct HashTable {
    Int64 A[modu];
    void reset() {
        memset(A, 0, sizeof(A));
    }
    int find(Int64 val) {
        int ha = val % modu, hb = 1 + val % modv,
            cur = ha;
        while(true) {
            if(A[cur] == val)
                return cur;
            if(A[cur] == 0)
                return -1;
            cur += hb;
            if(cur >= modu)
                cur -= modu;
        }
    }
    int insert(Int64 val) {
        int ha = val % modu, hb = 1 + val % modv,
            cur = ha;
        while(true) {
            if(A[cur] == 0) {
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
int m;
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
Int64 remapA[modu], remapB[modu];
int A[size], LA, B[size], LB, C[size], LC, D[size], LD;
void DFS(int u, int p, Int64 valA, Int64 valB) {
    {
        int id = HB.find(valA);
        if(id != -1)
            valA = remapA[id];
        id = HA.find(valA);
        if(id != -1) {
            id = posA[id];
            ++C[id];
            LC = std::max(LC, id);
        }
    }
    {
        int id = HD.find(valB);
        if(id != -1)
            valB = remapB[id];
        id = HC.find(valB);
        if(id != -1) {
            id = posB[id];
            ++D[id];
            LD = std::max(LD, id);
        }
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v])
            DFS(v, u, valA * fac + S[v],
                valB * fac + S[v]);
    }
}
void solve(int u) {
    LA = LB = 0;
    B[0] = 1;
    if(S[u] == P[m])
        A[1] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            LC = LD = 0;
            DFS(v, u, asInt64(S[u]) * fac + S[v],
                S[v]);
            for(int j = 1; j <= LC; ++j)
                ans += asInt64(C[j]) * B[m - j];
            for(int j = 1; j <= LD; ++j)
                ans += asInt64(D[j]) * A[m - j];
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
    memset(A + 1, 0, sizeof(int) * LA);
    memset(B + 1, 0, sizeof(int) * LB);
    printf("%d %llu\n", u, ans);
    throw;
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
Int64 tmp[size];
Int64 foo() {
    int n = read();
    reset(n);
    m = read();
    scanf("%s", S + 1);
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    scanf("%s", P + 1);
    {
        Int64 base = 1, cur = 0;
        for(int i = m; i >= 1; --i) {
            cur += base * P[i];
            base *= fac;
            posA[HA.insert(cur)] = m + 1 - i;
            tmp[i] = cur;
        }
        for(int i = m; i >= 1; --i) {
            cur += base * P[i];
            base *= fac;
            remapA[HB.insert(cur)] = tmp[i];
        }
    }
    {
        Int64 base = 1, cur = 0;
        for(int i = 1; i <= m; ++i) {
            cur += base * P[i];
            base *= fac;
            posB[HC.insert(cur)] = i;
            tmp[i] = cur;
        }
        for(int i = 1; i <= m; ++i) {
            cur += base * P[i];
            base *= fac;
            remapB[HD.insert(cur)] = tmp[i];
        }
    }
    ans = 0;
    divide(getRoot(1, n));
    return ans;
}
int main() {
    int t = read();
    for(int i = 0; i < t; ++i)
        printf("%llu\n", foo());
    return 0;
}
