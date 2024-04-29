#pragma once

#include <cstdint>

namespace lib::mmio
{
    template <typename Register>
    constexpr static auto write(Register const &reg, typename Register::DataType const &value) -> void
    {
        const volatile auto address = reinterpret_cast<volatile std::uintptr_t *>(reg.address);
        *address = value;
    }

    template <typename Register>
    constexpr static auto read(Register const &reg) -> typename Register::DataType
    {
        const volatile auto address = reinterpret_cast<volatile std::uintptr_t *>(reg.address);
        return static_cast<Register::DataType>(*address);
    }
}
