#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
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
const int size = 100005, maxS = 2 * size;
struct SAM {
    struct Node {
        int ch[26], link, len, cnt;
    } T[maxS];
    int last, siz;
    SAM() : last(1), siz(1) {}
    int extend(int ch) {
        int id = ++siz;
        T[id].len = T[last].len + 1;
        int p = last;
        while(p && !T[p].ch[ch]) {
            T[p].ch[ch] = id;
            p = T[p].link;
        }
        if(p) {
            int q = T[p].ch[ch];
            if(T[p].len + 1 == T[q].len)
                T[id].link = q;
            else {
                int cq = ++siz;
                T[cq] = T[q];
                T[cq].len = T[p].len + 1;
                while(p && T[p].ch[ch] == q) {
                    T[p].ch[ch] = cq;
                    p = T[p].link;
                }
                T[q].link = T[id].link = cq;
            }
        } else
            T[id].link = 1;
        last = id;
        return id;
    }
    int cnt[maxS], d[size], q[maxS];
    void topSort(int n) {
        for(int i = 1; i <= siz; ++i)
            ++d[T[i].len];
        for(int i = 1; i <= n; ++i)
            d[i] += d[i - 1];
        for(int i = 1; i <= siz; ++i)
            q[d[T[i].len]--] = i;
    }
    void cookA(int n) {
        topSort(n);
        for(int i = siz; i >= 1; --i) {
            int u = q[i], p = T[u].link;
            T[p].cnt += T[u].cnt;
        }
    }
    int fa[maxS][20];
    void cookB(int n) {
        cookA(n);
        for(int i = 1; i <= siz; ++i) {
            int u = q[i];
            fa[u][0] = T[u].link;
            for(int j = 1; j < 20; ++j)
                fa[u][j] = fa[fa[u][j - 1]][j - 1];
        }
    }
} sam;
struct Range {
    int l, r;
} R[size];
struct Query {
    std::string str;
    int a, b;
} Q[size];
int bid[size], qid[size];
bool cmp(int a, int b) {
    Query &qa = Q[a], &qb = Q[b];
    return bid[qa.a] == bid[qb.a] ?
        (bid[qa.a] & 1 ? qa.b > qb.b : qa.b < qb.b) :
        qa.a < qb.a;
}
int C[320][320], LC[320];
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 ans[size];
void fooA(int n, int m, int q, int k) {
    sam.cookA(n);
    int bsiz = m * sqrt(1.0 / q);
    for(int i = 0; i < m; ++i)
        bid[i] = i / bsiz;
    for(int i = 1; i <= q; ++i)
        qid[i] = i;
    std::sort(qid + 1, qid + q + 1, cmp);
    int lp = 0, rp = -1;
    for(int i = 1; i <= q; ++i) {
        int id = qid[i];
        Query& q = Q[id];
        while(rp < q.b) {
            ++rp;
            ++LC[R[rp].l];
            ++C[R[rp].l][R[rp].r];
        }
        while(rp > q.b) {
            --LC[R[rp].l];
            --C[R[rp].l][R[rp].r];
            --rp;
        }
        while(lp < q.a) {
            --LC[R[lp].l];
            --C[R[lp].l][R[lp].r];
            ++lp;
        }
        while(lp > q.a) {
            --lp;
            ++LC[R[lp].l];
            ++C[R[lp].l][R[lp].r];
        }
        for(int j = 0; j < k; ++j) {
            if(!LC[j])
                continue;
            int cur = 1;
            for(int x = j; x < k; ++x) {
                int c = q.str[x] - 'a';
                cur = sam.T[cur].ch[c];
                if(cur == 0)
                    break;
                if(C[j][x])
                    ans[id] += asInt64(C[j][x]) *
                        sam.T[cur].cnt;
            }
        }
    }
}
std::vector<int> lp[size];
void fooB(int n, int m, int q, int k) {
    sam.cookB(n);
    for(int i = 1; i <= q; ++i) {
        int cur = 1, cl = 0;
        Int64& res = ans[i];
        for(int j = 0; j < k; ++j)
            lp[j].clear();
        for(int j = Q[i].a; j <= Q[i].b; ++j)
            lp[R[j].r].push_back(R[j].l);
        for(int j = 0; j < k; ++j) {
            int c = Q[i].str[j] - 'a';
            while(cur && !sam.T[cur].ch[c])
                cur = sam.T[cur].link,
                cl = sam.T[cur].len;
            if(cur) {
                cur = sam.T[cur].ch[c], ++cl;
                for(int w = 0; w < lp[j].size(); ++w) {
                    int l = lp[j][w], len = j - l + 1,
                        p = cur;
                    if(cl < len)
                        continue;
                    for(int x = 19; x >= 0; --x)
                        if(sam.T[sam.fa[p][x]].len >=
                           len)
                            p = sam.fa[p][x];
                    res += sam.T[p].cnt;
                }
            } else
                cur = 1, cl = 0;
        }
    }
}
int pos[size];
int main() {
    int n = read();
    int m = read();
    int q = read();
    int k = read();
    int c;
    for(int i = 1; i <= n; ++i) {
        do
            c = getchar();
        while(c < 'a' || c > 'z');
        pos[i] = sam.extend(c - 'a');
    }
    for(int i = 1; i <= n; ++i)
        sam.T[pos[i]].cnt = 1;
    for(int i = 0; i < m; ++i) {
        R[i].l = read();
        R[i].r = read();
    }
    for(int i = 1; i <= q; ++i) {
        Q[i].str.reserve(k);
        for(int j = 1; j <= k; ++j) {
            do
                c = getchar();
            while(c < 'a' || c > 'z');
            Q[i].str.push_back(c);
        }
        Q[i].a = read();
        Q[i].b = read();
    }
    if(k <= sqrt(n))
        fooA(n, m, q, k);
    else
        fooB(n, m, q, k);
    for(int i = 1; i <= q; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
