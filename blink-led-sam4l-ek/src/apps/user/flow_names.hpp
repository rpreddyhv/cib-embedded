#pragma once

#include "cib/cib.hpp"

namespace apps::user::core {
	struct APP_INIT : public cib::callback_meta<> {};
	struct APP_RUN : public cib::callback_meta<> {};
	struct BUTTON_PRESS : public cib::callback_meta<> {};
	struct STATUS_LED_ON : public cib::callback_meta<> {};
	struct STATUS_LED_OFF : public cib::callback_meta<> {};
	
	struct Component {
		constexpr static auto config = 
		cib::config(cib::exports<APP_INIT, APP_RUN, BUTTON_PRESS, STATUS_LED_ON, STATUS_LED_OFF>);
	};
}
