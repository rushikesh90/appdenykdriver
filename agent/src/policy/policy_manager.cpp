#include "policy_manager.h"

#include "logging/logger.h"

namespace execguard {

bool PolicyManager::LoadFromFile(const std::string& path) {
    Logger::Info(std::string("Loading policy: ") + path);
    return true;
}

} // namespace execguard
