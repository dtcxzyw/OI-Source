#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
typedef unsigned long long Int64;
int n, p, end, maxm;
struct Mat {
    int A[70 * 70];
    Int64 hash() const {
        Int64 res = 0;
        for(int i = 0; i < end; ++i)
            res = res * 131 + A[i];
        return res;
    }
    int* operator[](int x) {
        return A + x * n;
    }
    const int* operator[](int x) const {
        return A + x * n;
    }
    void reset() {
        memset(A, 0, end * sizeof(int));
    }
    void read() {
        for(int i = 0; i < end; ++i)
            scanf("%d", &A[i]);
    }
    void id() {
        reset();
        for(int i = 0; i < n; ++i)
            A[i * n + i] = 1;
    }
    Mat operator*(const Mat& rhs) const {
        Mat res;
        res.reset();
        for(int i = 0; i < n; ++i)
            for(int k = 0; k < n; ++k) {
                int base = A[i * n + k], *beg = res[i],
                    *end = res[i + 1];
                const int* ptr = rhs[k];
                for(int *j = beg; j < end;
                    ++j, ++ptr) {
                    int& val = *j;
                    val += base * *ptr;
                    if(val > maxm)
                        val %= p;
                }
            }
        for(int i = 0; i < end; ++i)
            res.A[i] %= p;
        return res;
    }
};
const int modu = 1009, modv = 997;
Int64 key[modu];
const Int64 magic = 0x3f74aeace643eU;
int val[modu];
void insert(const Mat& mat, int v) {
    Int64 hv = mat.hash();
    int ha = hv % modu, hb = 1 + hv % modv, cur = ha;
    while(true) {
        if(key[cur] == magic)
            key[cur] = hv;
        if(key[cur] == hv) {
            val[cur] = v;
            return;
        }
        cur += hb;
        if(cur >= modu)
            cur -= modu;
    }
}
int find(const Mat& mat) {
    Int64 hv = mat.hash();
    int ha = hv % modu, hb = 1 + hv % modv, cur = ha;
    while(true) {
        if(key[cur] == magic)
            return -1;
        if(key[cur] == hv)
            return val[cur];
        cur += hb;
        if(cur >= modu)
            cur -= modu;
    }
}
Mat pow(Mat a, int k) {
    Mat res;
    res.id();
    while(k) {
        if(k & 1)
            res = res * a;
        k >>= 1, a = a * a;
    }
    return res;
}
int main() {
    scanf("%d%d", &n, &p);
    end = n * n;
    for(int i = 0; i < modu; ++i)
        key[i] = magic;
    maxm = INT_MAX - (p - 1) * (p - 1);
    Mat A, B;
    A.read();
    B.read();
    int k = sqrt(p) + 1;
    for(int i = 1; i <= k; ++i) {
        B = B * A;
        insert(B, i);
    }
    Mat base = pow(A, k), cur = base;
    for(int i = 1; i <= k; ++i, cur = cur * base) {
        int j = find(cur);
        if(j != -1) {
            printf("%d\n", i * k - j);
            break;
        }
    }
    return 0;
}
