#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int modu = 23003, modv = 22993, inf = 1 << 30;
struct HashTable {
    std::vector<std::pair<int, int> > LUT;
    std::vector<int> st;
    HashTable() : LUT(modu) {
        for(int i = 0; i < modu; ++i) {
            LUT[i].first = -1;
            LUT[i].second = -inf;
        }
    }
    void swap(HashTable& rhs) {
        LUT.swap(rhs.LUT);
        st.swap(rhs.st);
    }
    int& operator[](int x) {
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
int A[105][11], res = -inf;
void CAS(int& a, int b) {
    a = std::max(a, b);
}
void update(int m, HashTable& lut, int x, int val) {
    int c = get(x, m + 1);
    if(c == 2 && set(x, m + 1, 2, 0) == 0)
        CAS(res, val);
    else
        CAS(lut[x], val);
}
void tran(int i, int j, int n, int m, HashTable& lut,
          HashTable& clut) {
    int val = A[i][j];
    for(int k = 0; k < lut.st.size(); ++k) {
        int cur = lut.st[k];
        int base = lut[cur], sum = val + base;
        int vcnt = get(cur, m + 1);
        if(j == 1)
            cur = set(set(cur, m + 1, vcnt, 0) << 2,
                      m + 1, 0, vcnt);
        int la = get(cur, j - 1), lb = get(cur, j);
        int vaild = (la ? 1 : 0) + (lb ? 1 : 0);
        // 0
        if(vaild == 0)
            update(m, clut, cur, base);
        // 1
        if(vcnt < 2) {
            if(vaild == 1) {
                int dst =
                    set(set(set(cur, j - 1, la, 0), j,
                            lb, 0),
                        m + 1, vcnt, vcnt + 1);
                int ori = la | lb;
                if(ori != 3) {
                    int src = la ? j - 1 : j;
                    int pos = ori == 1 ?
                        next(cur, src) :
                        prev(cur, src);
                    dst = set(dst, pos, 3 - ori, 3);
                }
                update(m, clut, dst, sum);
            } else if(vaild == 0) {
                if(i != n) {
                    int dst =
                        set(set(cur, j - 1, 0, 3),
                            m + 1, vcnt, vcnt + 1);
                    update(m, clut, dst, sum);
                }
                if(j != m) {
                    int dst =
                        set(set(cur, j, 0, 3), m + 1,
                            vcnt, vcnt + 1);
                    update(m, clut, dst, sum);
                }
            }
        }
        // 2
        switch(vaild) {
            // rb
            case 0: {
                if(i != n && j != m) {
                    int dst =
                        set(set(cur, j - 1, 0, 1), j,
                            0, 2);
                    update(m, clut, dst, sum);
                }
            } break;
            // l/t+r/b
            case 1: {
                int src = la | lb;
                // b
                if(i != n) {
                    int dst =
                        set(set(cur, j - 1, la, src),
                            j, lb, 0);
                    update(m, clut, dst, sum);
                }
                // r
                if(j != m) {
                    int dst =
                        set(set(cur, j - 1, la, 0), j,
                            lb, src);
                    update(m, clut, dst, sum);
                }
            } break;
            // lt
            case 2: {
                int dst = cur;
                if(la == 1) {
                    if(lb == 1) {
                        int pos = next(cur, j);
                        dst = set(cur, pos, 2, 1);
                    } else if(lb == 2)
                        continue;
                    else {
                        int pos = next(cur, j - 1);
                        dst = set(cur, pos, 2, 3);
                    }
                } else if(la == 2) {
                    if(lb != 1) {
                        int pos = prev(cur, j - 1);
                        dst = set(cur, pos, 1, lb);
                    }
                } else {
                    if(lb == 1) {
                        int pos = next(cur, j);
                        dst = set(cur, pos, 2, 3);
                    } else if(lb == 2) {
                        int pos = prev(cur, j);
                        dst = set(cur, pos, 1, 3);
                    }
                }
                dst = set(set(dst, j - 1, la, 0), j,
                          lb, 0);
                update(m, clut, dst, sum);
            } break;
        }
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            scanf("%d", &A[i][j]);
            res = std::max(res, A[i][j]);
        }
    HashTable lut;
    lut[0] = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            HashTable clut;
            tran(i, j, n, m, lut, clut);
            clut.swap(lut);
        }
    printf("%d\n", res);
    return 0;
}
