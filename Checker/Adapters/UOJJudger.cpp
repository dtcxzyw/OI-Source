#include "../Judger.hpp"
#include "../Network.hpp"
#include "../OJAPI.hpp"
#include "../OJAdapter.hpp"
#include "../Scanner.hpp"
#include "../Timer.hpp"
#include <iostream>
static FT readImpl(const std::string& str,
                   const std::string& bak) {
    {
        std::regex pattern("texttt\\{([.0-9]+)" + bak +
                               "\\}",
                           regexFlag4Search);
        std::smatch match;
        std::regex_search(str, match, pattern);
        if(match.size() == 2)
            return scan<FT>(match[1].str());
    }
    {
        std::regex pattern("([.0-9]+)\\\\texttt\\{" +
                               bak + "\\}",
                           regexFlag4Search);
        std::smatch match;
        std::regex_search(str, match, pattern);
        if(match.size() == 2)
            return scan<FT>(match[1].str());
    }
    return 0;
}
static bool readOpt(Option& opt,
                    const std::string& str) {
    std::string title;
    {
        std::regex pattern("<h1 class=\"page-header "
                           "text-center\">([ "
                           "\\S]+)</h1>",
                           regexFlag4Search);
        std::smatch match;
        std::regex_search(str, match, pattern);
        if(match.size() == 2)
            title = "UOJ" + match[1].str();
        else
            return false;
    }
    FT maxTime = readImpl(str, "s");
    int64_t maxMem = readImpl(str, "MB");
    if(maxTime == 0 || maxMem == 0)
        return false;
    std::cout << "\033[34m";
    std::cout << "Title:UOJ" << title << std::endl;
    std::cout << "Time Limit:" << maxTime << " s"
              << std::endl;
    std::cout << "Memory Limit:" << maxMem << " MB"
              << std::endl;
    std::cout << "Compare Mode:Text";
    std::cout << "\033[0m" << std::endl;
    opt.insert("TimeMode", TimeMode::perTask);
    opt.insert("TimeLimit", static_cast<int64_t>(
                                maxTime * 1000000));
    opt.insert("MemoryLimit", maxMem << 10);
    opt.insert("CompareMode", CompareMode::Text);
    return true;
}
static bool runUOJ(const fs::path& exec) {
    line("Loading Problem Info");
    std::string execName =
        exec.stem().string().substr(3);
    int id = scan<int>(execName);
    Option opt;
    opt.insert("Exec", exec);
    std::string problem;
    if(!loadProblemInfo("UOJ", id, problem))
        return false;
    if(!readOpt(opt, problem))
        return false;
    auto data = scanData();
    runAll(opt, data);
    return true;
}
static OJAdapterInfo
    reg("UOJ-Judger", std::regex("(UOJ|uoj)[0-9]+\\S*",
                                 regexFlag4Match),
        runUOJ);
