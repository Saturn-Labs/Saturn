#pragma once
#include <uuid_v4.h>

namespace Saturn {
    class UUIDGenerator {
        static UUIDv4::UUIDGenerator<std::mt19937_64> s_Generator;
    public:
        static UUIDv4::UUID GenerateUUID();
    };
}
