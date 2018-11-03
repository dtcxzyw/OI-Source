#include <algorithm>
#include <cmath>
#include <cstdio>
typedef double FT;
const FT deg2Rad = acos(-1.0) / 180.0;
struct Vec {
    FT x, y, z;
    Vec() {}
    Vec(int id)
        : x(id & 1 ? 1.0 : -1.0),
          y(id & 2 ? 1.0 : -1.0),
          z(id & 4 ? 1.0 : -1.0) {}
    Vec(FT x, FT y, FT z) : x(x), y(y), z(z) {}
    void normailze() {
        FT dis = sqrt(x * x + y * y + z * z);
        x /= dis, y /= dis, z /= dis;
    }
    FT operator[](int idx) const {
        if(idx == 0)
            return x;
        if(idx == 1)
            return y;
        return z;
    }
    FT& operator[](int idx) {
        if(idx == 0)
            return x;
        if(idx == 1)
            return y;
        return z;
    }
    Vec operator-(const Vec& rhs) const {
        return Vec(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    int getId() const {
        return (x > 0.0 ? 1 : 0) | (y > 0.0 ? 2 : 0) |
            (z > 0.0 ? 4 : 0);
    }
};
Vec cross(const Vec& a, const Vec& b) {
    return Vec(a.y * b.z - a.z * b.y,
               a.z * b.x - a.x * b.z,
               a.x * b.y - a.y * b.x);
}
FT dot(const Vec& a, const Vec& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
struct Mat {
    Vec A[3];
    Vec operator[](int idx) const {
        return A[idx];
    }
    Vec& operator[](int idx) {
        return A[idx];
    }
    Vec operator()(const Vec& rhs) const {
        return Vec(dot(A[0], rhs), dot(A[1], rhs),
                   dot(A[2], rhs));
    }
};
Mat genCoordSystem(Vec axis) {
    Vec base(1.0, 2.0, 3.0);
    Mat res;
    res[0] = cross(base, axis);
    res[1] = cross(res[0], axis);
    res[2] = axis;
    for(int i = 0; i < 3; ++i)
        res[i].normailze();
    return res;
}
Mat getInv(const Mat& rhs) {
    Mat res;
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            res[i][j] = rhs[j][i];
    return res;
}
int lut[24][12], tid[8], link[8][8];
void rotate(int id, const Vec& axis, FT deg) {
    Mat trans = genCoordSystem(axis),
        inv = getInv(trans), rot;
    FT rad = deg * deg2Rad;
    rot[0] = Vec(cos(rad), -sin(rad), 0.0);
    rot[1] = Vec(sin(rad), cos(rad), 0.0);
    rot[2] = Vec(0.0, 0.0, 1.0);
    for(int i = 0; i < 8; ++i) {
        Vec tp = inv(rot(trans(Vec(i))));
        tid[i] = tp.getId();
    }
    for(int i = 0; i < 8; ++i) {
        for(int j = 1; j <= 4; j <<= 1)
            if(i & j) {
                int k = i ^ j, tu = tid[i],
                    tv = tid[k];
                if(tu < tv)
                    std::swap(tu, tv);
                lut[id][link[i][k]] = link[tu][tv];
            }
    }
}
void genTable() {
    int eid = 0;
    for(int i = 0; i < 8; ++i)
        for(int j = 1; j <= 4; j <<= 1)
            if(i & j)
                link[i][i ^ j] = eid++;
    for(int i = 0; i < 12; ++i)
        lut[0][i] = i;
    int id = 0;
    for(int i = 0; i < 3; ++i)
        for(int j = 90; j <= 270; j += 90)
            rotate(++id, Vec(i == 0, i == 1, i == 2),
                   j);
    for(int i = 0; i < 3; ++i) {
        Vec base(i != 0, i != 1, i != 2);
        rotate(++id, base, 180.0);
        for(int j = 0; j < 3; ++j)
            if(base[j] == 1) {
                base[j] = -1;
                break;
            }
        rotate(++id, base, 180.0);
    }
    for(int i = 0; i < 8; ++i)
        if(i < (i ^ 7)) {
            Vec base = Vec(i) - Vec(i ^ 7);
            rotate(++id, base, 120.0);
            rotate(++id, base, 240.0);
        }
}
int col[12];
int foo() {
    for(int i = 0; i < 12; ++i)
        scanf("%d", &col[i]);
    std::sort(col, col + 12);
    int cnt = 0;
    do {
        for(int i = 0; i < 24; ++i) {
            bool flag = true;
            for(int j = 0; j < 12; ++j)
                if(col[lut[i][j]] != col[j]) {
                    flag = false;
                    break;
                }
            cnt += flag;
        }
    } while(std::next_permutation(col, col + 12));
    return cnt / 24;
}
int main() {
    genTable();
    int t;
    scanf("%d", &t);
    while(t--)
        printf("%d\n", foo());
    return 0;
}
