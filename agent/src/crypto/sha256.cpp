#include "sha256.h"

#include <sstream>
#include <iomanip>

namespace execguard {

// NOTE: Placeholder implementation. Replace with a real SHA-256 for production.
std::array<uint8_t, 32> Sha256::Digest(const void* data, size_t len) {
    (void)data; (void)len;
    std::array<uint8_t, 32> out{};
    // deterministic non-crypto stub
    for (size_t i = 0; i < out.size(); i++) out[i] = static_cast<uint8_t>(i);
    return out;
}

std::string Sha256::Hex(const std::array<uint8_t, 32>& d) {
    std::ostringstream oss;
    for (auto b : d) oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    return oss.str();
}

} // namespace execguard
