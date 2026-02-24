#pragma once

#include <string>

namespace execguard {

class PolicyManager {
public:
    bool LoadFromFile(const std::string& path);
};

} // namespace execguard
