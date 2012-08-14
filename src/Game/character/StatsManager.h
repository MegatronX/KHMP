#pragma once
#ifndef _STATSMANAGER_H_
#define _STATSMANAGER_H_
#include <components/Component.h>
#include <components/StatsComponent.h>
#include <Entity.h>

#include <boost/signals2.hpp>
namespace Game
{
	namespace Character
	{
		typedef std::pair<bool, int> StatLimitBreaks;
		typedef boost::signals2::signal<void (const std::string& compName, Components::StatComponent<int>*, Character::Stat stat, int oldVal, int newVal)> StatChangedSignal;
		class StatsManager : public Components::Component
		{
		public:
			StatsManager(Entity* owner);
			StatsManager(Entity* owner, int baseStats[Character::StatCount]);
			StatsManager(Entity* owner, std::vector<int>& stats);
			int GetBaseStat(const Stat stat, bool IgnoreLimits = false) const;
			int GetPermanentStatBoost(const Stat stat) const;
			float GetPermanentStatMultiplier(const Stat stat) const;

			int GetAbilityStatAdder(const Stat stat) const;
			float GetAbilityStatMultiplier(const Stat stat) const;

			void IncrementAbilityStatAdder(const Stat stat, const int inc, bool sync = true);
			void IncrementAbilityStatMultiplier(const Stat stat, const float inc, bool sync = true);

			int GetStatusEffectStatAdder(const Stat stat) const;
			float GetStatusEffectStatMultiplier(const Stat stat) const;

			void IncrementStatusEffectStatAdder(const Stat stat, const int inc, bool sync = true);
			void IncrementStatusEffectStatMultiplier(const Stat stat, const float inc, bool sync = true);

			int GetAdditionalStatAdder(const std::string& name, const Stat stat) const;
			float GetAdditionalStatMultiplier(const std::string& name, const Stat stat) const;

			void IncrementAdditionalStatAdder(const std::string& name, const Stat stat, const int inc, bool sync = true);
			void IncrementAdditionalStatMultiplier(const std::string& name, const Stat stat, const float inc, bool sync = true);

			int GetCombinedStat(const Stat stat, bool IgnoreLimits = false) const;

			int GetBattleStat(const Stat stat, bool IgnoreLimits = false) const;

			void IncrementStatBreak(const Stat stat, const int breaks, const int Level = 1);

			//Sync Stat Functions
			void SyncStat(const Stat stat);
			void SyncStat(const int index);
			void SyncBattleStat(const Stat stat, bool SyncBase = false);
			void SyncBattleStat(const int index, bool SyncBase = false);
			void SyncAllStats();
			void SyncAllBattleStats(bool SyncBase = false);
		protected:
			void SetBaseStat(const Stat stat, const int increment, bool sync = true);
			void SetPermanentStatBoost(const Stat stat, const int inc, bool sync = true);
			void SetPermanentStatMultipliers(const Stat stat, const int inc, bool sync = true);

			void IncrementBaseStat(const Stat stat, const int increment, bool sync = true);
			void IncrementPermanentStatBoost(const Stat stat, const int inc, bool sync = true);
			void IncrementPermanentStatMultipliers(const Stat stat, const int inc, bool sync = true);

			std::array<boost::unordered_map<int, int>, StatCount> StatBreakCounts; //StatBreakCounts[stat][level] -> break count
			std::array<boost::unordered_map<int, int>, StatCount> StatLimits; //StatBreakCounts[stat][level] -> break count

			//boost::unordered_map<Character::Stat, boost::unordered_map<int, int> > StatBreakCounts; //StatBreakCounts[stat][level] -> break count
			//boost::unordered_map<Character::Stat, boost::unordered_map<int, int> > StatBreakLimits; //StatBreakLimits[stat][level] -> Stat Limit at level
		private:
			//Base Stat Set
			Components::StatComponent<int> BaseStats;
			Components::StatComponent<int> PermanentStatBoosts;
			Components::StatComponent<float> PermanentStatMultipliers;
			//Abilities
			Components::StatComponent<int> AbilityStatAdders;
			Components::StatComponent<float> AbilityStatMultipliers;
			//Equipment
			Components::StatComponent<int> EquipmentStatAdders;
			Components::StatComponent<float> EquipmentStatMultipliers;
			//Others
			boost::unordered_map<std::string, Components::StatComponent<int> > AdditionalStatsAdders;
			boost::unordered_map<std::string, Components::StatComponent<float> > AdditionalStatsMultipliers;
			//Combined
			Components::StatComponent<int> CombinedStats;
			//SE
			Components::StatComponent<int> SEStatAdders;
			Components::StatComponent<float> SEStatMultipliers;
			//Battle
			Components::StatComponent<int> BattleStatAdders;
			Components::StatComponent<float> BattleStatMultipliers;
			Components::StatComponent<int> BattleStats;
			/*Components::StatComponent<int, float> BaseStats;
			Components::StatComponent PermanentStatBoosts;
			Components::StatComponent AbilityStatBoosts;
			Components::StatComponent SEStatBoosts;
			Components::StatComponent CombinedStats;
			Components::StatComponent InBattleStats;
			
			Components::StatComponent PreviewStats;

			boost::unordered_map<std::string, Components::StatComponent> AdditionalStatsAdders;*/

			StatLimitBreaks StatsBreaksL1[Character::StatCount];
			StatLimitBreaks StatsBreaksL2[Character::StatCount];
		};

		
	}
}

#endif