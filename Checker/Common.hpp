#pragma once
#include <charconv>
#include <cstdint>
#include <filesystem>
#include <string>
using std::int64_t;
namespace fs = std::filesystem;
std::string file2Str(const fs::path& path);
// Time:us Memory:KB
struct Option final {
    fs::path exec;
    int64_t maxTime, maxMem, compareMode;
};
void line(const std::string& str, char full = '-');
using FT = long double;
constexpr FT eps = 1e-5;
struct Data final {
    fs::path input, output;
    Data(const fs::path& in, const fs::path& out);
    bool operator<(const Data& rhs) const;
};
class TempFile final {
private:
    fs::path mFile;

public:
    TempFile();
    TempFile(const TempFile&) = delete;
    TempFile(TempFile&&) = delete;
    TempFile& operator=(const TempFile&) = delete;
    TempFile& operator=(TempFile&&) = delete;
    fs::path path() const;
    ~TempFile();
};
bool downloadFile(const std::string& url,
                  const fs::path& loc);
bool unzip(const fs::path& path);
template <typename T>
inline T scan(const std::string& str) {
    T res = {};
    std::from_chars(str.c_str(),
                    str.c_str() + str.size(), res);
    return res;
}
