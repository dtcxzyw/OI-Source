// FIXME
// 最后每一项的求和要单位化，不会做
#include <cstdio>
#include <strstream>
namespace IO {
    char in[1 << 23], out[1 << 23];
    int init() {
        return fread(in, 1, sizeof(in), stdin);
    }
    void uninit(std::ostrstream& output) {
        int siz = output.pcount();
        fwrite(out, siz, 1, stdout);
    }
}
const int size = 200005;
typedef double FT;
struct Mat {
    FT A00, A01, A10, A11;
    Mat() {}
    Mat(FT A00, FT A01, FT A10, FT A11)
        : A00(A00), A01(A01), A10(A10), A11(A11) {}
    Mat operator+(const Mat& rhs) const {
        return Mat(A00 + rhs.A00, A01 + rhs.A01,
                   A10 + rhs.A10, A11 + rhs.A11);
    }
    Mat operator*(const Mat& rhs) const {
        return Mat(A00 * rhs.A00 + A01 * rhs.A10,
                   A00 * rhs.A01 + A01 * rhs.A11,
                   A10 * rhs.A00 + A11 * rhs.A10,
                   A10 * rhs.A01 + A11 * rhs.A11);
    }
} T[size << 2], S[size << 2];
void update(int id) {
    T[id] = T[id << 1] * T[id << 1 | 1];
    S[id] = S[id << 1] + T[id << 1] * S[id << 1 | 1];
}
FT P[size], Q[size];
Mat base[size][3], R, B;
void cook(int id) {
    Mat trans =
        Mat(P[id], 1.0 - P[id], Q[id], 1.0 - Q[id]);
    FT p = P[id + 1], q = Q[id + 1], np = 1.0 - p,
       nq = 1.0 - q;
    base[id][0] = Mat(np * trans.A00, nq * trans.A01,
                      np * trans.A10, nq * trans.A11);
    base[id][1] = Mat(p * trans.A00, q * trans.A01,
                      p * trans.A10, q * trans.A11);
    base[id][2] = trans;
}
bool flag[size];
void set(int id, int off, const Mat& X, const Mat& Y) {
    int p = id + off;
    T[p] = S[p] = X;
    if(!flag[id - 1])
        S[p - 1] = Y;
    int a = p, b = p - 1;
    while(a > 1) {
        update(a >>= 1);
        b >>= 1;
        if(b != a)
            update(b);
    }
}
int main() {
    std::istrstream input(IO::in, IO::init());
    std::ostrstream output(IO::out, sizeof(IO::out));
    output.precision(6);
    output << std::fixed;
    int n, m;
    char t;
    input >> n >> m >> t;
    int off = 1;
    while(off < (n + 2))
        off <<= 1;
    {
        input >> P[1];
        for(int i = 2; i <= n; ++i)
            input >> P[i] >> Q[i];
        for(int i = 1; i <= n; ++i) {
            cook(i);
            T[i + off] = S[i + off] = base[i][2];
        }
    }
    Mat I(1, 0, 0, 1);
    T[off] = I;
    for(int i = n + 1; i < off; ++i)
        T[i + off] = I;
    for(int i = off - 1; i >= 1; --i)
        update(i);
    R = Mat(1, 0, 1, 0), B = Mat(0, 1, 0, 1);
    for(int i = 1; i <= n; ++i) {
        char op[5];
        int id;
        input >> op >> id;
        if(*op == 'a') {
            int c;
            input >> c;
            set(id, off, c ? R : B, base[id - 1][c]);
            flag[id] = true;
        } else {
            flag[id] = false;
            set(id, off, base[id][2], base[id - 1][2]);
        }
        output << S[1].A00 << std::endl;
    }
    IO::uninit(output);
    return 0;
}
