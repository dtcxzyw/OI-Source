#include <algorithm>
#include <cstdio>
#include <cstring>
namespace IO {
    const int size = 1 << 24;
    char buf[size], *S = buf;
    void init() {
        fread(buf, 1, size, stdin);
    }
    char getc() {
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
const int size = 1000005;
namespace HashTable {
    const int modu = 4000037, modv = 3999971;
    std::pair<int, int> LUT[modu];
    int A[size], crk;
    void clear() {
        for(int i = 1; i <= crk; ++i)
            LUT[A[i]].first = 0;
        crk = 0;
    }
    int load(int key) {
        int hu = key % modu, hv = 1 + key % modv,
            cur = hu;
        while(true) {
            if(LUT[cur].first == 0) {
                LUT[cur].first = key;
                LUT[cur].second = ++crk;
                A[crk] = cur;
            }
            if(LUT[cur].first == key)
                return LUT[cur].second;
            cur += hv;
            if(cur >= modu)
                cur -= modu;
        }
    }
}
struct Info {
    int u, v, e;
} A[size];
int fa[size], rk[size];
int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u != v) {
        if(rk[u] < rk[v])
            fa[u] = v;
        else {
            fa[v] = u;
            if(rk[u] == rk[v])
                ++rk[u];
        }
    }
}
bool foo() {
    HashTable::clear();
    int n = read();
    for(int i = 1; i <= n; ++i) {
        A[i].u = HashTable::load(read());
        A[i].v = HashTable::load(read());
        A[i].e = read();
    }
    int siz = HashTable::crk;
    memset(fa + 1, 0, sizeof(int) * siz);
    for(int i = 1; i <= n; ++i)
        if(A[i].e)
            merge(A[i].u, A[i].v);
        else if(find(A[i].u) == find(A[i].v))
            return false;
    for(int i = 1; i <= n; ++i)
        if(A[i].e == 0 && find(A[i].u) == find(A[i].v))
            return false;
    return true;
}
int main() {
    IO::init();
    int t = read();
    for(int i = 0; i < t; ++i)
        puts(foo() ? "YES" : "NO");
    return 0;
}
