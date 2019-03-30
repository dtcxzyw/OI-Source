#include <algorithm>
#include <cstdio>
namespace IO {
    char in[1 << 25];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
const int size = 3000005;
std::pair<int, int> A[size], B[size];
int main() {
    IO::init();
    int k = read();
    int n = read();
    int bA = 0, eA = 0, bB = 0, eB = 0, res = 0;
    for(int i = 1, j = 1; i <= n; ++i) {
        int x = read();
        std::pair<int, int> key(x, i);
        while(bA < eA && A[eA - 1].first < x)
            --eA;
        A[eA++] = key;
        while(bB < eB && B[eB - 1].first > x)
            --eB;
        B[eB++] = key;
        while(A[bA].first - B[bB].first > k) {
            ++j;
            if(A[bA].second < j)
                ++bA;
            if(B[bB].second < j)
                ++bB;
        }
        res = std::max(res, i - j + 1);
    }
    printf("%d\n", res);
    return 0;
}
