#include "StatusEffectsManager.h"
#include <Entity.h>
#include <algorithm>

namespace Game
{
	namespace StatusEffects
	{
		StatusEffectsLibrary* StatusEffectsManager::SELibrary;
		StatusEffectsManager::StatusEffectsManager(Entity* owner) : Component(owner, "StatusEffectsManager" + owner->GetName(), "StatusEffectsManager")
		{

		}

		void StatusEffectsManager::AddStatusEffect(StatusEffect* se, const int turns)
		{
			AddStatusEffect(se_ptr(se), turns);
		}
		void StatusEffectsManager::AddStatusEffect(se_ptr se, const int turns)
		{
			if (se.get() != nullptr)
			{
				NameToSE[se->GetName()] = se;
				PriorityToSE[se->GetPriority()].push_back(se.get());
				for (auto cc = se->CallConditions.begin(); cc != se->CallConditions.end(); ++cc)
				{
					CallConditionToSE[*cc].push_back(se.get());
				}
				se->SetRemainingTicks(turns);
			}
		}
		void StatusEffectsManager::AddStatusEffect(const std::string& effectName, int turns)
		{
			AddStatusEffect(SELibrary->GetStatusEffectClone(effectName), turns);
		}

		bool StatusEffectsManager::RemoveStatusEffect(const std::string& name)
		{
			bool removed = false;
			return removed;
		}
		void StatusEffectsManager::RemoveStatusEffects(const int count, bool AtRandom)
		{

		}
		void StatusEffectsManager::RemoveNegativeStatusEffects(const int count, bool AtRandom)
		{

		}
		void StatusEffectsManager::RemovePositiveStatusEffects(const int count, bool AtRandom)
		{

		}



		se_ptr StatusEffectsManager::GetStatusEffect(const std::string& name) const
		{
			return se_ptr();
		}
		std::vector<StatusEffect*> EmptySE;
		std::vector<StatusEffect*>& StatusEffectsManager::GetStatusEffectsWithCallCondition(const CallCondition cc, bool sort)
		{
			auto it = CallConditionToSE.find(cc);
			if (it != CallConditionToSE.end())
			{
				return (it->second);
			}
			else
			{
				return EmptySE;
			}
		}
		
		std::vector<StatusEffect*>& StatusEffectsManager::GetStatusEffectsWithPriority(const int priority)
		{
			auto it = PriorityToSE.find(priority);
			if (it != PriorityToSE.end())
			{
				return (it->second);
			}
			else
			{
				return EmptySE;
			}
		}

		std::vector<StatusEffect*> StatusEffectsManager::GetStatusEffectsWithComponent(const std::string* compName, bool SortByPriority) const
		{
			std::vector<StatusEffect*> matches;
			for (auto it = NameToSE.begin(); it != NameToSE.end(); ++it)
			{
			}
			if (SortByPriority)
			{
				std::sort(matches.begin(), matches.end(), [](const StatusEffect* se1, const StatusEffect* se2){ return se1->GetPriority() < se2->GetPriority();});
			}
			return matches;
		}
		std::vector<StatusEffect*> StatusEffectsManager::GetPositiveStatusEffects(bool SortByPriority) const
		{
			std::vector<StatusEffect*> matches;
			return matches;
		}
		std::vector<StatusEffect*> StatusEffectsManager::GetNegativeStatusEffects(bool SortByPriority) const
		{
			std::vector<StatusEffect*> matches;
			return matches;
		}
		void StatusEffectsManager::HandleCharacterTicked(int ticks)
		{

		}
		void StatusEffectsManager::HandleTimeElapsed(const int time)
		{

		}

		float StatusEffectsManager::GetStatusResistance(const std::string& name) const
		{
			auto it = SEResistances.find(name);
			if (it != SEResistances.end())
				return it->second;
			return 0.f;
		}
		float StatusEffectsManager::GetStatusResistance(const StatusEffect* effect) const
		{
			if (effect != nullptr)
				return GetStatusResistance(effect->GetName());
			return 0.f;
		}
		float StatusEffectsManager::GetStatusResistance(se_ptr effect) const
		{
			if (effect.get() != nullptr)
				return GetStatusResistance(effect->GetName());
			return 0.f;
		}

		void StatusEffectsManager::IncrementStatusResistance(const std::string& name, const float inc)
		{
			auto it = SEResistances.find(name);
			if (it != SEResistances.end())
			{
				it->second += inc;
			}
			else
			{
				SEResistances[name] = inc;
			}
		}
		void StatusEffectsManager::IncrementStatusResistance(const StatusEffect* effect, const float inc)
		{
			if (effect != nullptr)
				IncrementStatusResistance(effect->GetName(), inc);
		}
		void StatusEffectsManager::IncrementStatusResistance(se_ptr effect, const float inc)
		{
			if (effect.get() != nullptr)
				IncrementStatusResistance(effect->GetName(), inc);
		}
	}
}