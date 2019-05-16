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
void Yes() {
    *IO::S++ = 'Y';
    *IO::S++ = 'e';
    *IO::S++ = 's';
    *IO::S++ = '\n';
}
void No() {
    *IO::S++ = 'N';
    *IO::S++ = 'o';
    *IO::S++ = '\n';
}
const int size = 100005;
struct Edge {
    int u, v;
} R[size * 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
struct Link {
    int to, nxt;
} E[size * 40];
int last[size << 2], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
void insert(int l, int r, int id, int nl, int nr,
            int ref) {
    if(nl <= l && r <= nr)
        addEdge(id, ref);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            insert(ls, nl, nr, ref);
        if(m < nr)
            insert(rs, nl, nr, ref);
    }
}
int fa[size], rk[size], rev[size];
std::pair<int, int> find(int x) {
    if(fa[x]) {
        std::pair<int, int> res = find(fa[x]);
        res.second ^= rev[x];
        return res;
    }
    return std::make_pair(x, 0);
}
int merge(int u, int v, int revf) {
    if(rk[u] < rk[v]) {
        fa[u] = v;
        rev[u] = revf;
        return u;
    } else {
        fa[v] = u;
        rev[v] = revf;
        if(rk[u] == rk[v]) {
            ++rk[u];
            return -v;
        }
        return v;
    }
}
int sta[size * 2], top = 0;
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
            fa[u] = rev[u] = 0;
        }
    }
};
void solve(int l, int r, int id) {
    Backup bak;
    for(int i = last[id]; i; i = E[i].nxt) {
        const Edge& e = R[E[i].to];
        std::pair<int, int> fu = find(e.u),
                            fv = find(e.v);
        bool rev = 1 ^ fu.second ^ fv.second;
        if(fu.first != fv.first)
            sta[++top] =
                merge(fu.first, fv.first, rev);
        else if(rev) {
            for(int j = l; j <= r; ++j)
                No();
            return;
        }
    }
    if(l == r)
        Yes();
    else {
        int m = (l + r) >> 1;
        solve(ls);
        solve(rs);
    }
}
int main() {
    IO::init();
    read();
    int m = read();
    int T = read();
    for(int i = 1; i <= m; ++i) {
        R[i].u = read();
        R[i].v = read();
        int s = read();
        int t = read();
        if(s < t)
            insert(1, T, 1, s + 1, t, i);
    }
    solve(1, T, 1);
    IO::uninit();
    return 0;
}
