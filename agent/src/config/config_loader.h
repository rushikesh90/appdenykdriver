#pragma once

#include <string>

namespace execguard {

struct AgentConfig {
    std::string backend; // "lsm" or "bpf"
};

class ConfigLoader {
public:
    // Minimal stub: reads EXECGUARD_BACKEND env var.
    static AgentConfig LoadFromEnvOrDefault();
};

} // namespace execguard
