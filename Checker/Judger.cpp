#include "Judger.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
template <typename T>
static bool compareImpl(
    const fs::path& out, const fs::path& stdo,
    const std::function<bool(const T&, const T&)>&
        cmp) {
    std::ifstream outf(out), stdof(stdo);
    using Iter = std::istream_iterator<T>;
    return std::equal(Iter(outf), Iter(), Iter(stdof),
                      Iter(), cmp);
}
static bool compare(CompareMode mode,
                    const fs::path& out,
                    const fs::path& stdo, FT& maxErr) {
    switch(mode) {
        case CompareMode::Text: {
            return compareImpl<std::string>(
                out, stdo,
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
            return compareImpl<FT>(out, stdo, cmp);
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
                tmpOutput.path(), data.output,
                res.maxErr))
        res.st = Status::WA;
    std::cout << "Result " << toString(res.st) << " ";
    if(res.st == Status::RE) {
        if(res.ret == RuntimeError::NonzeroExitCode)
            std::cout << "[Exited with code "
                      << res.sig << "]";
        else if(res.sig != -1)
            std::cout << "[SIG=" << res.sig
#if !defined(__WIN32)
                      << ":" << strsignal(res.sig)
#endif
                      << "]";
        std::cout << "(" << toString(res.ret) << ") ";
    }
    if(res.st == Status::SE || res.st == Status::UKE)
        std::cout << "(" << std::strerror(errno)
                  << ") ";
    std::cout << timer.choose(res.usrTime,
                              res.totTime) /
            1000.0
              << " ms " << res.mem / 1024.0 << " MB"
              << std::endl;
    std::cout << "SyscallCount=" << res.syscallcnt
              << std::endl;
    return res;
}
