#include "../../Common.hpp"
#include "../Platform.hpp"
#include <cstdlib>
#include <iostream>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
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
void reportJudgeError(const RunResult& res) {
    if(res.st == Status::RE) {
        if(res.ret == RuntimeError::NonzeroExitCode)
            std::cout << "[Exited with code "
                      << res.sig << "]";
        else if(res.sig != -1) {
            std::cout << "[SIG=" << res.sig << ":"
                      << strsignal(res.sig) << "]";
        }
        std::cout << "(" << toString(res.ret) << ") "
                  << std::endl;
    }
    if(res.st == Status::SE || res.st == Status::UKE)
        std::cout << "(" << std::strerror(errno)
                  << ") " << std::endl;
}
static std::string getCallTableName() {
#ifdef __i386__
#define FileName "unistd_32.h"
#elif defined(__ILP32__)
#define FileName "unistd_x32.h"
#else
#define FileName "unistd_64.h"
#endif
    return "/usr/include/i386-linux-gnu/asm/" FileName;
#undef FileName
}
std::string getCallName(long callid) {
    static std::string LUT =
        file2Str(getCallTableName());
    std::regex pattern(
        "#define\\s*__NR_([a-z0-9_]*)\\s*" +
            std::to_string(callid) + "\\s*#",
        regexFlag4Search);
    std::smatch match;
    std::regex_search(LUT, match, pattern);
    if(match.size() == 2)
        return match[1].str();
    return "Unknown";
}
int getConsoleWidth() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}
