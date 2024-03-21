/*
* blink-led-sam4l-ek.cpp
*
* Created: 07-03-2024 21:53:30
* Author : rajen
*/


#include "sam.h"

#include "apps/user/status_led.hpp"
#include "apps/user/input_button.hpp"
#include "apps/user/flow_names.hpp"

#include "cib/cib.hpp"

using namespace apps::user;

struct sam4l_ek {
    constexpr static auto config = 
        cib::components<
            led::Component,
            core::Component,
            button::Component
        >;
};

cib::nexus<sam4l_ek> nexus{};

int main(void)
{
    nexus.init();
    nexus.service<core::APP_INIT>();
    
    while (1)
    {
        nexus.service<core::APP_RUN>();
    }
}
