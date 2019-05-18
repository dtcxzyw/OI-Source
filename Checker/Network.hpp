#pragma once
#include "Common.hpp"
bool access(const std::string& url,
            const std::string& name);
bool download(const std::string& url,
              const fs::path& dst);
