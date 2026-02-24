#include "backend_factory.h"

#include "backend/bpf_backend.h"
#include "backend/lsm_backend.h"

#include <stdexcept>

namespace execguard {

IKernelBackendPtr BackendFactory::Create(const std::string& backendName) {
    if (backendName == "bpf") {
        return std::make_unique<BpfBackend>();
    }
    if (backendName == "lsm") {
        return std::make_unique<LsmBackend>();
    }
    throw std::runtime_error("Unknown backend: " + backendName);
}

} // namespace execguard
