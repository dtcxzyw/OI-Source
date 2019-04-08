#include <cstdio>
namespace IO {
    char in[1 << 23];
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
const int size = 4005;
int S[size][size];
int getW(int l, int r) {
    return S[r][r] - S[l][r] - S[r][l] + S[l][l];
}
int main() {
    IO::init();
    int n = read();
    int k = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            S[i][j] = read() + S[i - 1][j] +
                S[i][j - 1] - S[i - 1][j - 1];
    return 0;
}
