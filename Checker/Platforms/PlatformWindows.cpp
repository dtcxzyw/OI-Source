#include "PlatformWindows.hpp"
#include "../Common.hpp"
static std::string winerr2String(int cond) {
    char buf[1024];
    if(FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL,
                      cond, 0, buf, sizeof(buf), 0))
        return buf;
    return "Unknown Error";
}
Win32APIError::Win32APIError(const SourceLocation& loc)
    : mLoc(loc) {}
const char* Win32APIError::name() const noexcept {
    return "Win32API";
}
std::string Win32APIError::message(int cond) const
    noexcept {
    return "\033[35mSystem Error:\nError Code: " +
        std::to_string(cond) + "\nError Message: " +
        winerr2String(cond) + "\nFunction: " +
        mLoc.function_name() + "\nLine: " +
        std::to_string(mLoc.line()) + "\n\033[0m";
}
[[noreturn]] void
reportError(const SourceLocation& loc) {
    throw std::system_error(GetLastError(),
                            Win32APIError(loc));
}
Handle::Handle(HANDLE handle,
               const SourceLocation& loc)
    : mHandle(handle) {
    if(handle == INVALID_HANDLE_VALUE ||
       handle == NULL)
        reportError(loc);
}
HANDLE Handle::get() const noexcept {
    return mHandle;
}
Handle::~Handle() {
    CloseHandle(mHandle);
}
void winAssert(WINBOOL res,
               const SourceLocation& loc) {
    if(res == FALSE)
        reportError(loc);
}
void setCodePage(int codePage) {
    winAssert(SetConsoleCP(codePage));
    winAssert(SetConsoleOutputCP(codePage));
}
void initPlatform() {
    HANDLE ohnd = GetStdHandle(STD_OUTPUT_HANDLE);
    if(ohnd == INVALID_HANDLE_VALUE)
        reportError();
    DWORD old = 0;
    winAssert(GetConsoleMode(ohnd, &old));
    winAssert(SetConsoleMode(
        ohnd,
        old | ENABLE_VIRTUAL_TERMINAL_PROCESSING));
    setCodePage(65001);
}
void platformInfo() {
    system("ver");
}
fs::path selfPath() {
    WCHAR buf[256];
    DWORD size = sizeof(buf);
    winAssert(QueryFullProcessImageNameW(
        GetCurrentProcess(), 0, buf, &size));
    return buf;
}
