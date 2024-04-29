
#pragma once

namespace apps::common::led
{

	template <typename Gpio>
	struct Led
	{
		constexpr static auto init() -> void
		{
			Gpio::init();
		}

		constexpr static auto blink() -> void
		{
			Gpio::set();
			for (int i = 0; i < 5000; i++)
			{
			}
			Gpio::clear();
			for (int i = 0; i < 5000; i++)
			{
			}
		}

		constexpr static auto on() -> void
		{
			Gpio::set();
		}

		constexpr static auto off() -> void
		{
			Gpio::clear();
		}
	};
}
