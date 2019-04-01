#pragma once
#include "Runner.hpp"
enum class CompareMode { Text, FloatingPoint };
RunResult test(const Option& opt, const Data& data,
               const Timer& timer);
