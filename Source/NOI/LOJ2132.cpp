#include <algorithm>
#include <cstdio>
namespace IO {
    const int size = 1 << 21;
    char buf[size], *S = buf;
    void init() {
        fread(buf, 1, size, stdin);
    }
    char getc() {
        return *S++;
    }
}
typedef long long Int64;
Int64 read() {
    Int64 res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
const int size = 100500;
struct Queue {
    Int64 q[size];
    int b, e;
    Queue() : b(0), e(0) {}
    void sort() {
        std::sort(q + b, q + e);
    }
    void push(Int64 c) {
        q[e++] = c;
    }
    void pop() {
        ++b;
    }
    Int64 top() const {
        return b < e ? q[b] : (1LL << 62);
    }
} A, B;
Int64 getNode() {
    Int64 na = A.top(), nb = B.top();
    (na < nb ? A : B).pop();
    return na < nb ? na : nb;
}
int main() {
    IO::init();
    int n = read();
    int k = read();
    int m = (n - 1) % (k - 1),
        pass = (n - 1) / (k - 1);
    if(m) {
        int esiz = k - 1 - m;
        for(int i = 0; i < esiz; ++i)
            A.push(0);
        ++pass;
    }
    for(int i = 0; i < n; ++i)
        A.push(read() << 6);
    A.sort();
    Int64 sumw = 0;
    for(int t = 0; t < pass; ++t) {
        Int64 sw = 0, mh = 0;
        for(int i = 0; i < k; ++i) {
            Int64 c = getNode();
            sw += c >> 6;
            mh = std::max(mh, c & 63);
        }
        sumw += sw;
        B.push(sw << 6 | (mh + 1));
    }
    printf("%lld\n%lld\n", sumw, getNode() & 63);
    return 0;
}
