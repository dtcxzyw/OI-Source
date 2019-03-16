#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long Int64;
const int size = 100005;
struct Range {
    Int64 l, r;
    Range(Int64 l, Int64 r) : l(l), r(r) {}
};
std::vector<Range> R[size];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        Int64 l, r;
        scanf("%lld%lld", &l, &r);
        R[i].push_back(Range(l, r));
    }
    Int64 res = 0;
    for(int i = 60; i >= 0; --i) {
        Int64 l = 1LL << i;
        bool flag = true;
        for(int j = 1; j <= n; ++j) {
            bool res = false;
            for(int k = 0; k < R[j].size(); ++k)
                if(R[j][k].r >= l) {
                    res = true;
                    break;
                }
            if(!res) {
                flag = false;
                break;
            }
        }
        if(flag) {
            res |= l;
            for(int j = 1; j <= n; ++j) {
                std::vector<Range> tmp;
                for(int k = 0; k < R[j].size(); ++k)
                    if(R[j][k].r >= l) {
                        Int64 nl =
                            std::max(R[j][k].l, l) ^ l;
                        tmp.push_back(
                            Range(nl, R[j][k].r ^ l));
                    }
                R[j].swap(tmp);
            }
        } else {
            for(int j = 1; j <= n; ++j) {
                for(int k = 0; k < R[j].size(); ++k) {
                    Range& cr = R[j][k];
                    if(cr.l >= l)
                        cr.l ^= l, cr.r ^= l;
                    else if(cr.r >= l) {
                        if((cr.r ^ l) >= cr.l - 1) {
                            R[j].clear();
                            R[j].push_back(
                                Range(0, l - 1));
                            break;
                        }
                        Int64 old = cr.r;
                        cr.r = l - 1;
                        R[j].push_back(
                            Range(0, old ^ l));
                    }
                }
            }
        }
    }
    printf("%lld\n", res);
    return 0;
}
