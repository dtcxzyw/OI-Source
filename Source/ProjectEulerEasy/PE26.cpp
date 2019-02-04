#include <cstdio>
#include <map>
int main() {
    int maxc = 0, maxi = 0;
    for(int i = 1; i < 1000; ++i) {
        int c = 1, cc = 0, cnt = 0;
        std::map<int, int> r;
        while(c) {
            ++cc;
            c = c * 10 % i;
            if(r.count(c)) {
                cnt = cc - r[c];
                break;
            } else
                r[c] = cc;
        }
        printf("%d %d\n", i, cnt);
        if(cnt > maxc)
            maxc = cnt, maxi = i;
    }
    printf("%d\n", maxi);
    return 0;
}
