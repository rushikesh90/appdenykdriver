#pragma once

#include "backend/ikernel_backend.h"

namespace execguard {

// Traditional kernel module backend (user-mode side glue only).
class LsmBackend final : public IKernelBackend {
public:
    std::string Name() const override { return "lsm"; }
    bool Start() override;
    void Stop() override;
};

} // namespace execguard
