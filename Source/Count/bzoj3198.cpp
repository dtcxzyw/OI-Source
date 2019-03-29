#include <cstdio>
#include <cstring>
#include <vector>
namespace IO {
    char buf[1 << 23];
    void init() {
        fread(buf, 1, sizeof(buf), stdin);
    }
    char getc() {
        static char* S = buf;
        return *S++;
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
typedef unsigned long long HashT;
typedef long long Int64;
namespace HashTable {
    const int modu = 4000037, modv = 3999971;
    HashT val[modu];
    int cnt[modu];
    void insert(HashT h) {
        int ha = h % modu, hb = h % modv + 1, cur = ha;
        while(true) {
            if(val[cur] == 0)
                val[cur] = h;
            if(val[cur] == h) {
                ++cnt[cur];
                return;
            }
            cur += hb;
            if(cur >= modu)
                cur -= modu;
        }
    }
    int find(HashT h) {
        int ha = h % modu, hb = h % modv + 1, cur = ha;
        while(true) {
            if(val[cur] == 0)
                return 0;
            if(val[cur] == h)
                return cnt[cur];
            cur += hb;
            if(cur >= modu)
                cur -= modu;
        }
    }
    void reset() {
        memset(cnt, 0, sizeof(cnt));
        memset(val, 0, sizeof(val));
    }
}
const HashT fac = 12351246239, magic = 235146193462;
int K, tmp[7];
struct Edge {
    HashT to;
    int nxt;
} E[size * 64];
int last[size][7], cnt = 0;
void addEdge(int u, int b, HashT v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u][b];
    last[u][b] = cnt;
}
void DFS(int n, int id, int bcnt, HashT cur) {
    if(bcnt + n < K)
        return;
    if(n == 0)
        addEdge(id, bcnt, cur);
    else {
        DFS(n - 1, id, bcnt, cur * fac + magic);
        DFS(n - 1, id, bcnt + 1, cur * fac + tmp[n]);
    }
}
Int64 calc(int k, int n) {
    HashTable::reset();
    Int64 res = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = last[i][k]; j; j = E[j].nxt)
            res += HashTable::find(E[j].to);
        for(int j = last[i][k]; j; j = E[j].nxt)
            HashTable::insert(E[j].to);
    }
    return res;
}
int C[7][7];
int main() {
    IO::init();
    int n = read();
    K = read();
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= 6; ++j)
            tmp[j] = read();
        DFS(6, i, 0, 0);
    }
    C[0][0] = 1;
    for(int i = 1; i <= 6; ++i) {
        C[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    Int64 res = 0;
    for(int i = K; i <= 6; ++i) {
        Int64 val = C[i][K] * calc(i, n);
        if((i - K) & 1)
            res -= val;
        else
            res += val;
    }
    printf("%lld\n", res);
    return 0;
}
