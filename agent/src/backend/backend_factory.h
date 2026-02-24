#pragma once

#include "backend/ikernel_backend.h"

#include <string>

namespace execguard {

class BackendFactory {
public:
    // Config-driven backend selection.
    // NOTE: no kernel-specific headers should be included here.
    static IKernelBackendPtr Create(const std::string& backendName);
};

} // namespace execguard
