#include "Scanner.hpp"
#include "Platforms/Platform.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
using DirIter = fs::directory_iterator;
std::vector<Data> scanData(const fs::path& dataPath) {
    if(!fs::exists(dataPath))
        return {};
    std::map<fs::path, fs::path> in, out;
    std::vector<Data> res;
    for(auto it : DirIter(dataPath)) {
        it.refresh();
        if(!it.is_regular_file())
            continue;
        auto cp = it.path(), name = cp.stem(),
             ext = cp.extension();
        if(!cp.has_extension() || ext == ".in") {
            if(out.count(name))
                res.push_back(Data(cp, out[name]));
            else
                in[name] = cp;
        } else if(ext == ".out" || ext == ".a" ||
                  ext == ".ans") {
            if(in.count(name))
                res.push_back(Data(in[name], cp));
            else
                out[name] = cp;
        }
    }
    std::sort(res.begin(), res.end());
    line("Auto Scan Result");
    std::cout << "task count:" << res.size()
              << std::endl;
    {
        uintmax_t maxInput = 0, maxOutput = 0;
        for(auto d : res) {
            maxInput = std::max(
                maxInput, fs::file_size(d.input));
            maxOutput = std::max(
                maxOutput, fs::file_size(d.output));
        }
        std::cout << "maxInput:"
                  << maxInput / 1048576.0 << " MB"
                  << std::endl;
        std::cout << "maxOutput:"
                  << maxOutput / 1048576.0 << " MB"
                  << std::endl;
    }
    return res;
}
fs::path scanExec() {
    std::set<fs::path> blacklist{ "checker",
                                  "charCounter" };
    fs::file_time_type mft;
    fs::path res;
    for(auto it : DirIter(fs::current_path())) {
        it.refresh();
        if(!it.is_regular_file())
            continue;
        auto cp = it.path(), name = cp.stem(),
             ext = cp.extension();
        if(ext != ".out" || blacklist.count(name))
            continue;
        auto cft = fs::last_write_time(cp);
        if(cft > mft)
            mft = cft, res = cp;
    }
    return fs::relative(res);
}
bool needUpdate() {
    fs::path self = selfPath();
    auto selfTime = fs::last_write_time(self);
    for(auto p :
        fs::recursive_directory_iterator(SOURCE_DIR)) {
        p.refresh();
        if(p.is_regular_file() &&
           p.last_write_time() > selfTime)
            return true;
    }
    return false;
}
