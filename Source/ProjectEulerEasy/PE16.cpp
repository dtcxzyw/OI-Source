#include <algorithm>
#include <cstdio>
#include <cstring>
const int mod = 100000000, half = mod / 2;
struct BigNum {
    int num[50], siz;
    BigNum(int x = 0) : siz(1) {
        for(int i = 0; i < 50; ++i)
            num[i] = 0;
        num[1] = x;
    }
    void update() {
        for(int i = 1; i <= siz; ++i)
            if(num[i] >= mod) {
                num[i] -= mod;
                ++num[i + 1];
            }
        if(num[siz + 1])
            ++siz;
    }
    void operator+=(const BigNum& rhs) {
        siz = std::max(siz, rhs.siz);
        for(int i = 1; i <= siz; ++i)
            num[i] += rhs.num[i];
        update();
    }
    int count() const {
        int res = 0;
        for(int i = siz; i >= 1; --i) {
            int x = num[i];
            while(x) {
                res += x % 10;
                x /= 10;
            }
        }
        return res;
    }
};
int main() {
    int n;
    scanf("%d", &n);
    BigNum res(1);
    for(int i = 1; i <= n; ++i) {
        BigNum a = res;
        res += a;
    }
    printf("%d\n", res.count());
    return 0;
}
