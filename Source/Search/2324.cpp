#include <cctype>
#include <cstdio>
#include <map>
#include <vector>
int getChar() {
    int c;
    do
        c = getchar();
    while(!isgraph(c));
    return c;
}
int read() {
    int s = 0;
    for(int i = 0; i < 25; ++i) {
        int ch = getChar();
        if(ch == '*')
            s |= (i << 25);
        else if(ch == '1')
            s |= (1 << i);
    }
    return s;
}
const int off[8][2] = { { -1, -2 }, { -2, -1 },
                        { 1, -2 },  { -2, 1 },
                        { -1, 2 },  { 2, -1 },
                        { 1, 2 },   { 2, 1 } };
int move(int s, int dir) {
    int ep = s >> 25;
    int x = ep / 5, y = ep % 5;
    int ox = x + off[dir][0], oy = y + off[dir][1];
    if(0 <= ox && ox < 5 && 0 <= oy && oy < 5) {
        int nep = ox * 5 + oy;
        int col = ((s >> nep) & 1) << ep;
        int mask = ((1 << 25) - 1) ^ (1 << nep);
        return (s & mask) | col | (nep << 25);
    }
    return -1;
}
int genDst() {
    const char* str = "111110111100*110000100000";
    int s = 0;
    for(int i = 0; i < 25; ++i) {
        int ch = str[i];
        if(ch == '*')
            s |= (i << 25);
        else if(ch == '1')
            s |= (1 << i);
    }
    return s;
}
bool extend(int i, std::vector<int>& cur,
            std::map<int, int>& his,
            std::map<int, int>& lut) {
    std::vector<int> now;
    for(int j = 0; j < cur.size(); ++j) {
        int s = cur[j];
        for(int k = 0; k < 8; ++k) {
            int t = move(s, k);
            if(t != -1) {
                if(lut.count(t))
                    return true;
                if(!his.count(t)) {
                    his[t] = i;
                    now.push_back(t);
                }
            }
        }
    }
    now.swap(cur);
    return false;
}
int foo() {
    int src = read();
    int dst = genDst();
    if(src == dst)
        return 0;
    std::map<int, int> A, B;
    std::vector<int> curA, curB;
    curA.push_back(src);
    curB.push_back(dst);
    A[src] = B[dst] = 0;
    for(int i = 1; i <= 8; ++i) {
        if(extend(i, curA, A, B))
            return i * 2 - 1;
        if(i != 8 && extend(i, curB, B, A))
            return i * 2;
    }
    return -1;
}
int main() {
    int n;
    scanf("%d", &n);
    while(n--)
        printf("%d\n", foo());
    return 0;
}
