#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
class Integer {
private:
    std::vector<int> bit;
    const int mod = 1000000000;

public:
    void init() {
        bit.push_back(1);
    }
    void operator+=(const Integer& rhs) {
        if(rhs.bit.size() > bit.size())
            bit.resize(rhs.bit.size());
        for(int i = 0; i < rhs.bit.size(); ++i)
            bit[i] += rhs.bit[i];
        for(int i = 0; i < bit.size(); ++i) {
            if(bit[i] >= mod) {
                if(i == bit.size() - 1)
                    bit.push_back(1);
                else
                    ++bit[i + 1];
                bit[i] -= mod;
            }
        }
    }
    void print() {
        printf("%d", bit.back());
        for(int i = bit.size() - 2; i >= 0; --i)
            printf("%09d", bit[i]);
    }
    bool zero() const {
        return bit.empty();
    }
};
const int size = 3050;
char A[size], B[size];
int nxtA[size][52], nxtB[size][52];
Integer dp[size][size];
void DFSA(int x, int y) {
    if(dp[x][y].zero()) {
        dp[x][y].init();
        for(int i = 0; i < 52; ++i) {
            int a = nxtA[x][i], b = nxtB[y][i];
            if(a && b) {
                DFSA(a, b);
                dp[x][y] += dp[a][b];
            }
        }
    }
}
std::vector<std::string> base[size][size];
void DFSB(int x, int y) {
    if(base[x][y].empty()) {
        std::string s;
        if(x)
            s.push_back(A[x]);
        base[x][y].push_back(s);
        for(int i = 0; i < 52; ++i) {
            int a = nxtA[x][i], b = nxtB[y][i];
            if(a && b) {
                DFSB(a, b);
                for(int j = 0; j < base[a][b].size();
                    ++j)
                    base[x][y].push_back(
                        s + base[a][b][j]);
            }
        }
    }
}
int map[256];
int main() {
    for(int i = 0; i < 26; ++i)
        map['a' + i] = i;
    for(int i = 0; i < 26; ++i)
        map['A' + i] = 26 + i;
    int n, m, k;
    scanf("%d%d%s%s%d", &n, &m, A + 1, B + 1, &k);
    for(int i = n; i >= 1; --i) {
        for(int j = 0; j < 52; ++j)
            nxtA[i - 1][j] = nxtA[i][j];
        nxtA[i - 1][map[A[i]]] = i;
    }
    for(int i = m; i >= 1; --i) {
        for(int j = 0; j < 52; ++j)
            nxtB[i - 1][j] = nxtB[i][j];
        nxtB[i - 1][map[B[i]]] = i;
    }
    if(k) {
        DFSB(0, 0);
        std::vector<std::string>& vs = base[0][0];
        std::sort(vs.begin(), vs.end());
        for(int i = 0; i < vs.size(); ++i)
            puts(vs[i].c_str());
        printf("%d\n", static_cast<int>(vs.size()));
    } else {
        DFSA(0, 0);
        dp[0][0].print();
    }
    return 0;
}
