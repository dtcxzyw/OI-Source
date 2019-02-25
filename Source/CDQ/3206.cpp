#include <algorithm>
#include <cstdio>
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
const int size = 50005, inf = 1 << 30,
          magic = -(0x35fa35c);
typedef long long Int64;
struct Edge {
    int id, u, v, w;
    bool operator<(const Edge& rhs) const {
        return w < rhs.w;
    }
};
bool cmpId(const Edge& a, const Edge& b) {
    return a.id < b.id;
}
int find(std::vector<int>& fa, int x) {
    return fa[x] ? fa[x] = find(fa, fa[x]) : x;
}
void merge(std::vector<int>& fa, std::vector<int>& rk,
           int u, int v) {
    if(rk[u] < rk[v])
        fa[u] = v;
    else {
        fa[v] = u;
        if(rk[u] == rk[v])
            ++rk[u];
    }
}
struct Info {
    std::vector<Edge> E;
    Int64 sum;
    int vsiz;
};
void MST(Info& info) {
    std::vector<Edge>& E = info.E;
    std::sort(E.begin(), E.end());
    std::vector<int> fa(info.vsiz + 5),
        rk(info.vsiz + 5);
    int cnt = info.vsiz - 1;
    for(int i = 0; i < E.size(); ++i) {
        int u = find(fa, E[i].u), v = find(fa, E[i].v);
        if(u != v) {
            info.sum += E[i].w;
            E[i].w = magic;
            merge(fa, rk, u, v);
            if(--cnt == 0)
                break;
        }
    }
}
struct Op {
    int k, w;
} Op[size];
Int64 ans[size];
void solve(int l, int r, Info& info) {
    if(l == r) {
        for(int i = 0; i < info.E.size(); ++i)
            if(info.E[i].id == Op[l].k)
                info.E[i].w = Op[l].w;
        MST(info);
        ans[l] = info.sum;
    } else {
        std::vector<int> eid;
        eid.reserve(r - l + 1);
        for(int i = l; i <= r; ++i)
            eid.push_back(Op[i].k);
        std::sort(eid.begin(), eid.end());
        eid.erase(std::unique(eid.begin(), eid.end()),
                  eid.end());
        // R
        {
            Info tmp;
            for(int i = 0; i < info.E.size(); ++i) {
                if(!std::binary_search(eid.begin(),
                                       eid.end(),
                                       info.E[i].id))
                    tmp.E.push_back(info.E[i]);
            }
            tmp.vsiz = info.vsiz;
            MST(tmp);
            std::vector<int> ueid;
            for(int i = 0; i < tmp.E.size(); ++i)
                if(tmp.E[i].w == magic)
                    ueid.push_back(tmp.E[i].id);
            std::sort(ueid.begin(), ueid.end());
            int cur = 0;
            for(int i = 0; i < info.E.size(); ++i) {
                int id = info.E[i].id;
                if(std::binary_search(eid.begin(),
                                      eid.end(), id) ||
                   std::binary_search(ueid.begin(),
                                      ueid.end(), id))
                    info.E[cur++] = info.E[i];
            }
            info.E.resize(cur);
        }
        // C
        {
            Info tmp = info;
            for(int i = 0; i < tmp.E.size(); ++i) {
                if(std::binary_search(eid.begin(),
                                      eid.end(),
                                      tmp.E[i].id))
                    tmp.E[i].w = -1;
            }
            MST(tmp);
            std::vector<int> ueid;
            for(int i = 0; i < tmp.E.size(); ++i)
                if(!std::binary_search(eid.begin(),
                                       eid.end(),
                                       tmp.E[i].id) &&
                   tmp.E[i].w == magic)
                    ueid.push_back(tmp.E[i].id);
            std::sort(ueid.begin(), ueid.end());
            std::vector<int> fa(info.vsiz + 5),
                rk(info.vsiz + 5);
            int cur = 0;
            for(int i = 0; i < info.E.size(); ++i) {
                int id = info.E[i].id;
                if(std::binary_search(
                       ueid.begin(), ueid.end(), id)) {
                    info.sum += info.E[i].w;
                    merge(fa, rk,
                          find(fa, info.E[i].u),
                          find(fa, info.E[i].v));
                } else
                    info.E[cur++] = info.E[i];
            }
            info.E.resize(cur);
            std::vector<int> pid;
            for(int i = 1; i <= info.vsiz; ++i)
                if(find(fa, i) == i)
                    pid.push_back(i);
            info.vsiz = pid.size();
            for(int i = 0; i < info.E.size(); ++i) {
                int u = find(fa, info.E[i].u);
                int v = find(fa, info.E[i].v);
                info.E[i].u =
                    std::lower_bound(pid.begin(),
                                     pid.end(), u) -
                    pid.begin() + 1;
                info.E[i].v =
                    std::lower_bound(pid.begin(),
                                     pid.end(), v) -
                    pid.begin() + 1;
            }
        }
        int m = (l + r) >> 1;
        Info tmp = info;
        solve(l, m, tmp);
        std::sort(info.E.begin(), info.E.end(), cmpId);
        for(int i = l; i <= m; ++i) {
            Edge e;
            e.id = Op[i].k;
            std::vector<Edge>::iterator p =
                std::lower_bound(info.E.begin(),
                                 info.E.end(), e,
                                 cmpId);
            if(p != info.E.end() && p->id == e.id)
                p->w = Op[i].w;
        }
        solve(m + 1, r, info);
    }
}
int main() {
    int n = read();
    int m = read();
    int q = read();
    Info info;
    info.vsiz = n;
    info.sum = 0;
    info.E.resize(m);
    for(int i = 0; i < m; ++i) {
        info.E[i].id = i + 1;
        info.E[i].u = read();
        info.E[i].v = read();
        info.E[i].w = read();
    }
    for(int i = 1; i <= q; ++i) {
        Op[i].k = read();
        Op[i].w = read();
    }
    solve(1, q, info);
    for(int i = 1; i <= q; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
