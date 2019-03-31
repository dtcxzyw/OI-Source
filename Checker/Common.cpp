#include "Common.hpp"
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
std::string file2Str(const fs::path& path) {
    std::ifstream in(path);
    using Iter = std::istream_iterator<char>;
    return { Iter(in), Iter() };
}
void line(const std::string& str, char full) {
    std::cout << "\033[36m";
    int mid = (36 - str.size()) / 2;
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
bool downloadFile(const std::string& url,
                  const fs::path& loc) {
    if(fs::exists(url))
        return fs::copy_file(url, loc);
    else {
        std::string cmd =
            "wget -q -O " + loc.string() + " " + url;
        int res = system(cmd.c_str());
        return res == 0;
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
