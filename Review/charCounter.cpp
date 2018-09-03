#include <cstdio>
#include <cstdlib>
int main() {
    freopen("../latex/charcnt", "w", stdout);
    system("pdftotext ../latex/Main.pdf - | wc -w");
    return 0;
}
