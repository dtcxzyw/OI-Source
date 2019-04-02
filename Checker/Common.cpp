#include "Common.hpp"
#include <chrono>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
std::string file2Str(const fs::path& path) {
    std::ifstream in(path);
    using Iter = std::istream_iterator<char>;
    return { Iter(in), Iter() };
}
void showLine(const std::string& col,
              const std::string& str) {
    struct winsize size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    std::cout << '\r' << col << str << "\033[0m"
              << std::string(size.ws_col - str.size(),
                             ' ')
              << std::flush;
}
void line(const std::string& str, char full) {
    std::cout << "\033[36m";
    int mid = std::max(
        3, (46 - static_cast<int>(str.size())) / 2);
    for(int i = 0; i < mid; ++i)
        std::cout.put(full);
    std::cout << str;
    for(int i = 0; i < mid; ++i)
        std::cout.put(full);
    std::cout << "\033[0m" << std::endl;
}
Data::Data(const fs::path& in, const fs::path& out)
    : input(in), output(out) {}
bool Data::operator<(const Data& rhs) const {
    return input < rhs.input;
}
static fs::path uniqueTempFileName() {
    char name[] = "TMP_XXXXXX";
    if(mkstemp(name) == -1)
        throw std::runtime_error(
            "Failed to create temp file.");
    return name;
}
TempFile::TempFile() : mFile(uniqueTempFileName()) {}
fs::path TempFile::path() const {
    return mFile;
}
TempFile::~TempFile() {
    fs::remove(mFile);
}
static void clearCache() {
    if(fs::exists("Cache")) {
        using DirIter = fs::directory_iterator;
        std::vector<fs::path> deferred;
        using Clock = fs::file_time_type::clock;
        using namespace std::chrono;
        auto ct = Clock::now();
        for(auto it : DirIter("Cache")) {
            it.refresh();
            if(!it.is_regular_file())
                continue;
            auto wt = it.last_write_time();
            if(floor<hours>(ct - wt).count() >= 48) {
                std::cout
                    << "Cache " << it.path().stem()
                    << " is up-to-date." << std::endl;
                deferred.push_back(it.path());
            }
        }
        for(auto p : deferred)
            fs::remove(p);
    } else
        fs::create_directory("Cache");
}
static bool verifyZip(const fs::path& file) {
    std::string cmd = "unzip -t -q " + file.string();
    int res = system(cmd.c_str());
    return res == 0;
}
fs::path downloadFile(const std::string& url,
                      const std::string& pid,
                      bool verify) {
    clearCache();
    if(fs::exists(url))
        return url;
    else {
        fs::path cacheFile = "Cache/" + pid;
        if(verify && fs::exists(cacheFile) &&
           !verifyZip(cacheFile))
            fs::remove(cacheFile);
        if(!fs::exists(cacheFile)) {
            std::cout << "Downloading file " << url
                      << std::endl;
            line("wget");
            std::string cmd = "wget --dns-timeout=10 "
                              "--connect-timeout=10 "
                              "--read-timeout=600 "
                              "--tries=1 "
                              "--https-only -v "
                              "--no-use-server-"
                              "timestamps -O Cache/" +
                pid + " " + url;
            int res = system(cmd.c_str());
            line("");
            if(res != 0 ||
               (verify && !verifyZip(cacheFile))) {
                fs::remove(cacheFile);
                return fs::path();
            }
        } else
            std::cout << "Using cached file "
                      << cacheFile << std::endl;
        return cacheFile;
    }
}
bool unzip(const fs::path& path) {
    fs::remove_all("data");
    if(!fs::create_directory("data"))
        return false;
    std::string cmd =
        "unzip -q -j -d data " + path.string();
    int res = system(cmd.c_str());
    return res == 0;
}
std::string readConfig(const std::string& optName) {
    std::ifstream in("checker.config");
    std::string line;
    while(std::getline(in, line)) {
        std::size_t pos = line.find('#');
        std::string key = line.substr(0, pos);
        if(key == optName)
            return line.substr(pos + 1);
    }
    return {};
}
