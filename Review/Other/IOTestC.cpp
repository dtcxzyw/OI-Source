#include <cassert>
#include <cstdio>
namespace IO {
    void init() {
        const int size = 1 << 23;
        assert(setvbuf(stdin, 0, _IOFBF, size) == 0);
        assert(setvbuf(stdout, 0, _IOFBF, size) == 0);
    }
    void uninit() {}
    char getc() {
        return getchar();
    }
    void putc(int ch) {
        putchar(ch);
    }
}
#include "IOTest.hpp"
