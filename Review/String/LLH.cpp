#include <algorithm>
#include <cstdio>
#include <list>
#include <memory>
struct CharInfo {
    int id, cnt, len, code;
} info[10];
int lenCount[10], off[10];
class Node;
using SharedNode = std::shared_ptr<Node>;
using IterT = std::list<SharedNode>::const_iterator;
template <typename... T>
SharedNode makeSharedNode(T&&... args) {
    return std::make_shared<Node>(
        std::forward<T>(args)...);
}
class Node {
private:
    int val;
    SharedNode ls, rs;

public:
    Node(int val) : val(val) {}
    Node(SharedNode ls, SharedNode rs)
        : val(ls->getWeight() + rs->getWeight()),
          ls(ls), rs(rs) {}
    int getWeight() const {
        return ls ? val : info[val].cnt;
    }
    void count() {
        if(ls) {
            ls->count();
            rs->count();
        } else
            ++info[val].len;
    }
};
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if(n > (1 << m))
        return 1;
    for(int i = 0; i < n; ++i) {
        info[i].id = i;
        scanf("%d", &info[i].cnt);
    }
    std::sort(info, info + n, [](const CharInfo& lhs,
                                 const CharInfo& rhs) {
        return lhs.cnt < rhs.cnt;
    });
    std::list<SharedNode> list, stdlist;
    for(int i = 0; i < n; ++i)
        stdlist.emplace_back(makeSharedNode(i));
    list = stdlist;
    for(int i = m; i >= 2; --i) {
        std::list<SharedNode> clist = stdlist;
        std::list<SharedNode> glist;
        IterT it = list.cbegin();
        while(true) {
            IterT a = it++;
            IterT b = it++;
            if(a != list.cend() && b != list.cend()) {
                glist.emplace_back(
                    makeSharedNode(*a, *b));
            } else
                break;
        }
        glist.merge(clist, [](SharedNode lhs,
                              SharedNode rhs) {
            return lhs->getWeight() < rhs->getWeight();
        });
        glist.swap(list);
    }
    IterT it = list.begin();
    int sum = 2 * (n - 1);
    for(int i = 0; i < sum; ++i, ++it)
        (*it)->count();
    for(int i = 0; i < n; ++i)
        ++lenCount[info[i].len];
    for(int i = 1; i < m; ++i)
        off[i + 1] = (off[i] + lenCount[i]) << 1;
    for(int i = 0; i < n; ++i) {
        int len = info[i].len;
        info[i].code = off[len] + (--lenCount[len]);
    }
    std::sort(info, info + n, [](const CharInfo& lhs,
                                 const CharInfo& rhs) {
        return lhs.id < rhs.id;
    });
    for(int i = 0; i < n; ++i) {
        printf("id=%d code=", i);
        for(int j = info[i].len - 1; j >= 0; --j)
            putchar('0' + ((info[i].code >> j) & 1));
        putchar('\n');
    }
    return 0;
}
