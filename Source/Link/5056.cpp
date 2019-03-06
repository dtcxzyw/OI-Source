#include <cstdio>
#include <cstring>
#include <vector>
typedef long long Int64;
const int modu = 23003, modv = 22993;
struct HashTable {
    std::vector<std::pair<int, Int64> > LUT;
    std::vector<int> st;
    HashTable() : LUT(modu) {
        for(int i = 0; i < modu; ++i)
            LUT[i].first = -1;
    }
    void swap(HashTable& rhs) {
        LUT.swap(rhs.LUT);
        st.swap(rhs.st);
    }
    Int64& operator[](int x) {
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
int get(int x, int i) {
    return (x >> (i * 2)) & 3;
}
int set(int x, int i, int sb, int db) {
    return x ^ ((sb ^ db) << (i * 2));
}
int prev(int x, int i) {
    int sum = 0;
    while(true) {
        int c = get(x, i);
        if(c == 2)
            ++sum;
        else if(c == 1)
            --sum;
        if(sum == 0)
            return i;
        --i;
    }
}
int next(int x, int i) {
    int sum = 0;
    while(true) {
        int c = get(x, i);
        if(c == 1)
            ++sum;
        else if(c == 2)
            --sum;
        if(sum == 0)
            return i;
        ++i;
    }
}
char A[15][15];
void tran(int i, int j, int n, int m, HashTable& lut,
          HashTable& clut, bool last) {
    bool trans = A[i][j] == '.';
    for(int k = 0; k < lut.st.size(); ++k) {
        int cur = lut.st[k];
        Int64 val = lut[cur];
        if(j == 1)
            cur <<= 2;
        int la = get(cur, j - 1), lb = get(cur, j);
        int vaild = (la ? 1 : 0) + (lb ? 1 : 0);
        if(trans) {
            switch(vaild) {
                // rb
                case 0: {
                    if(i != n && j != m) {
                        int dst =
                            set(set(cur, j - 1, 0, 1),
                                j, 0, 2);
                        clut[dst] += val;
                    }
                } break;
                // l/t+r/b
                case 1: {
                    int src = la | lb;
                    // b
                    if(i != n) {
                        int dst = set(
                            set(cur, j - 1, la, src),
                            j, lb, 0);
                        clut[dst] += val;
                    }
                    // r
                    if(j != m) {
                        int dst =
                            set(set(cur, j - 1, la, 0),
                                j, lb, src);
                        clut[dst] += val;
                    }
                } break;
                // lt
                case 2: {
                    int dst = cur;
                    if(la == 1) {
                        if(lb == 1) {
                            int pos = next(cur, j);
                            dst = set(cur, pos, 2, 1);
                        } else if(!last)
                            continue;
                    } else if(lb == 2) {
                        int pos = prev(cur, j - 1);
                        dst = set(cur, pos, 1, 2);
                    }
                    dst = set(set(dst, j - 1, la, 0),
                              j, lb, 0);
                    clut[dst] += val;
                } break;
            }
        } else if(vaild == 0) {
            int dst = cur;
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
