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
    fs::path exec = scanExec();
    std::cout << "found program:" << exec << std::endl;
    autoRun(exec);
    line("", '*');
    return 0;
}
