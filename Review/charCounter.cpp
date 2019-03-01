#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
int main() {
    std::locale::global(std::locale(""));
    system("pdftotext ../latex/Main.pdf");
    std::wifstream in("../latex/Main.txt");
    int cntA = 0, cntB = 0;
    while(in) {
        wchar_t c = in.get();
        if(iswgraph(c)) {
            ++cntA;
            if(0x4E00 <= c && c <= 0x9FA5)
                ++cntB;
        }
    }
    std::wofstream out("../latex/charcnt");
    out << cntA << "(" << cntB << ")" << std::flush;
    return 0;
}
