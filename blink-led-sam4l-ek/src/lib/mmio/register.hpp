#pragma once

#include <cstdint>

namespace lib::mmio
{
    template <std::size_t Address, typename DataT = std::uint32_t>
    struct Register
    {
        constexpr static auto address = Address;
        using DataType = DataT;
    };
}
