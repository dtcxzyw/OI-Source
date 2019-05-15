#include <algorithm>
#include <cstdio>
namespace IO {
    char in[1 << 23];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 21], *S = out;
    void uninit() {
        fwrite(out, S - out, 1, stdout);
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
const int size = 500005;
struct Edge {
    int u, v;
} R[size];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
struct Link {
    int to, nxt;
} E[size * 20];
int last[size << 2], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
void insert(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        addEdge(id, nl);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            insert(ls, nl, nr);
        if(m < nr)
            insert(rs, nl, nr);
    }
}
int fa[size], rk[size];
int find(int x) {
    return fa[x] ? find(fa[x]) : x;
}
int merge(int u, int v) {
    if(rk[u] < rk[v]) {
        fa[u] = v;
        return u;
    } else {
        fa[v] = u;
        if(rk[u] == rk[v]) {
            ++rk[u];
            return -v;
        }
        return v;
    }
}
int sta[size], top = 0;
class Backup {
private:
    int htop;

public:
    Backup() : htop(top) {}
    ~Backup() {
        while(top != htop) {
            int u = sta[top--];
            if(u < 0) {
                u = -u;
                --rk[fa[u]];
            }
            fa[u] = 0;
        }
    }
};
bool que[size];
void solve(int l, int r, int id) {
    Backup bak;
    for(int i = last[id]; i; i = E[i].nxt) {
        const Edge& e = R[E[i].to];
        int fu = find(e.u), fv = find(e.v);
        if(fu != fv)
            sta[++top] = merge(fu, fv);
    }
    if(l == r) {
        if(que[l]) {
            const Edge& e = R[l];
            *(IO::S++) =
                (find(e.u) == find(e.v) ? 'Y' : 'N');
            *(IO::S++) = '\n';
        }
    } else {
        int m = (l + r) >> 1;
        solve(ls);
        solve(rs);
    }
}
const int modu = 1000003, modv = 999983;
typedef long long Int64;
int LUT[modu];
Int64 key[modu];
int load(const Edge& e) {
    Int64 k = static_cast<Int64>(e.u) << 30 | e.v;
    Int64 mu = k % modu, mv = 1 + k % modv, cur = mu;
    while(true) {
        if(key[cur] == 0)
            key[cur] = k;
        if(key[cur] == k)
            return cur;
        cur += mv;
        if(cur >= modu)
            cur -= modu;
    }
}
int main() {
    IO::init();
    read();
    int m = read();
    for(int i = 1; i <= m; ++i) {
        int op = read();
        Edge e;
        e.u = read(), e.v = read();
        if(e.u < e.v)
            std::swap(e.u, e.v);
        R[i] = e;
        switch(op) {
            case 0: {
                int id = load(e);
                LUT[id] = i;
            } break;
            case 1: {
                int id = load(e);
                insert(1, m, 1, LUT[id], i - 1);
                LUT[id] = 0;
            } break;
            case 2: {
                que[i] = true;
            } break;
        }
    }
    for(int i = 0; i < modv; ++i)
        if(LUT[i])
            insert(1, m, 1, LUT[i], m);
    solve(1, m, 1);
    IO::uninit();
    return 0;
}
