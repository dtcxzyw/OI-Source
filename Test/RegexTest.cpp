#include <iostream>
#include <regex>
#include <string>
int main() {
    std::string str("000VmPeak:270588kBVmSize:");
    std::regex pattern("VmPeak:([0-9]*)kB");
    std::cout << pattern.mark_count() << std::endl;
    std::smatch match;
    std::regex_search(str, match, pattern);
    std::cout << match.size() << std::endl;
    for(auto m : match)
        std::cout << m << std::endl;
    return 0;
}
