#include <cstdio>
#include <set>
namespace IO {
    const int size = 1 << 25;
    char in[size];
    void init() {
        fread(in, 1, size, stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[size], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = IO::getc();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return flag ? -res : res;
}
struct Node {
    mutable int b, e;
    explicit Node(int b, int e = 0) : b(b), e(e) {}
    bool operator<(const Node& rhs) const {
        return b < rhs.b;
    }
};
std::set<Node> A;
typedef std::set<Node>::iterator IterT;
void add(int p) {
    IterT it = A.upper_bound(Node(p)), cur;
    if(it == A.begin())
        cur = A.insert(it, Node(p, p + 1));
    else {
        IterT nxt = it;
        --it;
        if(it->e <= p) {
            if(it->e == p) {
                ++it->e;
                cur = it;
            } else
                cur = A.insert(nxt, Node(p, p + 1));
        } else if(it->b == p) {
            it->b = it->e++;
            cur = it;
        } else {
            int old = it->e;
            it->e = p;
            cur = A.insert(nxt, Node(old, old + 1));
        }
    }
    IterT nxt = cur;
    ++nxt;
    if(nxt != A.end() && nxt->b == cur->e) {
        cur->e = nxt->e;
        A.erase(nxt);
    }
}
void sub(int p) {
    IterT it = A.upper_bound(Node(p));
    if(it == A.begin()) {
        A.insert(it, Node(p, it->b));
        if(++it->b == it->e)
            A.erase(it);
    } else {
        IterT pre = it;
        --pre;
        if(pre->e <= p) {
            if(pre->e == p)
                pre->e = it->b;
            else
                A.insert(it, Node(p, it->b));
            if(++it->b == it->e)
                A.erase(it);
        } else {
            if(pre->e - pre->b == 1)
                A.erase(pre);
            else if(pre->b == p)
                ++pre->b;
            else {
                int old = pre->e;
                pre->e = p;
                if(p + 1 < old)
                    A.insert(it, Node(p + 1, old));
            }
        }
    }
}
bool query(int p) {
    IterT it = A.upper_bound(Node(p));
    if(it == A.begin())
        return false;
    --it;
    return it->e > p;
}
int main() {
    IO::init();
    int n = read();
    read(), read(), read();
    for(int i = 0; i < n; ++i)
        if(read() == 1) {
            int a = read();
            int b = read();
            if(a >= 0) {
                for(int j = 0; j < 30; ++j)
                    if(a & (1 << j))
                        add(j + b);
            } else {
                a = -a;
                for(int j = 0; j < 30; ++j)
                    if(a & (1 << j))
                        sub(j + b);
            }
        } else {
            int k = read();
            IO::putc(query(k) ? '1' : '0');
            IO::putc('\n');
        }
    IO::uninit();
    return 0;
}
