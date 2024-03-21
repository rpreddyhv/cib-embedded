#pragma once

#include "sam.h"

#include "apps/user/flow_names.hpp"

#include "apps/common/button/button.hpp"
#include "hal/driver/gpio/gpio.hpp"

namespace apps::user::button {
    using namespace apps::common::button;
    using namespace apps::user::core;
    
    using ButtonGpio = hal::driver::gpio::Gpio<PIN_PC03, hal::driver::gpio::Direction::INPUT>;
    using InputButton = Button<ButtonGpio>;
    
    struct Component {
        constexpr static auto checkButtonPress() -> void {
            if (InputButton::isPressed()) {
                cib::service<STATUS_LED_ON>();
            } else {
                cib::service<STATUS_LED_OFF>();
            }
        }
        
        constexpr static auto config = cib::config(
            cib::extend<APP_INIT>(&InputButton::init),
            cib::extend<APP_RUN>(&checkButtonPress)
        );
    };
}
