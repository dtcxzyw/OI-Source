#include "OJAdapter.hpp"
#include "Scanner.hpp"
#include <charconv>
#include <iostream>
static bool readOpt(Option& opt,
                    const std::string& str) {
    std::string title;
    {
        std::regex pattern(
            "<h1class=\"uiheader\">(\\S+)</h1>");
        std::smatch match;
        std::regex_search(str, match, pattern);
        if(match.size() == 2)
            title = match[1].str();
        else
            return false;
    }
    {
        std::regex pattern("([0-9]+)ms</span>");
        std::smatch match;
        std::regex_search(str, match, pattern);
        if(match.size() == 2)
            opt.maxTime =
                scan<int64_t>(match[1].str());
        else
            return false;
    }
    {
        std::regex pattern("([0-9]+)MiB</span>");
        std::smatch match;
        std::regex_search(str, match, pattern);
        if(match.size() == 2)
            opt.maxMem = scan<int64_t>(match[1].str());
        else
            return false;
    }
    if(opt.maxTime == 0 || opt.maxMem == 0)
        return false;
    opt.compareMode =
        (str.find("SpecialJudge") == str.npos ? 0 : 1);
    std::cout << "Title:LOJ" << title << std::endl;
    std::cout << "Time Limit:" << opt.maxTime << " ms"
              << std::endl;
    std::cout << "Memory Limit:" << opt.maxMem
              << " MiB" << std::endl;
    std::cout << "Compare Mode:"
              << (opt.compareMode ? "Floating Point" :
                                    "Text")
              << std::endl;
    opt.maxTime *= 1000, opt.maxMem <<= 10;
    return true;
}
static bool runLOJ(const fs::path& exec) {
    line("Loading Problem Info");
    std::string execName =
        exec.stem().string().substr(3);
    int id = scan<int>(execName);
    execName = std::to_string(id);
    std::string purl =
        "https://loj.ac/problem/" + execName;
    TempFile problem;
    if(!downloadFile(purl, problem.path()))
        return false;
    Option opt;
    opt.exec = exec;
    if(!readOpt(opt, file2Str(problem.path())))
        return false;
    TempFile testData;
    std::string turl = purl + "/testdata/download";
    if(!downloadFile(turl, testData.path()))
        return false;
    if(!unzip(testData.path()))
        return false;
    runAll(opt, scanData("data"));
    return true;
}
static OJAdapterInfo
    reg("LOJJudger", std::regex("(LOJ|loj)[0-9]+\\w*"),
        runLOJ);
