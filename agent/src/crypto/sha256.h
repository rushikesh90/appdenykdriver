#pragma once

#include <array>
#include <cstdint>
#include <string>

namespace execguard {

class Sha256 {
public:
    static std::array<uint8_t, 32> Digest(const void* data, size_t len);
    static std::string Hex(const std::array<uint8_t, 32>& d);
};

} // namespace execguard
