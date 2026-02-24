#pragma once

#include "backend/ikernel_backend.h"

namespace execguard {

// eBPF LSM backend (user-mode side glue only).
class BpfBackend final : public IKernelBackend {
public:
    std::string Name() const override { return "bpf"; }
    bool Start() override;
    void Stop() override;
};

} // namespace execguard
