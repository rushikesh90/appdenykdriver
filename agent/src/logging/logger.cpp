#include "logger.h"

#include <iostream>

namespace execguard {

void Logger::Init() {
    // stub
}

void Logger::Info(const std::string& msg) {
    std::cerr << "[INFO] " << msg << "\n";
}

void Logger::Error(const std::string& msg) {
    std::cerr << "[ERROR] " << msg << "\n";
}

} // namespace execguard
