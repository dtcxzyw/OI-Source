#include "../Common.hpp"
#include <cstdlib>
#include <iostream>
#include <sys/resource.h>
void platformInfo() {
    system("lsb_release -d");
}
void initPlatform() {
    struct rlimit limit;
    getrlimit(RLIMIT_STACK, &limit);
    limit.rlim_cur = limit.rlim_max;
    std::cout << "Max stack size="
              << (limit.rlim_max == RLIM_INFINITY ?
                      std::string("unlimit") :
                      std::to_string(limit.rlim_max >>
                                     10) +
                          " MB")
              << std::endl;
    setrlimit(RLIMIT_STACK, &limit);
}
fs::path selfPath() {
    return fs::read_symlink("/proc/self/exe");
}
