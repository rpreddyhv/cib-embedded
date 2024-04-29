#pragma once

#include <cstdint>

namespace lib::mmio
{
    template <typename RegisterT, std::size_t Msb, std::size_t Lsb, typename DataTypeT = RegisterT::DataType>
    struct Field
    {
        using DataType = DataTypeT;
        using Register = RegisterT;
        constexpr static auto value = DataType{};

        constexpr auto operator()(DataType const &value)
        {
            return mask & (value << Msb);
        }

    private:
        constexpr static DataType mask = ((1 << Msb) - 1) & ((1 << Lsb) - 1);
    };
}
