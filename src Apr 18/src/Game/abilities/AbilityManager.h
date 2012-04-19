#pragma once
#ifndef _ABILITYMANAGER_H_
#define _ABILITYMANAGER_H_
#include <abilities/Ability.h>
#include <components/Component.h>
namespace Game
{
	class Entity;
	namespace Abilities
	{
		class AbilityHolder
		{
		public:
			AbilityHolder(abil_ptr ability, bool APFree = false, bool AutoEquipped = false, bool Show = true, bool Unequippable = false) : AttachedAbility(ability), APFree(APFree), AutoEquipped(AutoEquipped), Show(Show), Unequippable(Unequippable)
			{

			}
			abil_ptr AttachedAbility;
			bool APFree;
			bool AutoEquipped;
			bool Show;
			bool Unequippable;
		};
		class AbilityManager : public Components::Component
		{
		public:
			AbilityManager();
			AbilityManager(Entity* owner);
			std::vector<Ability*>& GetAbilitiesWithCallCondition(const CallCondition cc, bool sortByPriority = false) const;
			std::vector<Ability*>& GetAbilitiesWithPriority(const int priority) const;

			std::vector<Ability*> GetAbilitiesWithComponent(const std::string* compName, bool SortByPriority = false) const;
			std::vector<Ability*> GetPositiveStatusEffects(bool SortByPriority = false) const;
			std::vector<Ability*> GetNegativeStatusEffects(bool SortByPriority = false) const;
			void DistributeXP(const int XP);
		private:
			boost::unordered_map<std::string, AbilityHolder> PermanentAbilities;
			boost::unordered_map<std::string, AbilityHolder> UnlearnedAbilities;
			bool AllowXP;
		};
	}
}

#endif