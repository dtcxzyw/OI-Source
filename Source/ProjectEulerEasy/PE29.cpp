#include <algorithm>
#include <cstdio>
class BigNum {
private:
    static const int bit = 9;
    static const unsigned long long mod =
        1000000000ULL;
    unsigned int mData[205];
    int mSize;

public:
    BigNum() {}
    BigNum(int i) : mSize(1) {
        mData[0] = i;
    }
    void operator*=(long long rhs) {
        if(rhs == 0)
            mSize = 1, mData[0] = 0;
        if(mSize == 1 && mData[0] == 0)
            return;
        unsigned long long tmp = 0;
        for(int i = 0; i < mSize; ++i) {
            tmp += mData[i] * rhs;
            mData[i] = tmp % mod;
            tmp /= mod;
        }
        if(tmp) {
            mData[mSize] = tmp;
            ++mSize;
        }
    }
    bool operator<(const BigNum& rhs) const {
        if(mSize != rhs.mSize)
            return mSize < rhs.mSize;
        for(int i = mSize - 1; i >= 0; --i)
            if(mData[i] != rhs.mData[i])
                return mData[i] < rhs.mData[i];
        return false;
    }
    bool operator==(const BigNum& rhs) const {
        if(mSize != rhs.mSize)
            return false;
        for(int i = 0; i < mSize; ++i)
            if(mData[i] != rhs.mData[i])
                return false;
        return true;
    }
} A[10005];
int main() {
    int icnt = 0;
    for(int a = 2; a <= 100; ++a) {
        BigNum c(a);
        for(int b = 2; b <= 100; ++b) {
            c *= a;
            A[icnt++] = c;
        }
    }
    std::sort(A, A + icnt);
    int siz = std::unique(A, A + icnt) - A;
    printf("%d\n", siz);
    return 0;
}
