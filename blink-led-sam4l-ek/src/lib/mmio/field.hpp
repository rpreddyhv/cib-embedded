#pragma once

#include <cstdint>

namespace lib::mmio
{
    template <typename RegisterT, std::size_t Msb, std::size_t Lsb, typename DataTypeT = RegisterT::DataType>
    struct Field
    {
        using DataType = DataTypeT;
        using Register = RegisterT;

        constexpr auto operator()(DataType const &toUpdate)
        {
            value = mask & (toUpdate << Lsb);
        }

        constexpr static auto operator()()
        {
            return mask;
        }

    private:
        constexpr static DataType mask = ((1 << (Msb + 1)) - 1) & ~((1 << Lsb) - 1);
        DataType value{};
    };
}
