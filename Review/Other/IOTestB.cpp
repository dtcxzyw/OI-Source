#include <cassert>
#include <cstdio>
namespace IO {
    void init() {
        assert(setvbuf(stdin, 0, _IONBF, 0) == 0);
        assert(setvbuf(stdout, 0, _IONBF, 0) == 0);
    }
    const int size = 1 << 23;
    char in[size];
    char getc() {
        static char *S = in, *T = in;
        if(S == T)
            S = in, T = in + fread(in, 1, size, stdin);
        return S == T ? EOF : *S++;
    }
    char out[size], *S = out, *T = out + size;
    void putc(char ch) {
        if(S == T) {
            fwrite(out, size, 1, stdout);
            S = out;
        }
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
#include "IOTest.hpp"
