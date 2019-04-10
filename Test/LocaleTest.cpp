#include <clocale>
#include <iostream>
#include <locale>
#include <mbctype.h>
int main() {
    system("chcp 65001");
    setlocale(LC_ALL, "");
    puts("@我是中国人@@@");
    _putws(L"@我是中国人@@@");
    // std::locale loc("");
    // std::locale::global(loc);
    // std::cout << loc.name() << std::endl;
    std::cout << "@我是中国人@@@" << std::endl;
    std::wcout << u"@我是中国人@@@" << std::endl;
    std::cin.get();
    return 0;
}
