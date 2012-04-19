#include "StatsManager.h"

namespace Game
{
	namespace Character
	{
		StatsManager::StatsManager(Entity* owner) : Component(owner, owner->GetName() + "StatsManager", "StatsManager"), InBattleStats(owner, 0), BaseStats(owner, 0), CombinedStats(owner, 0), PermanentStatBoosts(owner, 0), PreviewStats(owner, 0)
		{

		}
		StatsManager::StatsManager(Entity* owner, int baseStats[Character::StatCount]) : Component(owner, owner->GetName() + "StatsManager", "StatsManager"), InBattleStats(owner, 0), BaseStats(owner, baseStats), CombinedStats(owner, 0), PermanentStatBoosts(owner, 0), PreviewStats(owner, 0)
		{
			SyncAllStats();
		}
		int StatsManager::GetBaseStat(const Stat stat) const
		{
			return BaseStats.GetStat(stat);
		}
		void StatsManager::SetBaseStat(const Stat stat, const int val)
		{
			BaseStats[stat] = val;
		}
		int StatsManager::GetCombinedStat(const Stat stat) const
		{
			return CombinedStats.GetStat(stat);
		}
		int StatsManager::GetBattleStat(const Stat stat) const
		{
			return InBattleStats.GetStat(stat);
		}
		void StatsManager::SetBattleStat(const Stat stat, const int val)
		{
			InBattleStats[stat] = val;
		}

		int StatsManager::GetAdditionalStat(const std::string& adderName, const Stat stat) const
		{
			auto it = AdditionalStatsAdders.find(adderName);
			if (it != AdditionalStatsAdders.end())
			{
				return ((*it).second).GetStat(stat);
			}
			return 0;
		}

		void StatsManager::SetAdditionalStat(const std::string& adderName, const Stat stat, int val)
		{
			auto it = AdditionalStatsAdders.find(adderName);
			if (it != AdditionalStatsAdders.end())
			{
				(*it).second[stat] = val;
			}
		}


		void StatsManager::SyncStat(const Stat stat)
		{
			int value = BaseStats[stat] + PermanentStatBoosts[stat];
			if (AdditionalStatsAdders.size() > 0)
			{
				for (auto it = AdditionalStatsAdders.begin(); it != AdditionalStatsAdders.end(); ++it)
				{
					value += (*it).second[stat];
				}
			}
			CombinedStats[stat] = value;
		}
		void StatsManager::SyncStat(const int stat)
		{
			int value = BaseStats[stat] + PermanentStatBoosts[stat];
			if (AdditionalStatsAdders.size() > 0)
			{
				for (auto it = AdditionalStatsAdders.begin(); it != AdditionalStatsAdders.end(); ++it)
				{
					value += (*it).second[stat];
				}
			}
			CombinedStats[stat] = value;
		}
		void StatsManager::SyncBattleStat(const Stat stat)
		{
			SyncStat(stat);
			InBattleStats[stat] = CombinedStats[stat];
		}
		void StatsManager::SyncBattleStat(const int index)
		{
			SyncStat(index);
			InBattleStats[index] = CombinedStats[index];
		}
		void StatsManager::SyncAllStats()
		{
			for (int i = 0; i < Character::StatCount; ++i)
			{
				SyncStat(i);
			}
		}
		void StatsManager::SyncAllBattleStats()
		{
			for (int i = 0; i < Character::StatCount; ++i)
			{
				SyncBattleStat(i);
			}
		}
	}
}