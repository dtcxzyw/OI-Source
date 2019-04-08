#include "Runner.hpp"
RunResult::RunResult()
    : time(0), mem(0), syscallcnt(0), st(Status::UKE),
      ret(RuntimeError::Unknown), sig(-1),
      maxErr(0.0) {}
std::string toString(Status st) {
    switch(st) {
        case Status::AC:
            return "\033[32mAccepted\033[0m";
            break;
        case Status::WA:
            return "\033[31mWrong Answer\033[0m";
            break;
        case Status::MLE:
            return "\033[33mMemory Limit "
                   "Exceeded\033[0m";
            break;
        case Status::TLE:
            return "\033[36mTime Limit "
                   "Exceeded\033[0m";
            break;
        case Status::RE:
            return "\033[35mRuntime Error\033[0m";
            break;
        case Status::UKE:
            return "\033[35mUnknown Error\033[0m";
            break;
        case Status::SE:
            return "\033[35mJudge System Error\033[0m";
            break;
        case Status::SKIPPED:
            return "\033[33mSkipped\033[0m";
            break;
        default:
            throw;
            break;
    }
}
std::string toString(RuntimeError st) {
    switch(st) {
        case RuntimeError::FloatingPointError:
            return "Floating Point Error";
            break;
        case RuntimeError::FloatingPointErrorO2:
            return "(SIGFPE):Floating Point "
                   "Error(-O2?)";
            break;
        case RuntimeError::NonzeroExitCode:
            return "Nonzero Exit Code";
            break;
        case RuntimeError::SegmentationFault:
            return "Segmentation Fault";
            break;
        case RuntimeError::Exception:
            return "Uncaught C++ Exception";
            break;
        case RuntimeError::Unknown:
            return "Unknown";
            break;
        default:
            throw;
            break;
    }
}
