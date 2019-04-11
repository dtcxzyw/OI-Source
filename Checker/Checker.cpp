#include "OJAdapter.hpp"
#include "Platforms/Platform.hpp"
#include "Runner.hpp"
#include "Scanner.hpp"
#include <iostream>
int main() {
    initPlatform();
    std::cout.precision(2);
    std::cout << std::fixed;

    line("Checker " VERSION, '*');
    std::cout << "Built at " << __TIME__ << " on "
              << __DATE__ << std::endl;
    platformInfo();
    if(needUpdate())
        std::cout << "\033[33mThe checker is "
                     "out-of-date.\033[0m"
                  << std::endl;
    fs::path exec = scanExec();
    std::cout << "found program:" << exec << std::endl;
    autoRun(exec);
    line("", '*');
    return 0;
}
