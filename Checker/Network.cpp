#include "Network.hpp"
bool download(const std::string& url,
              const fs::path& dst) {
    std::cout << "Downloading file " << url
              << std::endl;
    line("wget");
    std::string cmd = "wget --dns-timeout=20 "
                      "--connect-timeout=20 "
                      "--read-timeout=600 "
                      "--tries=5 -v "
                      "--no-use-server-"
                      "timestamps -O " +
        dst.string() + " " + url;
    std::cout << cmd << std::endl;
    int res = system(cmd.c_str());
    line("");
    return res == 0;
}
