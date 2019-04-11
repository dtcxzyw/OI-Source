#include "Judger.hpp"
#include "Platforms/Platform.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
static std::string newline(std::string str) {
    while(str.size() &&
          (str.back() == '\n' || str.back() == '\r'))
        str.pop_back();
    str.push_back('\n');
    return str;
}
template <typename T>
static bool
compareImpl(const fs::path& out, const fs::path& stdi,
            const fs::path& stdo,
            const std::function<bool(const T&,
                                     const T&)>& cmp) {
    std::ifstream outf(out), stdof(stdo);
    using Iter = std::istream_iterator<T>;
    if(std::equal(Iter(outf), Iter(), Iter(stdof),
                  Iter(), cmp))
        return true;
    if(std::max(fs::file_size(out),
                fs::file_size(stdo)) <= 100) {
        auto ins = file2Str(stdi);
        if(ins.size() > 97) {
            ins.resize(97);
            ins += "...";
        }
        std::cout << "input: " << newline(ins);
        std::cout << "std: "
                  << newline(file2Str(stdo));
        std::cout << "user: "
                  << newline(file2Str(out));
        std::cout.flush();
    }
    return false;
}
static bool compare(CompareMode mode,
                    const fs::path& out,
                    const fs::path& stdi,
                    const fs::path& stdo, FT& maxErr) {
    switch(mode) {
        case CompareMode::Text: {
            return compareImpl<std::string>(
                out, stdi, stdo,
                std::equal_to<std::string>());
        } break;
        case CompareMode::FloatingPoint: {
            auto cmp = [&maxErr](FT a, FT b) {
                if(!std::isfinite(a) ||
                   !std::isfinite(b))
                    return false;
                FT err = std::min(fabsl(a - b),
                                  fabsl(a - b) / b);
                maxErr = std::max(maxErr, err);
                return err < eps;
            };
            return compareImpl<FT>(out, stdi, stdo,
                                   cmp);
        }
        default:
            std::cout << "Unknown Comparer"
                      << std::endl;
            break;
    }
    return false;
}
RunResult test(const Option& opt, const Data& data,
               const Timer& timer) {
    line("Running Task " + data.input.stem().string());
    if(timer.isTLE()) {
        RunResult res;
        res.st = Status::SKIPPED;
        std::cout << "Result " << toString(res.st)
                  << std::endl;
        return res;
    }
    TempFile tmpOutput;
    RunResult res =
        run(opt, timer, data.input, tmpOutput.path());
    if(res.st == Status::AC &&
       !compare(opt.get<CompareMode>(
                    "CompareMode", CompareMode::Text),
                tmpOutput.path(), data.input,
                data.output, res.maxErr))
        res.st = Status::WA;
    std::cout << "Result " << toString(res.st) << " "
              << res.time / 1000.0 << " ms "
              << res.mem / 1024.0 << " MB"
              << std::endl;
    reportJudgeError(res);
    return res;
}
