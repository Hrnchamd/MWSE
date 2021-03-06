#pragma once

#include "NIObject.h"

namespace NI {
	struct ObjectNET : Object {
		char * name; // 0x8
		void * extraData; // 0xC
		void * controllers; // 0x10
	};
	static_assert(sizeof(ObjectNET) == 0x14, "NI::ObjectNET failed size validation");
}
