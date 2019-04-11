#include <cstdio>
#include <windows.h>
int main() {
    system("chcp 936");
    char buf[1024] = {};
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL,
                   EXCEPTION_STACK_OVERFLOW, 0, buf,
                   sizeof(buf), 0);
    // puts(buf);
    while(FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
                         NULL, GetLastError(), 0, buf,
                         sizeof(buf), 0) == 0)
        puts("XXX");
    puts(buf);
    const char* str = R"(
#include <winnt.h>
                      )";
    puts(str);
    return 0;
}
