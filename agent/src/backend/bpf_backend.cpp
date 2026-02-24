#include "bpf_backend.h"

#include "logging/logger.h"

namespace execguard {

bool BpfBackend::Start() {
    Logger::Info("Starting BPF backend (stub)");
    return true;
}

void BpfBackend::Stop() {
    Logger::Info("Stopping BPF backend (stub)");
}

} // namespace execguard
