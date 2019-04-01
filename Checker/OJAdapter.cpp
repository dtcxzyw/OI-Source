#include "OJAdapter.hpp"
#include <iostream>
#include <vector>
static std::vector<OJAdapterInfo*>& getRef() {
    static std::vector<OJAdapterInfo*> ref;
    return ref;
}
OJAdapterInfo::OJAdapterInfo(
    const std::string& name, const std::regex& pattern,
    const std::function<bool(const fs::path&)>& func,
    int priority)
    : mName(name), mPattern(pattern), mFunc(func),
      mPriority(priority) {
    getRef().push_back(this);
}
bool OJAdapterInfo::match(const fs::path& exec) const {
    return std::regex_match(exec.stem().string(),
                            mPattern);
}
bool OJAdapterInfo::call(const fs::path& exec) const {
    std::cout << "Using \033[33m" << mName << "\033[0m"
              << std::endl;
    return mFunc(exec);
}
std::string OJAdapterInfo::name() const {
    return mName;
}
bool OJAdapterInfo::
operator<(const OJAdapterInfo& rhs) const {
    return mPriority < rhs.mPriority;
}
bool runDefault(const fs::path& exec);
void autoRun(const fs::path& exec) {
    std::vector<OJAdapterInfo*>& ref = getRef();
    std::sort(ref.rbegin(), ref.rend(),
              [](const OJAdapterInfo* a,
                 const OJAdapterInfo* b) {
                  return *a < *b;
              });
    line("Supported OJAdapter");
    for(auto poa : ref)
        std::cout << poa->name() << std::endl;
    line("");
    for(auto poa : ref) {
        if(poa->match(exec)) {
            if(!poa->call(exec)) {
                std::cout
                    << "\033[35mJudge failed , using "
                       "DefaultJudger\033[0m"
                    << std::endl;
                runDefault(exec);
            }
            return;
        }
    }
    std::cout << "\033[35mNo suitable OJAdapter\033[0m"
              << std::endl;
}
