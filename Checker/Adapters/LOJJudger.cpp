#include "../Judger.hpp"
#include "../OJAPI.hpp"
#include "../OJAdapter.hpp"
#include "../Scanner.hpp"
#include "../Timer.hpp"
#include <cstdlib>
#include <fstream>
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
#ifdef SYZOJTOOLS
static bool testSYZOJTools(const Option& opt) {
    std::string testCmd = "which syzoj";
    if(system(testCmd.c_str()))
        return false;
    if(fs::exists("data/data.yml"))
        fs::copy_file("data/data.yml", "problem.yml");
    else {
        std::cout << "Using default data.yml"
                  << std::endl;
        std::ofstream out("problem.yml");
        out << "type: traditional" << std::endl;
        out << "cases: auto" << std::endl;
        out << "cases-global:" << std::endl;
        out << "  time-limit: "
            << opt.get<int64_t>("TimeLimit", 0) / 1000
            << "ms" << std::endl;
        out << "  memory-limit: "
            << (opt.get<int64_t>("MemoryLimit", 0) >>
                10)
            << "MB" << std::endl;
    }
    return true;
}
static std::string findSource(const fs::path& exec) {
    using DirIterT = fs::recursive_directory_iterator;
    fs::path src, root = readConfig("SrcDir");
    for(auto p : DirIterT(root)) {
        p.refresh();
        if(p.is_regular_file() &&
           p.path().stem() == exec.stem() &&
           p.path().extension() == ".cpp") {
            if(src.empty() ||
               fs::last_write_time(p.path()) >
                   fs::last_write_time(src))
                src = p.path();
        }
    }
    std::cout << "Found source file "
              << fs::relative(src, root) << std::endl;
    return fs::relative(src);
}
static bool callSYZOJTools(const fs::path& exec) {
    std::string cmd = "syzoj judge " +
        findSource(exec) + " --show-testcases";
    int res = system(cmd.c_str());
    std::cout << "syzoj-tools exited with code=" << res
              << std::endl;
    return res == 0;
}
#endif
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
#ifdef SYZOJTOOLS
    if(testSYZOJTools(opt)) {
        std::cout << "Using syzoj-tools" << std::endl;
        return callSYZOJTools(exec);
    }
#endif
    runAll(opt, scanData("data"));
    return true;
}
static OJAdapterInfo
    reg("LOJ-Judger", std::regex("(LOJ|loj)[0-9]+\\w*",
                                 regexFlag4Match),
        runLOJ);
