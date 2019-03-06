#include <cstdio>
#include <cstring>
#include <vector>
typedef long long Int64;
const int modu = 23003, modv = 22993;
struct HashTable {
    std::vector<std::pair<Int64, Int64> > LUT;
    std::vector<Int64> st;
    HashTable() : LUT(modu) {
        for(int i = 0; i < modu; ++i)
            LUT[i].first = -1;
    }
    void swap(HashTable& rhs) {
        LUT.swap(rhs.LUT);
        st.swap(rhs.st);
    }
    Int64& operator[](Int64 x) {
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
    int remap[8], cnt = 0;
    remap[0] = 0;
    for(int i = 1; i < 8; ++i)
        remap[i] = -1;
    Int64 res = 0;
    for(int i = 0; i <= m; ++i, x >>= 3) {
        Int64 b = x & 7;
        if(remap[b] == -1)
            remap[b] = ++cnt;
        b = remap[b];
        res |= b << (i * 3);
    }
    return res;
}
int get(Int64 x, int i) {
    return (x >> (i * 3)) & 7;
}
Int64 set(Int64 x, int i, Int64 sb, Int64 db) {
    return x ^ ((sb ^ db) << (i * 3));
}
const int nlb = 7;
Int64 merge(int m, Int64 x, int a, int b, int ea,
            int eb) {
    Int64 res = 0;
    for(int i = 0; i <= m; ++i, x >>= 3) {
        Int64 cb = x & 7;
        cb = ((cb == a || cb == b) ? nlb : cb);
        if(i == ea || i == eb)
            cb = 0;
        res |= cb << (i * 3);
    }
    return rescan(m, res);
}
char A[15][15];
void tran(int i, int j, int n, int m, HashTable& lut,
          HashTable& clut, bool last) {
    bool trans = A[i][j] == '.';
    for(int k = 0; k < lut.st.size(); ++k) {
        Int64 cur = lut.st[k];
        Int64 val = lut[cur];
        if(j == 1)
            cur <<= 3;
        int la = get(cur, j - 1), lb = get(cur, j);
        int vaild = (la ? 1 : 0) + (lb ? 1 : 0);
        if(trans) {
            switch(vaild) {
                // rb
                case 0: {
                    if(i != n && j != m) {
                        Int64 dst = rescan(
                            m, set(set(cur, j - 1, 0,
                                       nlb),
                                   j, 0, nlb));
                        clut[dst] += val;
                    }
                } break;
                // l/t+r/b
                case 1: {
                    int src = la | lb;
                    // b
                    if(i != n) {
                        Int64 dst = set(
                            set(cur, j - 1, la, src),
                            j, lb, 0);
                        clut[dst] += val;
                    }
                    // r
                    if(j != m) {
                        Int64 dst =
                            set(set(cur, j - 1, la, 0),
                                j, lb, src);
                        clut[dst] += val;
                    }
                } break;
                // lt
                case 2: {
                    if((la != lb) || last) {
                        Int64 dst = merge(
                            m, cur, la, lb, j - 1, j);
                        clut[dst] += val;
                    }
                } break;
            }
        } else if(vaild == 0) {
            Int64 dst = cur;
            clut[dst] += val;
        }
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int li, lj;
    for(int i = 1; i <= n; ++i) {
        scanf("%s", A[i] + 1);
        for(int j = 1; j <= m; ++j)
            if(A[i][j] == '.')
                li = i, lj = j;
    }
    HashTable lut;
    lut[0] = 1;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            HashTable clut;
            tran(i, j, n, m, lut, clut,
                 i == li && j == lj);
            clut.swap(lut);
        }
    printf("%lld\n", lut[0]);
    return 0;
}
