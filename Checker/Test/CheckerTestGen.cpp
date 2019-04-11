#include <fstream>
#include <iostream>
#include <string>
int main() {
    int n;
    std::cin >> n;
    for(int i = 1; i <= n; ++i) {
        std::string str = "data/" + std::to_string(i);
        std::ofstream in(str + ".in"),
            ans(str + ".ans");
        in << i << std::endl;
        ans << i << std::endl;
    }
    return 0;
}
