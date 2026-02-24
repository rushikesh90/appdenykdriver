#pragma once

#include <memory>
#include <string>

namespace execguard {

// Clean backend abstraction: user-mode agent depends only on this interface.
class IKernelBackend {
public:
    virtual ~IKernelBackend() = default;
    virtual std::string Name() const = 0;
    virtual bool Start() = 0;
    virtual void Stop() = 0;
};

using IKernelBackendPtr = std::unique_ptr<IKernelBackend>;

} // namespace execguard
