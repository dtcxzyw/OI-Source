#pragma once
#include "Common.hpp"
#include <vector>
std::vector<Data>
scanData(const fs::path& dataPath =
             fs::temp_directory_path() / "data");
fs::path scanExec();
