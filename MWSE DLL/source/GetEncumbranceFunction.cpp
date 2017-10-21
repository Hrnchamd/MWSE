#include "GetEncumbranceFunction.h"

#include <set>

#include "TES3OFFSETS.h"
#include "TES3TYPES.h"
#include "VMTYPES.h"

bool GetEncumbranceFunction::execute(void)
{
	enum Encumbrance
	{
		kCurrent = 0,
		kMax = 1,
		kBase = 2
	};
	long encumbrance_type;
	double encumbrance = -1.0;
	unsigned long record_type;
	VPVOID reference, temp, base;
	if (GetTargetData(machine, &reference, &temp, &record_type, &base)
		&& (record_type == NPC || record_type == CREATURE)) {
		MACPRecord const* const macp =
			reinterpret_cast<MACPRecord*>(GetAttachPointer(
			machine, reference, MACHNODE));
		machine.pop(encumbrance_type);
		if (macp != NULL) {
			if (encumbrance_type == kCurrent) {
				encumbrance = macp->weight_limit.current;
			} else if (encumbrance_type == kMax) {
				encumbrance = macp->weight_limit.base;
			} else if (encumbrance_type == kBase) {
				encumbrance = macp->weight_limit.current;
				if (macp->num_active_effects > 0) {
					// first effect is a "dummy" node
					MACPRecord::ActiveEffect* current_effect =
						macp->active_effects->next;
					for (int i = 0; i < macp->num_active_effects; i++) {
						if (current_effect->effect_type == kFeather) {
							encumbrance += current_effect->magnitude;
						} else if (current_effect->effect_type == kBurden) {
							// Burden is modified by Magicka Resistance
							// we must take into account any MR that was active
							// when Burden went into effect.
							char* name;
							GetOffsetData(machine, base?base:temp, 0x1c,
								reinterpret_cast<unsigned long*>(&name));
							name_ = name;
							unsigned long address = 0x7C67DC;
							unsigned long* pointer =
								reinterpret_cast<unsigned long*>(address);
							address = (*pointer) + 0x70;
							pointer =
								reinterpret_cast<unsigned long*>(address);
							address = (*pointer) + 0xC;
							pointer =
								reinterpret_cast<unsigned long*>(address);
							address = *pointer;
							SPLLNode const* const root =
								reinterpret_cast<SPLLNode*>(address);
							address = 0x7C7C8C;
							pointer =
								reinterpret_cast<unsigned long*>(address);
							address = *pointer;
							SPLLNode const* const leaf =
								reinterpret_cast<SPLLNode*>(address);
							visited_.clear();
							visited_.insert(root);
							visited_.insert(leaf);
							encumbrance -= SearchForBurden(root->first);
							encumbrance -= SearchForBurden(root->second);
							encumbrance -= SearchForBurden(root->third);
						}
						current_effect = current_effect->next;
					}
				}
			}
		}
	}
	float value = static_cast<float>(encumbrance);
	return (machine.push(value));
}

double GetEncumbranceFunction::SearchForBurden(SPLLNode const* const node)
{
	if (node == NULL || visited_.count(node) != 0) return 0.0;
	unsigned long pointer = reinterpret_cast<unsigned long>(node);
	double burden = 0.0;
	visited_.insert(node);
	SPLLRecord const* const active_spell = node->spll_record;
	if (active_spell != NULL) {
		pointer = reinterpret_cast<unsigned long>(active_spell);
		SPELRecord const* const spell = active_spell->spell;
		for (int effect = 0; effect < 8; effect++) {
			if (spell->effects[effect].effectId == kBurden) {
				unsigned long size = active_spell->effects[effect].size;
				unsigned long found = 0;
				SPLLRecord::ActiveSpell const* const* const active_spells =
					active_spell->effects[effect].active_spells;
				for (int index = 0; index < size; index++) {
					SPLLRecord::ActiveSpell const* const current_spell =
						active_spells[index];
					if (current_spell != NULL &&
						name_ == current_spell->id) {
						burden += current_spell->magnitude *
							(100.0 - current_spell->statistic) / 100.0;
						found++;
					}
					if (found == active_spell->effects[effect].in_use)
						break;
				}
			}
		}
	}
	burden += SearchForBurden(node->first);
	burden += SearchForBurden(node->second);
	burden += SearchForBurden(node->third);
	return burden;
}