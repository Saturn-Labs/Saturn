#include "Utils/UUIDGenerator.hpp"

namespace Saturn {
    UUIDv4::UUIDGenerator<std::mt19937_64> UUIDGenerator::s_Generator = {};
    UUIDv4::UUID UUIDGenerator::GenerateUUID() {
        return s_Generator.getUUID();
    }
}
