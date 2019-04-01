#pragma once
#include "Common.hpp"
#include <functional>
#include <regex>
class OJAdapterInfo final {
private:
    std::string mName;
    std::regex mPattern;
    std::function<bool(const fs::path&)> mFunc;
    int mPriority;

public:
    OJAdapterInfo(
        const std::string& name,
        const std::regex& pattern,
        const std::function<bool(const fs::path&)>&
            func,
        int priority = 0);
    bool match(const fs::path& exec) const;
    bool call(const fs::path& exec) const;
    std::string name() const;
    bool operator<(const OJAdapterInfo& rhs) const;
};
void autoRun(const fs::path& exec);
bool runAll(const Option& opt,
            const std::vector<Data>& data);
