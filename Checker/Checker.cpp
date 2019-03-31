#include "OJAdapter.hpp"
#include "Runner.hpp"
#include "Scanner.hpp"
#include <iostream>
int main() {
    std::cout.precision(2);
    std::cout << std::fixed;
    initRunner();

    line("Checker 2.6.0", '*');
    std::cout << "Built at " << __TIME__ << " on "
              << __DATE__ << std::endl;
    fs::path exec = scanExec();
    std::cout << "found program:" << exec << std::endl;
    autoRun(exec);
    return 0;
}
