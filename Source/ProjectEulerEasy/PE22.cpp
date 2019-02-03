#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
std::string read() {
    std::string res;
    int c;
    do {
        c = getchar();
        if(c == EOF)
            throw c;
    } while(c < 'A' || c > 'Z');
    while('A' <= c && c <= 'Z') {
        res.push_back(c);
        c = getchar();
    }
    return res;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
int main() {
    freopen("p022_names.txt", "r", stdin);
    std::vector<std::string> str;
    try {
        while(true)
            str.push_back(read());
    } catch(...) {
    }
    printf("read %d\n", static_cast<int>(str.size()));
    std::sort(str.begin(), str.end());
    Int64 res = 0;
    const char off = 'A' - 1;
    for(size_t i = 0; i < str.size(); ++i) {
        Int64 val = 0;
        for(int j = 0; j < str[i].size(); ++j)
            val += str[i][j] - off;
        res += (i + 1) * val;
    }
    printf("%lld\n", res);
    return 0;
}
