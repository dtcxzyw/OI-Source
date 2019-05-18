#pragma once
#include "CheckerConfig.hpp"
#include <any>
#include <charconv>
#include <cstdint>
#include <experimental/source_location>
#include <filesystem>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
using std::int64_t;
using SourceLocation =
    std::experimental::source_location;
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
void showLine(const std::string& col,
              const std::string& str);
using FT = long double;
constexpr FT eps = 1e-5;
struct Data final {
    fs::path input, output;
    Data(const fs::path& in, const fs::path& out);
    bool operator<(const Data& rhs) const;
};
struct Unmovable {
    Unmovable() = default;
    ~Unmovable() = default;
    Unmovable(const Unmovable&) = delete;
    Unmovable(Unmovable&&) = delete;
    Unmovable& operator=(const Unmovable&) = delete;
    Unmovable& operator=(Unmovable&&) = delete;
};
class TempFile final : private Unmovable {
private:
    fs::path mFile;

public:
    TempFile();
    fs::path path() const;
    ~TempFile();
};
fs::path downloadFile(const std::string& url,
                      const std::string& pid,
                      bool verifyZip);
bool unzip(const fs::path& path);
template <typename T>
inline T scan(const std::string& str) {
    std::stringstream ss(str);
    T res{};
    ss >> res;
    return res;
}
constexpr auto regexFlag4Search =
    std::regex_constants::ECMAScript |
    std::regex_constants::optimize |
    std::regex_constants::__polynomial;
constexpr auto regexFlag4Match =
    regexFlag4Search | std::regex_constants::nosubs;
std::string readConfig(const std::string& optName);
