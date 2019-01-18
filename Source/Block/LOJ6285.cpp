#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
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
const int size = 100005, bc = 32, bsiz = size / bc + 5;
int A[size], B[size], n;
int getL(int id) {
    return std::max(1, id * bc);
}
int getR(int id) {
    return std::min((id + 1) * bc - 1, n);
}
std::vector<int> pos[size];
struct Maxv {
    int cnt, val;
    bool operator<(const Maxv& rhs) const {
        return cnt == rhs.cnt ? val > rhs.val :
                                cnt < rhs.cnt;
    }
} C[bsiz][bsiz], cmaxv;
int cnt[size];
void add(int val) {
    int cc = ++cnt[val];
    if(cc > cmaxv.cnt)
        cmaxv.cnt = cc, cmaxv.val = val;
    else if(cc == cmaxv.cnt && val < cmaxv.val)
        cmaxv.val = val;
}
Maxv query(int l, int r, int val) {
    std::vector<int>& c = pos[val];
    int cnt = std::upper_bound(c.begin(), c.end(), r) -
        std::lower_bound(c.begin(), c.end(), l);
    Maxv res;
    res.cnt = cnt, res.val = val;
    return res;
}
int main() {
    n = read();
    // bc = sqrt(n / log2(n));
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    memcpy(B + 1, A + 1, sizeof(int) * n);
    std::sort(B + 1, B + n + 1);
    int siz = std::unique(B + 1, B + n + 1) - (B + 1);
    for(int i = 1; i <= n; ++i) {
        A[i] = std::lower_bound(B + 1, B + siz + 1,
                                A[i]) -
            B;
        pos[A[i]].push_back(i);
    }
    int maxb = n / bc;
    for(int i = 0; i <= maxb; ++i) {
        memset(cnt + 1, 0, sizeof(int) * siz);
        cmaxv.cnt = 0;
        for(int j = i; j <= maxb; ++j) {
            int l = getL(j), r = getR(j);
            for(int k = l; k <= r; ++k)
                add(A[k]);
            C[i][j] = cmaxv;
        }
    }
    for(int i = 1; i <= n; ++i) {
        int l = read();
        int r = read();
        int lb = l / bc, rb = r / bc;
        Maxv ans;
        ans.cnt = 0;
        if(lb == rb) {
            for(int i = l; i <= r; ++i)
                ans = std::max(ans, query(l, r, A[i]));
        } else {
            int bb = (l - 1) / bc + 1,
                eb = (r + 1) / bc - 1;
            int bbp = bb * bc, ebp = (eb + 1) * bc;
            ans = C[bb][eb];
            for(int i = l; i < bbp; ++i)
                ans = std::max(ans, query(l, r, A[i]));
            for(int i = ebp; i <= r; ++i)
                ans = std::max(ans, query(l, r, A[i]));
        }
        printf("%d\n", B[ans.val]);
    }
    return 0;
}
