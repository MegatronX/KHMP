#include "AbilityManager.h"
#include <Entity.h>
namespace Game
{
	namespace Abilities
	{
		std::vector<Ability*> EmptyAbilSet;
		AbilityManager::AbilityManager()
		{

		}
		AbilityManager::AbilityManager(Entity* owner) : Component(owner, "AbilityManger" + owner->GetName(), "AbilityManager")
		{

		}

		std::vector<Ability*>& AbilityManager::GetAbilitiesWithCallCondition(const CallCondition cc, bool sortByPriority) const
		{
			return EmptyAbilSet;
		}
		std::vector<Ability*>& AbilityManager::GetAbilitiesWithPriority(const int priority) const
		{
			return EmptyAbilSet;
		}

		std::vector<Ability*> AbilityManager::GetAbilitiesWithComponent(const std::string* compName, bool SortByPriority) const
		{
			return EmptyAbilSet;
		}
		std::vector<Ability*> AbilityManager::GetPositiveStatusEffects(bool SortByPriority) const
		{
			return EmptyAbilSet;
		}
		std::vector<Ability*> AbilityManager::GetNegativeStatusEffects(bool SortByPriority) const
		{
			return EmptyAbilSet;
		}
		void AbilityManager::DistributeXP(const int XP)
		{
			if (AllowXP)
			{

			}
		}
	}
}