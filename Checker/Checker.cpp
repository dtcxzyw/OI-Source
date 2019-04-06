#include "OJAdapter.hpp"
#include "Runner.hpp"
#include "Scanner.hpp"
#include <iostream>
int main() {
    std::cout.precision(2);
    std::cout << std::fixed;

    line("Checker 2.7.0", '*');
    std::cout << "Built at " << __TIME__ << " on "
              << __DATE__ << std::endl;
    fs::path exec = scanExec();
    std::cout << "found program:" << exec << std::endl;
    initRunner();
    autoRun(exec);
    line("", '*');
    return 0;
}
