
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
		constexpr static auto GPER = lib::mmio::Register<portOffset | GPIO_GPER_OFFSET>{};
		// constexpr static auto GPER = portOffset | GPIO_GPER_OFFSET;
		constexpr static auto ODER = portOffset | GPIO_ODER_OFFSET;
		constexpr static auto OVR = portOffset | GPIO_OVR_OFFSET;
		constexpr static auto PVR = portOffset | GPIO_PVR_OFFSET;
		constexpr static auto PUER = portOffset | GPIO_PUER_OFFSET;
		constexpr static auto PDER = portOffset | GPIO_PDER_OFFSET;
		constexpr static auto IER = portOffset | GPIO_IER_OFFSET;
		constexpr static auto STER = portOffset | GPIO_STER_OFFSET;

	public:
		constexpr static auto init() -> void
		{
			auto const gper = lib::mmio::read(GPER);
			auto const updateGper = gper | (1 << pin);
			lib::mmio::write(GPER, updateGper);
			//*((unsigned int *)GPER) |= (1 << pin);

			if constexpr (DirectionT == Direction::OUTPUT)
			{
				*((unsigned int *)ODER) |= (1 << pin);
				*((unsigned int *)OVR) |= (1 << pin);
			}

			if constexpr (DirectionT == Direction::INPUT)
			{
				*((unsigned int *)ODER) &= ~(1 << pin);
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
			return (*(unsigned int *)PVR) & (1 << pin);
		}

		constexpr static auto set() -> void
		{
			(*(unsigned int *)OVR) |= (1 << pin);
		}

		constexpr static auto clear() -> void
		{
			(*(unsigned int *)OVR) &= ~(1 << pin);
		}
	};
}
