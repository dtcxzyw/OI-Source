#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
namespace IO {
    char in[1 << 25];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 23], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 read() {
    Int64 res = 0, c;
    bool flag = false;
    do {
        c = IO::getc();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return flag ? -res : res;
}
void writeImpl(Int64 x) {
    if(x >= 10)
        writeImpl(x / 10);
    IO::putc('0' + x % 10);
}
void write(Int64 x) {
    if(x < 0)
        IO::putc('-'), x = -x;
    writeImpl(x);
    IO::putc('\n');
}
const int size = 500005, mx = 1000000;
struct Edge {
    int to, nxt, op, id;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v, int op, int id) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u],
    E[cnt].op = op, E[cnt].id = id;
    last[u] = cnt;
}
const Int64 inf = 1LL << 60;
struct RemovableHeap {
    std::priority_queue<Int64, std::vector<Int64>,
                        std::greater<Int64> >
        A, B;
    void push(Int64 x) {
        A.push(x);
    }
    void pop(Int64 x) {
        B.push(x);
    }
    Int64 top() {
        while(A.size() && B.size() &&
              A.top() == B.top())
            A.pop(), B.pop();
        return A.size() ? A.top() : inf;
    }
} Heap[size];
struct Node {
    Int64 minc;
    int minx, maxx;
    Int64 eval(int x0) const {
        Int64 delta = std::max(
            0, std::max(minx - x0, x0 - maxx));
        return delta * delta + minc;
    }
} T[size * 4];
int X[size], Y[size];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void init(int l, int r, int id) {
    T[id].minc = inf, T[id].minx = 1 << 30,
    T[id].maxx = -(1 << 30);
    if(l != r) {
        int m = (l + r) >> 1;
        init(ls);
        init(rs);
    }
}
void update(int id) {
    T[id].minc =
        std::min(T[id << 1].minc, T[id << 1 | 1].minc);
    T[id].minx =
        std::min(T[id << 1].minx, T[id << 1 | 1].minx);
    T[id].maxx =
        std::max(T[id << 1].maxx, T[id << 1 | 1].maxx);
}
void insert(int l, int r, int id, int x, Int64 c0) {
    if(l == r) {
        Heap[l].push(c0);
        T[id].minx = T[id].maxx = Y[l];
        T[id].minc = Heap[l].top();
    } else {
        int m = (l + r) >> 1;
        if(x <= m)
            insert(ls, x, c0);
        else
            insert(rs, x, c0);
        update(id);
    }
}
void erase(int l, int r, int id, int x, Int64 c0) {
    if(l == r) {
        Heap[l].pop(c0);
        T[id].minc = Heap[l].top();
        if(T[id].minc == inf)
            T[id].minx = 1 << 30,
            T[id].maxx = -(1 << 30);
    } else {
        int m = (l + r) >> 1;
        if(x <= m)
            erase(ls, x, c0);
        else
            erase(rs, x, c0);
        update(id);
    }
}
Int64 cres;
void queryImpl(int l, int r, int id, int x0,
               Int64 eval) {
    if(eval >= cres)
        return;
    if(l == r)
        cres = eval;
    else {
        int m = (l + r) >> 1;
        Int64 lv = T[id << 1].eval(x0),
              rv = T[id << 1 | 1].eval(x0);
        if(lv < rv) {
            queryImpl(ls, x0, lv);
            queryImpl(rs, x0, rv);
        } else {
            queryImpl(rs, x0, rv);
            queryImpl(ls, x0, lv);
        }
    }
}
Int64 query(int siz, int x0) {
    cres = inf;
    queryImpl(1, siz, 1, x0, T[1].eval(x0));
    return cres;
}
Int64 ans[size], C[size];
std::vector<std::pair<int, int> > Q[size];
int siz;
void modify(int op, int id) {
    if(op)
        erase(1, siz, 1, X[id], C[id]);
    else
        insert(1, siz, 1, X[id], C[id]);
}
void DFS(int u) {
    for(int i = 0; i < Q[u].size(); ++i) {
        int x0 = Q[u][i].first;
        int id = Q[u][i].second;
        ans[id] = query(siz, x0);
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        modify(E[i].op, E[i].id);
        DFS(v);
        modify(E[i].op ^ 1, E[i].id);
    }
}
int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    IO::init();
    int n = read();
    int m = read();
    Int64 c0 = read();
    int pcnt = 0;
    Y[++pcnt] = 0;
    for(int i = 1; i < n; ++i) {
        int op = read();
        int p = read();
        int id = read();
        if(op == 0) {
            int x = read();
            read();
            read();
            Int64 c = read();
            C[id] = c;
            X[id] = x;
            Y[++pcnt] = x;
        }
        addEdge(p, i, op, id);
    }
    std::sort(Y + 1, Y + pcnt + 1);
    siz = std::unique(Y + 1, Y + pcnt + 1) - (Y + 1);
    for(int i = 0; i < n; ++i)
        X[i] = std::lower_bound(Y + 1, Y + siz + 1,
                                X[i]) -
            Y;
    init(1, siz, 1);
    insert(1, siz, 1, X[0], c0);
    for(int i = 1; i <= m; ++i) {
        int s = read();
        int x0 = read();
        Q[s].push_back(std::make_pair(x0, i));
    }
    DFS(0);
    for(int i = 1; i <= m; ++i)
        write(ans[i]);
    IO::uninit();
    return 0;
}
