#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 30005, maxS = size * 2, esiz = 26;
struct SAM {
    struct State {
        int len, link, nxt[esiz], jmp, jdis;
        bool mark;
    } st[maxS];
    int siz, last;
    SAM() : siz(1), last(1) {}
    void reset() {
        memset(st + 1, 0, sizeof(State) * siz);
        siz = last = 1;
    }
    void extend(int c) {
        int id = ++siz;
        st[id].len = st[last].len + 1;
        int p = last;
        while(p && !st[p].nxt[c]) {
            st[p].nxt[c] = id;
            p = st[p].link;
        }
        if(p) {
            int q = st[p].nxt[c];
            if(st[p].len + 1 == st[q].len)
                st[id].link = q;
            else {
                int cq = ++siz;
                st[cq] = st[q];
                st[cq].len = st[p].len + 1;
                while(p && st[p].nxt[c] == q) {
                    st[p].nxt[c] = cq;
                    p = st[p].link;
                }
                st[q].link = st[id].link = cq;
            }
        } else
            st[id].link = 1;
        last = id;
    }
    int len() const {
        return st[last].len;
    }
    void jump(int u) {
        int p, dis = 0;
        for(p = u; st[p].jmp; p = st[p].jmp)
            dis += st[p].jdis;
        if(dis) {
            int res = p;
            for(p = u; st[p].jmp;) {
                int old = st[p].jdis;
                st[p].jdis = dis;
                dis -= old;
                int nxt = st[p].jmp;
                st[p].jmp = res;
                p = nxt;
            }
        }
    }
    int top, *sa;
    void DFS(int u, int d) {
        if(st[u].mark)
            sa[++top] = d;
        for(int i = 0; i < esiz; ++i) {
            int v = st[u].nxt[i];
            if(v) {
                jump(v);
                if(st[v].jmp)
                    DFS(st[v].jmp, d - 1 - st[v].jdis);
                else
                    DFS(v, d - 1);
            }
        }
    }
    void buildSA(int* buf) {
        for(int p = last; p != 1; p = st[p].link)
            st[p].mark = true;
        for(int i = 1; i <= siz; ++i)
            if(!st[i].mark) {
                int c = 0, p;
                for(int j = 0; j < esiz && c <= 1; ++j) {
                    int v = st[i].nxt[j];
                    if(v) {
                        p = v;
                        ++c;
                    }
                }
                if(c == 1)
                    st[i].jmp = p, st[i].jdis = 1;
            }
        sa = buf;
        top = 0;
        DFS(1, len() + 1);
    }
} sam;
char A[size];
int SA[size], rank[2][size], height[2][15][size];
void initSA(int n, int id) {
    for(int i = 1; i <= n; ++i)
        rank[id][SA[i]] = i;
    int h = 0;
    for(int i = 1; i <= n; ++i) {
        if(rank[id][i] == 1)
            h = 0;
        else {
            int k = SA[rank[id][i] - 1];
            if(h)
                --h;
            while(A[i + h] == A[k + h])
                ++h;
        }
        height[id][0][rank[id][i]] = h;
    }
    for(int i = 1; i < 15; ++i) {
        int end = n - (1 << i) + 1, off = 1 << (i - 1);
        for(int j = 1; j <= end; ++j)
            height[id][i][j] = std::min(height[id][i - 1][j],
                                        height[id][i - 1][j + off]);
    }
}
int ilg2(int x) {
    return 31 - __builtin_clz(x);
}
int query(int l, int r, int id) {
    int p = ilg2(r - l + 1);
    return std::min(height[id][p][l],
                    height[id][p][r - (1 << p) + 1]);
}
int lcp(int l, int r, int id) {
    l = rank[id][l], r = rank[id][r];
    if(l > r)
        std::swap(l, r);
    return query(l + 1, r, id);
}
typedef long long Int64;
int L[size], R[size];
Int64 foo() {
    scanf("%s", A + 1);
    sam.reset();
    for(int i = 1; A[i]; ++i)
        sam.extend(A[i] - 'a');
    sam.buildSA(SA);
    int n = sam.len();
    initSA(n, 0);
    std::reverse(A + 1, A + n + 1);
    sam.reset();
    for(int i = 1; A[i]; ++i)
        sam.extend(A[i] - 'a');
    sam.buildSA(SA);
    initSA(n, 1);
    memset(L, 0, sizeof(int) * (n + 2));
    memset(R, 0, sizeof(int) * (n + 2));
    int end = n >> 1;
    for(int i = 1; i <= end; ++i) {
        int right = 0;
        for(int r = i << 1; r <= n; r += i) {
            int l = r - i;
            if(l > right) {
                int a = lcp(l, r, 0),
                    b = lcp(n - l + 1, n - r + 1, 1);
                if(a + b > i) {
                    int beg = l - b + 1, end = l + a - i + 1,
                        off = 2 * i - 1;
                    ++R[beg], --R[end];
                    ++L[beg + off], --L[end + off];
                }
                right = l + a - 1;
            }
        }
    }
    for(int i = 1; i <= n; ++i)
        L[i] += L[i - 1], R[i] += R[i - 1];
    Int64 res = 0;
    for(int i = 2; i < n; ++i)
        res += L[i] * R[i + 1];
    return res;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--)
        printf("%lld\n", foo());
    return 0;
}
