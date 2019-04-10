#include "Common.hpp"
#include <chrono>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#ifdef __WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#endif
#include <vector>
std::string file2Str(const fs::path& path) {
    std::ifstream in(path);
    if(fs::is_regular_file(path)) {
        in.seekg(0, std::ios::end);
        auto siz = in.tellg();
        if(siz <= 0)
            return "";
        in.seekg(0, std::ios::beg);
        std::vector<char> data(siz);
        in.read(data.data(), siz);
        return std::string(data.data(),
                           data.data() + siz);
    } else {
        std::string res;
        while(in)
            res.push_back(in.get());
        return res;
    }
}
static int getConsoleWidth() {
#ifdef __WIN32
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwSize.X;
#else
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
#endif
}
void showLine(const std::string& col,
              const std::string& str) {
    std::cout << '\r' << col << str << "\033[0m"
              << std::string(getConsoleWidth() -
                                 str.size(),
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
    static std::mt19937_64 dev(
        std::chrono::high_resolution_clock::now()
            .time_since_epoch()
            .count());
    return fs::temp_directory_path() /
        std::to_string(dev());
}
TempFile::TempFile() : mFile(uniqueTempFileName()) {}
fs::path TempFile::path() const {
    return mFile;
}
TempFile::~TempFile() {
    try {
        fs::remove(mFile);
    } catch(...) {
    }
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
            std::cout << cmd << std::endl;
            int res = system(cmd.c_str());
            line("");
            if(res != 0 ||
               (verify && !verifyZip(cacheFile))) {
                if(fs::exists(cacheFile))
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
    fs::path dst = fs::temp_directory_path() / "data";
    fs::remove_all(dst);
    if(!fs::create_directory(dst))
        return false;
    std::string cmd = "unzip -q -j -d " +
        dst.string() + " " + path.string();
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
