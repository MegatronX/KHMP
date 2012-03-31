#pragma once
#ifndef _ABILITY_H_
#define _ABILITY_H_
#include <statuseffects/StatusEffect.h>
namespace Game
{
	namespace Abilities
	{
		class Ability : public StatusEffects::StatusEffect
		{
		public:
			Ability(Character::BaseCharacter* owner, const std::string& name, int priority);
			virtual RawClonePtr RawClone() const override;
			int GetAPCost() const;
		private:
			int APCost;
			int Instances;
			int RequiredXP;
			static boost::unordered_map<std::string, boost::unordered_map<std::string, int> > APCostOverrides;
			static boost::unordered_map<std::string, boost::unordered_map<std::string, int> > RequiredXPOverrides;
		};

		typedef boost::shared_ptr<Ability> abil_ptr;
	}
}

#endif