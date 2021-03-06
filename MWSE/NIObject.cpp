#include "NIObject.h"

#include "NIDefines.h"

#include "NIRTTI.h"

#include <cstring>

namespace NI {
	RTTI * Object::getRunTimeTypeInformation() {
		return vTable.asObject->getRTTI(this);
	}

	Object * Object::createClone() {
		return reinterpret_cast<Object * (__thiscall *)(Object *)>(0x6E9910)(this);
	}

	bool Object::isOfType(RunTimeTypeInformation::RTTI type) {
		return ((unsigned int)vTable.asObject->getRTTI(this) == type);
	}

	bool Object::isInstanceOfType(RunTimeTypeInformation::RTTI type) {
		RTTI * rtti = vTable.asObject->getRTTI(this);
		while (rtti) {
			if ((unsigned int)rtti == type) {
				return true;
			}

			rtti = rtti->baseRTTI;
		}

		return false;
	}
}
