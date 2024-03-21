#pragma once

#include "sam.h"

#include "apps/user/flow_names.hpp"

#include "apps/common/led/led.hpp"
#include "hal/driver/gpio/gpio.hpp"

namespace apps::user::led {
    using namespace apps::common::led;
    using namespace apps::user::core;
    
    using LedGpio = hal::driver::gpio::Gpio<PIN_PC10>;
    using StatusLed = Led<LedGpio>;
    
    struct Component {
        constexpr static auto config = cib::config(
            cib::extend<APP_INIT>(&StatusLed::init),
            //cib::extend<core::APP_RUN>(&StatusLed::blink),
            cib::extend<STATUS_LED_ON>(&StatusLed::on),
            cib::extend<STATUS_LED_OFF>(&StatusLed::off)
        );
    };
}
