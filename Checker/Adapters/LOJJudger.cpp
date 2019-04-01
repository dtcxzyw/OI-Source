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
        std::regex pattern(
            "<h1class=\"uiheader\">(\\S+)</h1>",
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
        std::regex pattern("([0-9]+)ms</span>",
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
        std::regex pattern("([0-9]+)MiB</span>",
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
    CompareMode compareMode =
        (str.find("SpecialJudge") == str.npos ?
             CompareMode::Text :
             CompareMode::FloatingPoint);
    std::cout << "\033[34m";
    std::cout << "Title:LOJ" << title << std::endl;
    std::cout << "Time Limit:" << maxTime << " ms"
              << std::endl;
    std::cout << "Memory Limit:" << maxMem << " MiB"
              << std::endl;
    std::cout << "Compare Mode:"
              << (compareMode ==
                          CompareMode::FloatingPoint ?
                      "Floating Point" :
                      "Text");
    std::cout << "\033[0m" << std::endl;
    opt.insert("TimeMode", TimeMode::perTask);
    opt.insert("TimeVal", TimeVal::totTime);
    opt.insert("TimeLimit", maxTime * 1000);
    opt.insert("MemoryLimit", maxMem << 10);
    opt.insert("CompareMode", compareMode);
    opt.insert("TimeSamples", fs::path("LOJ-Samples"));
    return true;
}
static bool runLOJ(const fs::path& exec) {
    line("Loading Problem Info");
    std::string execName =
        exec.stem().string().substr(3);
    int id = scan<int>(execName);
    execName = std::to_string(id);
    Option opt;
    opt.insert("Exec", exec);
    std::string problem;
    if(!loadProblemInfo("LOJ", id, problem))
        return false;
    if(!readOpt(opt, problem))
        return false;
    runAll(opt, scanData("data"));
    return true;
}
static OJAdapterInfo
    reg("LOJ-Judger", std::regex("(LOJ|loj)[0-9]+\\w*",
                                 regexFlag4Match),
        runLOJ);
