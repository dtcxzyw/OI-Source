#include <cstdio>
#include <sstream>
#include <string>
int main() {
    std::stringstream ss;
    for(int i = 0; i <= 200000; ++i)
        ss << i;
    std::string str = ss.str();
    int res = 1;
    for(int i = 1; i <= 1000000; i *= 10)
        res *= str[i] - '0';
    printf("%d\n", res);
    return 0;
}
