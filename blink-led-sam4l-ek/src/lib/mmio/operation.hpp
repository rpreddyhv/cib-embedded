#pragma once

#include <cstdint>

namespace lib::mmio
{
    template <typename Field>
    constexpr inline auto set(Field const &field) -> void
    {
        constexpr auto reg = typename Field::Register{};
        const volatile auto address = reinterpret_cast<volatile std::uintptr_t *>(reg.address);
        auto const readValue =  static_cast<Field::DataType>(*address);
        auto const updatedValue = readValue | field();
        *address = updatedValue;
    }

    template <typename Field>
    constexpr inline auto clear(Field const &field) -> void
    {
        constexpr auto reg = typename Field::Register{};
        const volatile auto address = reinterpret_cast<volatile std::uintptr_t *>(reg.address);
        auto const readValue =  static_cast<Field::DataType>(*address);
        auto const updatedValue = readValue & ~(field());
        *address = updatedValue;
    }

    template <typename Register>
    constexpr inline auto write(Register const &reg, typename Register::DataType const &value) -> void
    {
        const volatile auto address = reinterpret_cast<volatile std::uintptr_t *>(reg.address);
        *address = value;
    }

    template <typename Field>
    constexpr inline auto write(Field const &field) -> void
    {
        constexpr auto reg = typename Field::Register{};
        const volatile auto address = reinterpret_cast<volatile std::uintptr_t *>(reg.address);
        auto const readValue =  static_cast<Field::DataType>(*address);
        auto const updatedValue = readValue | field();
        *address = updatedValue;
    }

    template <typename Register>
    constexpr inline auto read(Register const &reg) -> typename Register::DataType
    {
        const volatile auto address = reinterpret_cast<volatile std::uintptr_t *>(reg.address);
        return static_cast<Register::DataType>(*address);
    }

    // template <typename... Operations>
    // constexpr inline auto apply(Operations const &...ops)
    // {
    //     (ops, ...);
    // }
}
