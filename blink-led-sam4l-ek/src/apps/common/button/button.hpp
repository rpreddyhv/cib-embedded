
#pragma once

namespace apps::common::button {
	
	template <typename Gpio>
	struct Button {
		private:
		//using ButtonGpio = gpio::Gpio<PinNumber, gpio::Direction::INPUT>;
		
		public:
		constexpr static auto init() -> void {
			Gpio::init();
		}
		
		constexpr static auto isPressed() -> bool {
			return !Gpio::get();
		}
	};
}
