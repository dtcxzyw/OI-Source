#include "PlatformWindows.hpp"
#include "../../Common.hpp"
#include "../Platform.hpp"
static std::string winerr2String(DWORD code) {
    char buf[1024];
    if(FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL,
                      code, 0, buf, sizeof(buf), 0))
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
        std::to_string(static_cast<DWORD>(cond)) +
        "\nError Message: " + winerr2String(cond) +
        "\nFile: " + mLoc.file_name() +
        "\nFunction: " + mLoc.function_name() +
        "\nLine: " + std::to_string(mLoc.line()) +
        "\n\033[0m";
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
void setCodePage(int codePage) noexcept {
    SetConsoleCP(codePage);
    SetConsoleOutputCP(codePage);
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
static const std::string& getWinntHeader() {
    static std::string str =
        file2Str(readConfig("WinntHeader"));
    return str;
}
static std::string getHexCode(DWORD code) {
    std::stringstream ss;
    ss << std::hex << std::uppercase
       << std::setfill('0') << std::setw(8) << code;
    return "0x" + ss.str();
}
bool isExceptionCode(DWORD code) {
    auto hexCode = getHexCode(code);
    std::regex pattern(
        R"x(#define STATUS_(\S*) \(\(DWORD\))x" +
            hexCode + R"x(\))x",
        regexFlag4Match);
    return std::regex_search(getWinntHeader(),
                             pattern);
}
static std::string
exceptionCode2String(const std::string& hexCode) {
    std::regex pattern(
        R"x(#define STATUS_(\S*) \(\(DWORD\))x" +
            hexCode + R"x(\))x",
        regexFlag4Search);
    std::smatch match;
    std::regex_search(getWinntHeader(), match,
                      pattern);
    if(match.size() == 2) {
        std::string str = match[1].str();
        bool keep = true;
        for(auto& ch : str) {
            if(isalpha(ch)) {
                if(keep)
                    keep = false;
                else
                    ch = tolower(ch);
            } else {
                ch = ' ';
                keep = true;
            }
        }
        return str;
    }
    return "Unknown Error";
}
void reportJudgeError(const RunResult& res) {
    if(res.st == Status::RE) {
        auto hexCode = getHexCode(res.sig);
        if(res.ret == RuntimeError::NonzeroExitCode) {
            std::cout << toString(res.ret)
                      << ":code=" << hexCode
                      << std::endl;
            if(res.sig == 3)
                std::cout
                    << toString(
                           RuntimeError::Exception)
                    << "???" << std::endl;
        } else {
            std::cout
                << "Win32 Exception:[code=" << hexCode
                << "]: "
                << exceptionCode2String(hexCode)
                << std::endl;
        }
    }
}
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    winAssert(GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE), &info));
    return info.dwSize.X;
}
