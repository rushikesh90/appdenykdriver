#include "lsm_backend.h"

#include "logging/logger.h"

namespace execguard {

bool LsmBackend::Start() {
    Logger::Info("Starting LSM backend (stub)");
    return true;
}

void LsmBackend::Stop() {
    Logger::Info("Stopping LSM backend (stub)");
}

} // namespace execguard
