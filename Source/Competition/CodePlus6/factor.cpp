#include <cctype>
#include <cstdio>
#include <set>
#include <vector>
const int size = 1000005;
char buf[size * 6];
int encode(int x) {
    return (buf[x] * 1000 + buf[x + 1]) * 1000 +
        buf[x + 2];
}
int main() {
    int m;
    scanf("%d", &m);
    m *= 6;
    int c;
    do
        c = getchar();
    while(!isprint(c));
    for(int i = 1; i <= m; ++i) {
        buf[i] = c;
        c = getchar();
    }
    std::set<int> id;
    for(int i = 1; i <= m; i += 3)
        id.insert(encode(i));
    int n = id.size();
    std::vector<int> fac;
    for(int i = 2; i <= n; ++i)
        if(n % i == 0) {
            do {
                n /= i, fac.push_back(i);
            } while(n % i == 0);
        }
    printf("%d\n", static_cast<int>(fac.size()));
    for(int i = 0; i < fac.size(); ++i)
        printf("%d\n", fac[i]);
    return 0;
}
