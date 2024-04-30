
#pragma once

#include "sam.h"
#include <cstdint>
#include "lib/mmio/mmio.hpp"

namespace hal::driver::gpio
{

	enum Direction
	{
		INPUT,
		OUTPUT
	};
	enum Interrupt
	{
		RISING_EDGE,
		FALLING_EDGE,
		HIGH,
		LOW
	};
	enum Input
	{
		POLLING,
		INTERRUPT
	};
	enum PullUpDown
	{
		PULL_UP,
		PULL_DOWN
	};

	template <
		std::size_t PinNumber,
		Direction DirectionT = Direction::OUTPUT,
		Input InputT = Input::POLLING,
		Interrupt InterruptT = Interrupt::HIGH,
		PullUpDown PullUpDownT = PullUpDown::PULL_UP>
	struct Gpio
	{
	private:
		constexpr static auto port = PinNumber / 32;
		constexpr static auto pin = PinNumber % 32;
		constexpr static auto portIndex = (0x200 * port);

		constexpr static auto portOffset = GPIO_ADDR | portIndex;
		using GPER = lib::mmio::Register<portOffset | GPIO_GPER_OFFSET>;
		// constexpr static auto GPER = portOffset | GPIO_GPER_OFFSET;
		constexpr static auto ODER = lib::mmio::Register<portOffset | GPIO_ODER_OFFSET>{};
		// constexpr static auto ODER = portOffset | GPIO_ODER_OFFSET;
		using OVR = lib::mmio::Register<portOffset | GPIO_OVR_OFFSET>;
		// constexpr static auto OVR = portOffset | GPIO_OVR_OFFSET;
		constexpr static auto PVR = lib::mmio::Register<portOffset | GPIO_PVR_OFFSET>{};
		// constexpr static auto PVR = portOffset | GPIO_PVR_OFFSET;
		constexpr static auto PUER = portOffset | GPIO_PUER_OFFSET;
		constexpr static auto PDER = portOffset | GPIO_PDER_OFFSET;
		constexpr static auto IER = portOffset | GPIO_IER_OFFSET;
		constexpr static auto STER = portOffset | GPIO_STER_OFFSET;

		constexpr static auto GPER_BIT = lib::mmio::Field<GPER, pin, pin>{};
		constexpr static auto OVR_BIT = lib::mmio::Field<OVR, pin, pin>{};

	public:
		constexpr static auto init() -> void
		{
			lib::mmio::set(GPER_BIT);
			// auto const gper = lib::mmio::read(GPER);
			// auto const updateGper = gper | (1 << pin);
			// lib::mmio::write(GPER, updateGper);

			//*((unsigned int *)GPER) |= (1 << pin);

			if constexpr (DirectionT == Direction::OUTPUT)
			{
				auto const oder = lib::mmio::read(ODER);
				auto const updateOder = oder | (1 << pin);
				lib::mmio::write(ODER, updateOder);
				// *((unsigned int *)ODER) |= (1 << pin);

				lib::mmio::set(OVR_BIT);
				// auto const ovr = lib::mmio::read(OVR);
				// auto const updateOvr = ovr | (1 << pin);
				// lib::mmio::write(OVR, updateOvr);
				// *((unsigned int *)OVR) |= (1 << pin);
			}

			if constexpr (DirectionT == Direction::INPUT)
			{
				auto const oder = lib::mmio::read(ODER);
				auto const updateOder = oder & ~(1 << pin);
				lib::mmio::write(ODER, updateOder);
				// *((unsigned int *)ODER) &= ~(1 << pin);

				*((unsigned int *)STER) |= (1 << pin);

				// if constexpr (PullUpDownT == PULL_DOWN) {
				//*((unsigned int *)PDER) |= (1 << pin);
				//*((unsigned int *)PUER) &= ~(1 << pin);
				//}
				//
				// if constexpr (PullUpDownT == PULL_UP) {
				//*((unsigned int *)PDER) &= ~(1 << pin);
				//*((unsigned int *)PUER) |= (1 << pin);
				//}
				// if constexpr (InputT == Input::INTERRUPT) {
				//
				//}
			}
		}

		constexpr static auto get() -> bool
		{
			return lib::mmio::read(PVR);
			// return (*(unsigned int *)PVR) & (1 << pin);
		}

		constexpr static auto set() -> void
		{
			lib::mmio::set(OVR_BIT);
			// auto const ovr = lib::mmio::read(OVR);
			// auto const updateOvr = ovr | (1 << pin);
			// lib::mmio::write(OVR, updateOvr);
			// (*(unsigned int *)OVR) |= (1 << pin);
		}

		constexpr static auto clear() -> void
		{
			lib::mmio::clear(OVR_BIT);
			// auto const ovr = lib::mmio::read(OVR);
			// auto const updateOvr = ovr & ~(1 << pin);
			// lib::mmio::write(OVR, updateOvr);
			// (*(unsigned int *)OVR) &= ~(1 << pin);
		}
	};
}
