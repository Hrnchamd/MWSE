#include "TES3CreatureLua.h"

#include "LuaManager.h"
#include "TES3ActorLua.h"

#include "TES3AIConfig.h"
#include "TES3Creature.h"
#include "TES3Item.h"
#include "TES3Script.h"
#include "TES3SpellList.h"

namespace mwse {
	namespace lua {
		void bindTES3Creature() {
			// Get our lua state.
			sol::state& state = LuaManager::getInstance().getState();

			// Binding for TES3::Creature
			{
				// Start our usertype. We must finish this with state.set_usertype.
				auto usertypeDefinition = state.create_simple_usertype<TES3::Creature>();
				usertypeDefinition.set("new", sol::no_constructor);

				// Define inheritance structures. These must be defined in order from top to bottom. The complete chain must be defined.
				usertypeDefinition.set(sol::base_classes, sol::bases<TES3::Actor, TES3::PhysicalObject, TES3::Object, TES3::BaseObject>());
				setUserdataForActor(usertypeDefinition);

				// Basic property binding.
				usertypeDefinition.set("aiConfig", sol::readonly_property(&TES3::Creature::aiConfig));
				usertypeDefinition.set("isInstance", sol::var(false));
				usertypeDefinition.set("soul", &TES3::Creature::soul);
				usertypeDefinition.set("soundCreature", &TES3::Creature::soundGenerator);
				usertypeDefinition.set("spells", sol::readonly_property(&TES3::Creature::spellList));
				usertypeDefinition.set("type", sol::readonly_property(&TES3::Creature::creatureType));

				// Indirect bindings to unions and arrays.
				usertypeDefinition.set("attacks", sol::readonly_property([](TES3::Creature& self) { return std::ref(self.attacks); }));
				usertypeDefinition.set("attributes", sol::readonly_property([](TES3::Creature& self) { return std::ref(self.attributes); }));
				usertypeDefinition.set("skills", sol::readonly_property([](TES3::Creature& self) { return std::ref(self.skills); }));

				// Functions exposed as properties.
				usertypeDefinition.set("fatigue", sol::readonly_property(&TES3::Creature::getFatigue));
				usertypeDefinition.set("health", sol::readonly_property(&TES3::Creature::getDurability));
				usertypeDefinition.set("isAttacked", sol::readonly_property(&TES3::Creature::getIsAttacked));
				usertypeDefinition.set("isEssential", sol::readonly_property(&TES3::Creature::isEssential));
				usertypeDefinition.set("isRespawn", sol::readonly_property(&TES3::Creature::isRespawn));
				usertypeDefinition.set("level", sol::readonly_property(&TES3::Creature::getLevel));
				usertypeDefinition.set("magicka", sol::readonly_property(&TES3::Creature::getMagicka));
				usertypeDefinition.set("model", sol::property(&TES3::Creature::getModelPath, &TES3::Creature::setModelPath));
				usertypeDefinition.set("name", sol::property(&TES3::Creature::getName, &TES3::Creature::setName));
				usertypeDefinition.set("script", sol::readonly_property(&TES3::Creature::getScript));

				// Finish up our usertype.
				state.set_usertype("tes3creature", usertypeDefinition);
			}

			// Binding for TES3::CreatureInstance
			{
				// Start our usertype. We must finish this with state.set_usertype.
				auto usertypeDefinition = state.create_simple_usertype<TES3::CreatureInstance>();
				usertypeDefinition.set("new", sol::no_constructor);

				// Define inheritance structures. These must be defined in order from top to bottom. The complete chain must be defined.
				usertypeDefinition.set(sol::base_classes, sol::bases<TES3::Actor, TES3::PhysicalObject, TES3::Object, TES3::BaseObject>());
				setUserdataForActor(usertypeDefinition);

				// Basic property binding.
				usertypeDefinition.set("equipment", sol::readonly_property(&TES3::CreatureInstance::equipment));
				usertypeDefinition.set("fatigue", sol::readonly_property(&TES3::CreatureInstance::getFatigue));
				usertypeDefinition.set("health", sol::readonly_property(&TES3::CreatureInstance::getDurability));
				usertypeDefinition.set("inventory", sol::readonly_property(&TES3::CreatureInstance::inventory));
				usertypeDefinition.set("isInstance", sol::var(true));
				usertypeDefinition.set("weapon", sol::readonly_property([](TES3::CreatureInstance& self) { return makeLuaObject(self.weapon); }));

				// Properties that directly point to the base creature.
				usertypeDefinition.set("aiConfig", sol::readonly_property([](TES3::CreatureInstance& self) { return self.baseCreature->aiConfig; }));
				usertypeDefinition.set("attacks", sol::readonly_property([](TES3::CreatureInstance& self) { return std::ref(self.baseCreature->attacks); }));
				usertypeDefinition.set("attributes", sol::readonly_property([](TES3::CreatureInstance& self) { return std::ref(self.baseCreature->attributes); }));
				usertypeDefinition.set("baseObject", sol::readonly_property([](TES3::CreatureInstance& self) { return makeLuaObject(self.baseCreature); }));
				usertypeDefinition.set("soul", sol::property(
					[](TES3::CreatureInstance& self) { return self.baseCreature->soul; },
					[](TES3::CreatureInstance& self, int value) { self.baseCreature->soul = value; }
				));
				usertypeDefinition.set("soundCreatureInstance", sol::readonly_property([](TES3::CreatureInstance& self) { return self.baseCreature->soundGenerator; }));
				usertypeDefinition.set("skills", sol::readonly_property([](TES3::CreatureInstance& self) { return std::ref(self.baseCreature->skills); }));
				usertypeDefinition.set("type", sol::readonly_property([](TES3::CreatureInstance& self) { return self.baseCreature->creatureType; }));
				usertypeDefinition.set("spells", sol::readonly_property([](TES3::CreatureInstance& self) { return self.baseCreature->spellList; }));

				// Functions exposed as properties.
				usertypeDefinition.set("barterGold", sol::property(&TES3::CreatureInstance::getBaseBarterGold, &TES3::CreatureInstance::setBaseBarterGold));
				usertypeDefinition.set("isAttacked", sol::readonly_property(&TES3::CreatureInstance::getIsAttacked));
				usertypeDefinition.set("isEssential", sol::readonly_property(&TES3::CreatureInstance::isEssential));
				usertypeDefinition.set("isRespawn", sol::readonly_property(&TES3::CreatureInstance::isRespawn));
				usertypeDefinition.set("level", sol::readonly_property(&TES3::CreatureInstance::getLevel));
				usertypeDefinition.set("magicka", sol::readonly_property(&TES3::CreatureInstance::getMagicka));
				usertypeDefinition.set("model", sol::property(&TES3::CreatureInstance::getModelPath, &TES3::CreatureInstance::setModelPath));
				usertypeDefinition.set("name", sol::property(&TES3::CreatureInstance::getName, &TES3::CreatureInstance::setName));
				usertypeDefinition.set("script", sol::readonly_property(&TES3::CreatureInstance::getScript));

				// DEPRECATED. Will remove.
				usertypeDefinition.set("baseCreature", sol::readonly_property([](TES3::CreatureInstance& self) { return makeLuaObject(self.baseCreature); }));

				// Finish up our usertype.
				state.set_usertype("tes3creatureInstance", usertypeDefinition);
			}
		}
	}
}
