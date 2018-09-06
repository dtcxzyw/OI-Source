#include <cctype>
#include <cstdlib>
#include <fstream>
#include <locale>
int main() {
    std::locale::global(std::locale(""));
    system("pdftotext ../latex/Main.pdf");
    std::wifstream in("../latex/Main.txt");
    int cnt = 0;
    while(in) {
        wchar_t c = in.get();
        if(iswgraph(c))
            ++cnt;
    }
    std::wofstream out("../latex/charcnt");
    out << cnt << std::flush;
    return 0;
}
