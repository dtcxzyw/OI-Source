#pragma once
#include <any>
#include <charconv>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <map>
#include <regex>
#include <string>
using std::int64_t;
namespace fs = std::filesystem;
std::string file2Str(const fs::path& path);
class Option final {
private:
    std::map<std::string, std::any> options;

public:
    template <typename T>
    void insert(const std::string& key, const T& val) {
        options.emplace(key, std::any(val));
    }
    template <typename T>
    T get(const std::string& key, const T& def) const {
        auto it = options.find(key);
        if(it != options.end())
            return std::any_cast<T>(it->second);
        else {
            std::cout
                << "Warning:Failed to get option "
                << key << std::endl;
            return def;
        }
    }
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
fs::path downloadFile(const std::string& url,
                      const std::string& pid,
                      bool verifyZip);
bool unzip(const fs::path& path);
template <typename T>
inline T scan(const std::string& str) {
    T res = {};
    std::from_chars(str.c_str(),
                    str.c_str() + str.size(), res);
    return res;
}
constexpr auto regexFlag4Search =
    std::regex_constants::ECMAScript |
    std::regex_constants::optimize |
    std::regex_constants::__polynomial;
constexpr auto regexFlag4Match =
    regexFlag4Search | std::regex_constants::nosubs;
std::string readConfig(const std::string& optName);
