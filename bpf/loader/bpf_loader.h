#pragma once

#include <string>

namespace execguard {

class BpfLoader {
public:
    bool LoadObjectFile(const std::string& objPath);
    bool AttachLsm();
    void Detach();
};

} // namespace execguard
