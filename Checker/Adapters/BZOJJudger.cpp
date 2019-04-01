#include "../Judger.hpp"
#include "../OJAPI.hpp"
#include "../OJAdapter.hpp"
#include "../Scanner.hpp"
#include "../Timer.hpp"
#include <iostream>
static bool readOpt(Option& opt,
                    const std::string& str) {
    std::string title;
    {
        std::regex pattern("<title>(\\S+)</title>",
                           regexFlag4Search);
        std::smatch match;
        std::regex_search(str, match, pattern);
        if(match.size() == 2)
            title = match[1].str();
        else
            return false;
    }
    int64_t maxTime = 0;
    {
        std::regex pattern(
            "[：|</span>]([0-9]+)[s|Sec]",
            regexFlag4Search);
        std::smatch match;
        std::regex_search(str, match, pattern);
        if(match.size() == 2)
            maxTime = scan<int64_t>(match[1].str());
        else
            return false;
    }
    int64_t maxMem = 0;
    {
        std::regex pattern("([0-9]+)MB",
                           regexFlag4Search);
        std::smatch match;
        std::regex_search(str, match, pattern);
        if(match.size() == 2)
            maxMem = scan<int64_t>(match[1].str());
        else
            return false;
    }
    if(maxTime == 0 || maxMem == 0)
        return false;
    std::cout << "\033[34m";
    std::cout << "Title:BZOJ" << title << std::endl;
    std::cout << "Time Limit:" << maxTime << " Sec"
              << std::endl;
    std::cout << "Memory Limit:" << maxMem << " MB"
              << std::endl;
    std::cout << "Compare Mode:Text";
    std::cout << "\033[0m" << std::endl;
    opt.insert("TimeMode", TimeMode::allTask);
    opt.insert("TimeVal", TimeVal::totTime);
    opt.insert("TimeLimit", maxTime * 1000000);
    opt.insert("MemoryLimit", maxMem << 10);
    opt.insert("CompareMode", CompareMode::Text);
    opt.insert("TimeSamples",
               fs::path("BZOJ-Samples"));
    return true;
}
static bool runBZOJ(const fs::path& exec) {
    line("Loading Problem Info");
    std::string execName =
        exec.stem().string().substr(4);
    int id = scan<int>(execName);
    Option opt;
    opt.insert("Exec", exec);
    std::string problem;
    if(!loadProblemInfo("BZOJ", id, problem))
        return false;
    if(!readOpt(opt, problem))
        return false;
    auto data = scanData("data");
    runAll(opt, data);
    return true;
}
static OJAdapterInfo
    reg("BZOJ-Judger",
        std::regex("(BZOJ|bzoj)[0-9]+\\w*",
                   regexFlag4Match),
        runBZOJ);
