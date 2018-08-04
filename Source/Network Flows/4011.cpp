//TODO:"P4011"
#include <cstdio>
#include <cstring>
#include <vector>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
class State {
   private:
    int val;
    State(int val) : val(val) {}

   public:
    State(int x, int y, int s) : val(((x << 4) | y) << 11 | s) {}
    State addKey(int id) const {
        return State(val | 1 << id);
    }
    bool haveKey(int id) const {
        return val & (1 << id);
    }
    State move(int ox, int oy) const {
        int sx = val >> 15, sy = (val >> 11) & 15, ss = val & ((1 << 11) - 1);
        return State(sx + ox, sy + oy, ss);
    }
};
int map[15][15][2];
std::vector<int> key[15][15];
int main() {
    int n = read();
    int m = read();
    int p = read() + 1;
    int k = read();
    while (k--) {
        int x1 = read();
        int y1 = read();
        int x2 = read();
        int y2 = read();
        int g = read();
        if (g == 0) g = p;
        if (x1 == x2 && y1 > y2) std::swap(y1, y2);
        if (y1 == y2 && x1 > x2) std::swap(x1, x2);
        if (x1 == x2)
            map[x1][y1][1] = g;
        else
            map[x1][y1][0] = g;
    }
    int cs = 0;
    std::vector<State> st;
    st.push_back(State(1, 1, cs));
    int t = 1;
    while (true) {
        ++t;
        for ()
    }
    printf("%d\n", t);
    return 0;
}
