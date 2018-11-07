#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
int compare(int id, const std::string& exec) {
    std::string sid = std::to_string(id);
    auto in = "data/" + sid + ".in";
    auto stdo = "data/" + sid + ".out";
    std::ifstream stdof(stdo);
    if(!stdof)
        return 2;
    auto out = "tmp.out";
    auto cmd = "./" + exec + " <" + in + " >" + out;
    system(cmd.c_str());
    std::ifstream outf(out);
    using Iter = std::istream_iterator<int>;
    return std::equal(Iter(outf), Iter(),
                      Iter(stdof)) ?
        1 :
        0;
}
int main() {
    std::string name;
    std::cin >> name;
    int c1 = 0, c2 = 0;
    while(true) {
        ++c1;
        int res = compare(c1, name + ".out");
        if(res == 2)
            break;
        printf("%d %s\n", c1, res ? "AC" : "WA");
        c2 += res;
    }
    printf("Score:%d\n", c2 * 100 / (c1 - 1));
    return 0;
}
