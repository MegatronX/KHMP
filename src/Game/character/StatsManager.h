#pragma once
#ifndef _STATSMANAGER_H_
#define _STATSMANAGER_H_
#include <components/Component.h>
#include <components/StatsComponent.h>
#include <Entity.h>
namespace Game
{
	namespace Character
	{
		typedef std::pair<bool, int> StatLimitBreaks;
		class StatsManager : public Components::Component
		{
		public:
			StatsManager(Entity* owner);
			StatsManager(Entity* owner, int baseStats[Character::StatCount]);
			int GetBaseStat(const Stat stat) const;
			void SetBaseStat(const Stat stat, const int val);
			int GetCombinedStat(const Stat stat) const;
			int GetBattleStat(const Stat stat) const;
			void SetBattleStat(const Stat stat, const int val);

			int GetAdditionalStat(const std::string& adderName, const Stat stat) const;
			void SetAdditionalStat(const std::string& adderName, const Stat stat, int val);

			void SyncStat(const Stat stat);
			void SyncStat(const int index);
			void SyncBattleStat(const Stat stat);
			void SyncBattleStat(const int index);
			void SyncAllStats();
			void SyncAllBattleStats();
		protected:
		private:
			Components::StatComponent BaseStats;
			Components::StatComponent PermanentStatBoosts;
			Components::StatComponent CombinedStats;
			Components::StatComponent InBattleStats;
			
			Components::StatComponent PreviewStats;

			boost::unordered_map<std::string, Components::StatComponent> AdditionalStatsAdders;

			StatLimitBreaks StatsBreaksL1[Character::StatCount];
			StatLimitBreaks StatsBreaksL2[Character::StatCount];
		};

		
	}
}

#endif