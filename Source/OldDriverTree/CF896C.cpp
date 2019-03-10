#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
typedef long long Int64;
Int64 powm(Int64 a, int k, int mod) {
    a %= mod;
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int seed;
int getRandom() {
    int res = seed;
    seed = (seed * 7LL + 13LL) % 1000000007LL;
    return res;
}
struct Node {
    mutable Int64 val;
    int l;
    Node(Int64 val, int l) : val(val), l(l) {}
    bool operator<(const Node& rhs) const {
        return l < rhs.l;
    }
};
std::set<Node> seq;
typedef std::set<Node>::iterator IterT;
IterT split(int pos) {
    IterT it = seq.lower_bound(Node(0, pos));
    if(it->l == pos)
        return it;
    --it;
    return seq.insert(Node(it->val, pos)).first;
}
struct Info {
    Int64 val;
    int siz;
    Info(Int64 val, int siz) : val(val), siz(siz) {}
    bool operator<(const Info& rhs) const {
        return val < rhs.val;
    }
};
int main() {
    int n, m, maxv;
    scanf("%d%d%d%d", &n, &m, &seed, &maxv);
    for(int i = 1; i <= n; ++i) {
        Int64 x = getRandom() % maxv + 1;
        seq.insert(Node(x, i));
    }
    seq.insert(Node(0, n + 1));
    for(int t = 1; t <= m; ++t) {
        int op = getRandom() % 4;
        int l = getRandom() % n + 1;
        int r = getRandom() % n + 1;
        if(l > r)
            std::swap(l, r);
        int x = getRandom() %
                (op == 2 ? r - l + 1 : maxv) +
            1;
        IterT beg = split(l), end = split(r + 1);
        switch(op) {
            case 0: {
                for(IterT it = beg; it != end; ++it)
                    it->val += x;
            } break;
            case 1: {
                seq.erase(beg, end);
                seq.insert(Node(x, l));
            } break;
            case 2: {
                std::vector<Info> subseq;
                IterT it = beg, nxt = beg;
                ++nxt;
                for(; it != end; it = nxt++) {
                    int siz = nxt->l - it->l;
                    subseq.push_back(
                        Info(it->val, siz));
                }
                std::sort(subseq.begin(),
                          subseq.end());
                int cnt = 0;
                for(int i = 0; i < subseq.size();
                    ++i) {
                    cnt += subseq[i].siz;
                    if(cnt >= x) {
                        printf("%lld\n",
                               subseq[i].val);
                        break;
                    }
                }
            } break;
            case 3: {
                int y = getRandom() % maxv + 1;
                IterT it = beg, nxt = beg;
                ++nxt;
                Int64 res = 0;
                for(; it != end; it = nxt++) {
                    int siz = nxt->l - it->l;
                    res = (res +
                           siz * powm(it->val, x, y)) %
                        y;
                }
                printf("%lld\n", res);
            } break;
        }
    }
    return 0;
}
