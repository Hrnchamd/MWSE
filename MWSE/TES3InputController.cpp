#include "TES3InputController.h"

#define TES3_InputController_readKeyState 0x4065E0
#define TES3_InputController_keybindTest 0x406F40

namespace TES3 {
	void InputController::readKeyState() {
		reinterpret_cast<void(__thiscall *)(InputController*)>(TES3_InputController_readKeyState)(this);
	}

	int InputController::keybindTest(unsigned int keyBind, unsigned int transition) {
		return reinterpret_cast<int(__thiscall *)(InputController*, unsigned int, unsigned int)>(TES3_InputController_keybindTest)(this, keyBind, transition);
	}
}
