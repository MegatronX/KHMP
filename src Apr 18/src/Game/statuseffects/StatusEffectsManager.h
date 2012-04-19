#pragma once
#ifndef _STATUSEFFECTSMANAGER_H_
#define _STATUSEFFECTSMANAGER_H_

#include <boost/unordered_map.hpp>
#include "StatusEffect.h"
#include <components/Component.h>
#include "StatusEffectsLibrary.h"

#define DEFAULT_TURNS 100000

class Entity;

namespace Game
{
	class GameInstance;
	
	namespace StatusEffects
	{
		class StatusEffectsManager : public Components::Component
		{
		public:
			StatusEffectsManager(Entity* owner);
			
			void AddStatusEffect(StatusEffect* se, const int turns);
			void AddStatusEffect(se_ptr se, int turns);
			void AddStatusEffect(const std::string& effectName, int turns);
			
			bool RemoveStatusEffect(const std::string& name);
			void RemoveStatusEffects(const int count, bool AtRandom = true);
			void RemoveNegativeStatusEffects(const int count, bool AtRandom = true);
			void RemovePositiveStatusEffects(const int count, bool AtRandom = true);
			
	

			se_ptr GetStatusEffect(const std::string& name) const;
			std::vector<StatusEffect*>& GetStatusEffectsWithCallCondition(const CallCondition cc, bool sort);
			std::vector<StatusEffect*>& GetStatusEffectsWithPriority(const int priority);
			
			std::vector<StatusEffect*> GetStatusEffectsWithComponent(const std::string* compName, bool SortByPriority = false) const;
			std::vector<StatusEffect*> GetPositiveStatusEffects(bool SortByPriority = false) const;
			std::vector<StatusEffect*> GetNegativeStatusEffects(bool SortByPriority = false) const;
			void HandleCharacterTicked(int ticks);
			void HandleTimeElapsed(const int time);

			float GetStatusResistance(const std::string& name) const;
			float GetStatusResistance(const StatusEffect* effect) const;
			float GetStatusResistance(se_ptr effect) const;

			void IncrementStatusResistance(const std::string& name, const float inc);
			void IncrementStatusResistance(const StatusEffect* effect, const float inc);
			void IncrementStatusResistance(se_ptr effect, const float inc);

			virtual RawClonePtr RawClone() const override;
		private:
			boost::unordered_map<std::string, se_ptr> NameToSE;
			boost::unordered_map<CallCondition, std::vector<StatusEffect*> > CallConditionToSE;
			boost::unordered_map<int, std::vector<StatusEffect*> > PriorityToSE;
			boost::unordered_set<std::string> LockedInStatusEffects;
			boost::unordered_map<std::string, float> SEResistances;
			static StatusEffectsLibrary* SELibrary;
			friend class GameInstance;
		};
	}
}

#endif