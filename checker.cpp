#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
using Clock = std::chrono::high_resolution_clock;
int64_t totTime = 0;
int compare(int id, const std::string& exec,
            const std::string& app) {
    auto sid = app + std::to_string(id);
    auto in = "data/" + sid + ".in";
    auto stdo = "data/" + sid + ".out";
    std::ifstream stdof(stdo);
    if(!stdof) {
        stdo = "data/" + sid + ".ans";
        stdof.open(stdo);
        if(!stdof)
            return 2;
    }
    auto out = "tmp.out";
    auto cmd = "./" + exec + " <" + in + " >" + out;
    auto beg = Clock::now();
    int res = system(cmd.c_str());
    totTime += (Clock::now() - beg).count();
    if(res != 0)
        return 0;
    std::ifstream outf(out);
    using Iter = std::istream_iterator<std::string>;
    bool flag =
        std::equal(Iter(outf), Iter(), Iter(stdof));
    outf.seekg(std::ios::beg);
    stdof.seekg(std::ios::beg);
    flag &=
        std::equal(Iter(stdof), Iter(), Iter(outf));
    return flag;
}
int main() {
    std::string name, app;
    std::cin >> name >> app;
    if(app == "null")
        app.clear();
    int c1 = 0, c2 = 0;
    while(true) {
        ++c1;
        int res = compare(c1, name + ".out", app);
        if(res == 2)
            break;
        printf("%d %s\n", c1, res ? "AC" : "WA");
        c2 += res;
    }
    if(c1 != 1) {
        printf("Score:%d\n", c2 * 100 / (c1 - 1));
        double t = totTime *
            static_cast<double>(std::milli::den) /
            static_cast<double>(Clock::period::den);
        printf("%.0lf ms\n", t);
    } else
        puts("No Input!!!");
    return 0;
}
