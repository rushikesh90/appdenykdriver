#pragma once

#include <string>

namespace execguard {

class Logger {
public:
    static void Init();
    static void Info(const std::string& msg);
    static void Error(const std::string& msg);
};

} // namespace execguard
