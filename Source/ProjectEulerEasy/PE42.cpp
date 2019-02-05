#include <cstdio>
#include <string>
int read() {
    int res = 0, c;
    do {
        c = getchar();
        if(c == EOF)
            throw c;
    } while(c < 'A' || c > 'Z');
    while('A' <= c && c <= 'Z') {
        const int off = 'A' - 1;
        res += c - off;
        c = getchar();
    }
    return res;
}
bool flag[2000];
int main() {
    freopen("p042_words.txt", "r", stdin);
    for(int i = 1; i <= 40; ++i)
        flag[i * (i + 1) / 2] = true;
    int res = 0;
    try {
        while(true)
            res += flag[read()];
    } catch(...) {
    }
    printf("%d\n", res);
    return 0;
}
