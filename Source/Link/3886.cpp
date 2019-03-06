#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int modu = 23003, modv = 22993;
typedef long long Int64;
struct HashTable {
    std::vector<std::pair<Int64, int> > LUT;
    std::vector<Int64> st;
    HashTable() : LUT(modu) {
        for(int i = 0; i < modu; ++i) {
            LUT[i].first = -1;
            LUT[i].second = -(1 << 30);
        }
    }
    void swap(HashTable& rhs) {
        LUT.swap(rhs.LUT);
        st.swap(rhs.st);
    }
    int& operator[](Int64 x) {
        int ha = x % modu, hb = 1 + x % modv, cur = ha;
        while(true) {
            if(LUT[cur].first == -1) {
                LUT[cur].first = x;
                st.push_back(x);
            }
            if(LUT[cur].first == x)
                return LUT[cur].second;
            cur += hb;
            if(cur >= modu)
                cur -= modu;
        }
    }
};
Int64 rescan(int m, Int64 x) {
    int remap[16], cnt = 0;
    remap[0] = 0;
    for(int i = 1; i < 16; ++i)
        remap[i] = -1;
    Int64 res = 0;
    for(int i = 0; i < m; ++i, x >>= 4) {
        Int64 b = x & 15;
        if(remap[b] == -1)
            remap[b] = ++cnt;
        b = remap[b];
        res |= b << (i * 4);
    }
    return res;
}
Int64 get(Int64 x, int i) {
    return (x >> (i * 4)) & 15;
}
Int64 set(Int64 x, int i, Int64 sb, Int64 db) {
    return x ^ ((sb ^ db) << (i * 4));
}
void CAS(int& a, int b) {
    a = std::max(a, b);
}
const int nlb = 15;
Int64 merge(int m, Int64 x, int a, int b) {
    Int64 res = 0;
    for(int i = 0; i < m; ++i, x >>= 4) {
        Int64 cb = x & 15;
        cb = ((cb == a || cb == b) ? nlb : cb);
        res |= cb << (i * 4);
    }
    return rescan(m, res);
}
bool find(int m, Int64 x, int b, int p) {
    for(int i = 0; i < m; ++i, x >>= 4) {
        int cb = x & 15;
        if(cb == b && i != p)
            return true;
    }
    return false;
}
bool test(int m, Int64 x) {
    for(int i = 0; i < m; ++i, x >>= 4) {
        int cb = x & 15;
        if(cb > 1)
            return false;
    }
    return true;
}
int A[15][15];
void tran(int i, int j, int n, HashTable& lut,
          HashTable& clut) {
    int val = A[i][j];
    for(int k = 0; k < lut.st.size(); ++k) {
        Int64 cur = lut.st[k];
        int base = lut[cur], sum = base + val;
        int la = j == 0 ? 0 : get(cur, j - 1),
            lb = get(cur, j);
        Int64 dst;
        if(la && lb)
            dst = merge(n, cur, la, lb);
        else {
            int src = la | lb;
            dst = rescan(
                n, set(cur, j, lb, src ? src : nlb));
        }
        CAS(clut[dst], sum);
        if(lb) {
            if(find(n, cur, lb, j)) {
                Int64 dst =
                    rescan(n, set(cur, j, lb, 0));
                CAS(clut[dst], base);
            }
        } else
            CAS(clut[cur], base);
    }
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", &A[i][j]);
    HashTable lut;
    lut[0] = 0;
    int res = -(1 << 30);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            HashTable clut;
            tran(i, j, n, lut, clut);
            clut.swap(lut);
            for(int k = 0; k < lut.st.size(); ++k) {
                Int64 s = lut.st[k];
                if(s && test(n, s))
                    res = std::max(res, lut[s]);
            }
        }
    printf("%d\n", res);
    return 0;
}
