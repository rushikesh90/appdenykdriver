#include "bpf_loader.h"

namespace execguard {

bool BpfLoader::LoadObjectFile(const std::string& objPath) {
    (void)objPath;
    return true;
}

bool BpfLoader::AttachLsm() {
    return true;
}

void BpfLoader::Detach() {
}

} // namespace execguard
