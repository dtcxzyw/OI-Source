#include "Scanner.hpp"
#include <algorithm>
#include <map>
#include <set>
using DirIter = fs::directory_iterator;
std::vector<Data> scanData(const fs::path& dir) {
    std::map<fs::path, fs::path> in, out;
    std::vector<Data> res;
    for(DirIter it(dir); it != DirIter(); ++it)
        if(it->status().type() ==
           fs::file_type::regular) {
            auto cp = it->path(), name = cp.stem(),
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
    return res;
}
fs::path scanExec() {
    std::set<fs::path> blacklist{ "checker",
                                  "charCounter" };
    fs::file_time_type mft;
    fs::path res;
    for(DirIter it(fs::current_path());
        it != DirIter(); ++it)
        if(it->status().type() ==
           fs::file_type::regular) {
            auto cp = it->path(), name = cp.stem(),
                 ext = cp.extension();
            if(ext != ".out" || blacklist.count(name))
                continue;
            auto cft = fs::last_write_time(cp);
            if(cft > mft)
                mft = cft, res = cp;
        }
    return fs::relative(res);
}
