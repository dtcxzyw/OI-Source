#include "OJAPI.hpp"
#include "Common.hpp"
bool loadProblemInfo(const std::string& OJ, int id,
                     std::string& problem) {
    std::string purl = readConfig(OJ + "ProblemURL");
    std::regex pattern("@ID@", regexFlag4Search);
    std::string cid = std::to_string(id);
    purl = std::regex_replace(purl, pattern, cid);
    fs::path ploc =
        downloadFile(purl, OJ + "-PR" + cid, false);
    if(!fs::exists(ploc))
        return false;
    problem = file2Str(ploc);
    std::string turl = readConfig(OJ + "TestdataURL");
    turl = std::regex_replace(turl, pattern, cid);
    fs::path testData =
        downloadFile(turl, OJ + "-TD" + cid, true);
    if(!fs::exists(testData))
        return false;
    if(!unzip(testData))
        return false;
    return true;
}
