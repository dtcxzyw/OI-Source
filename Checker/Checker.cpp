#include "OJAdapter.hpp"
#include "Runner.hpp"
#include "Scanner.hpp"
#include <iostream>
#include <locale>
int main() {
    initRunner();
    std::locale::global(std::locale("C.UTF-8"));
    std::cout.precision(2);
    std::cout << std::fixed;

    line("Checker 2.8.0", '*');
    std::cout << "Built at " << __TIME__ << " on "
              << __DATE__ << std::endl;
    platformInfo();
    fs::path exec = scanExec();
    std::cout << "found program:" << exec << std::endl;
    autoRun(exec);
    line("", '*');
    return 0;
}
