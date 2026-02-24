#include "config_loader.h"

#include <cstdlib>

namespace execguard {

AgentConfig ConfigLoader::LoadFromEnvOrDefault() {
    AgentConfig cfg;
    const char* v = std::getenv("EXECGUARD_BACKEND");
    cfg.backend = (v && *v) ? std::string(v) : std::string("lsm");
    return cfg;
}

} // namespace execguard
