#include "StatsManager.h"

namespace Game
{
	namespace Character
	{
		const int StatLimitL1 = 9999;
		const int StatLimitL2 = 99999;
		StatsManager::StatsManager(Entity* owner) : Component(owner, owner->GetName() + "StatsManager", "StatsManager"), 
			BaseStats(owner, 0), PermanentStatBoosts(owner, 0), PermanentStatMultipliers(owner, 0.f), AbilityStatAdders(owner, 0), AbilityStatMultipliers(owner, 0.f), SEStatAdders(owner, 0), SEStatMultipliers(owner, 0.f),
			CombinedStats(owner, 0), BattleStatAdders(owner, 0), BattleStatMultipliers(owner, 0.f), BattleStats(owner, 0), EquipmentStatAdders(owner, 0), EquipmentStatMultipliers(owner, 0.f)
		{
			SyncAllBattleStats(true);
		}
		StatsManager::StatsManager(Entity* owner, int baseStats[Character::StatCount]) : Component(owner, owner->GetName() + "StatsManager", "StatsManager"), 
			BaseStats(owner, baseStats), PermanentStatBoosts(owner, 0), PermanentStatMultipliers(owner, 0.f), AbilityStatAdders(owner, 0), AbilityStatMultipliers(owner, 0.f), SEStatAdders(owner, 0), SEStatMultipliers(owner, 0.f),
			CombinedStats(owner, 0), BattleStatAdders(owner, 0), BattleStatMultipliers(owner, 0.f), BattleStats(owner, 0), EquipmentStatAdders(owner, 0), EquipmentStatMultipliers(owner, 0.f)
		{
			SyncAllBattleStats(true);
		}
		StatsManager::StatsManager(Entity* owner, std::vector<int>& stats) : Component(owner, owner->GetName() + "StatsManager", "StatsManager"), 
			BaseStats(owner, 0), PermanentStatBoosts(owner, 0), PermanentStatMultipliers(owner, 0.f), AbilityStatAdders(owner, 0), AbilityStatMultipliers(owner, 0.f), SEStatAdders(owner, 0), SEStatMultipliers(owner, 0.f),
			CombinedStats(owner, 0), BattleStatAdders(owner, 0), BattleStatMultipliers(owner, 0.f), BattleStats(owner, 0), EquipmentStatAdders(owner, 0), EquipmentStatMultipliers(owner, 0.f)
		{
			for (int i = 0; i < stats.size() && i < StatCount; ++i)
			{
				BaseStats[i] = stats[i];
			}
			SyncAllBattleStats(true);
		}
		int StatsManager::GetBaseStat(const Stat stat, bool ignoreLimits) const
		{
			return BaseStats.GetStat(stat);
		}
		int StatsManager::GetPermanentStatBoost(const Stat stat) const
		{
			return PermanentStatBoosts.GetStat(stat);
		}
		float StatsManager::GetPermanentStatMultiplier(const Stat stat) const
		{
			return PermanentStatMultipliers.GetStat(stat);
		}

		int StatsManager::GetAbilityStatAdder(const Stat stat) const
		{
			return AbilityStatAdders.GetStat(stat);
		}
		float StatsManager::GetAbilityStatMultiplier(const Stat stat) const
		{
			return AbilityStatMultipliers.GetStat(stat);
		}

		void StatsManager::IncrementAbilityStatAdder(const Stat stat, const int inc, bool sync)
		{
			AbilityStatAdders[stat] += inc;
			if (sync)
			{
				SyncStat(stat);
			}
		}
		void StatsManager::IncrementAbilityStatMultiplier(const Stat stat, const float inc, bool sync)
		{
			AbilityStatMultipliers[stat] += inc;
			if (sync)
			{
				SyncStat(stat);
			}
		}

		int StatsManager::GetStatusEffectStatAdder(const Stat stat) const
		{
			return SEStatAdders.GetStat(stat);
		}
		float StatsManager::GetStatusEffectStatMultiplier(const Stat stat) const
		{
			return SEStatMultipliers.GetStat(stat);
		}

		void StatsManager::IncrementStatusEffectStatAdder(const Stat stat, const int inc, bool sync)
		{
			SEStatAdders[stat] += inc;
			if (sync)
			{
				SyncBattleStat(stat);
			}
		}
		void StatsManager::IncrementStatusEffectStatMultiplier(const Stat stat, const float inc, bool sync)
		{
			SEStatMultipliers[stat] += inc;
			if (sync)
			{
				SyncBattleStat(stat);
			}
		}

		int StatsManager::GetAdditionalStatAdder(const std::string& name, const Stat stat) const
		{
			auto it = AdditionalStatsAdders.find(name);
			if (it != AdditionalStatsAdders.end())
			{
				return (*it).second.GetStat(stat);
			}
			return 0;
		}
		float StatsManager::GetAdditionalStatMultiplier(const std::string& name, const Stat stat) const
		{
			auto it = AdditionalStatsMultipliers.find(name);
			if (it != AdditionalStatsMultipliers.end())
			{
				return (*it).second.GetStat(stat);
			}
			return 0;
		}

		void StatsManager::IncrementAdditionalStatAdder(const std::string& name, const Stat stat, const int inc, bool sync)
		{
			AdditionalStatsAdders[name].IncrementStat(stat, inc);
			if (sync)
			{
				SyncStat(stat);
			}
		}
		void StatsManager::IncrementAdditionalStatMultiplier(const std::string& name, const Stat stat, const float inc, bool sync)
		{
			AdditionalStatsMultipliers[name].IncrementStat(stat, inc);
			if (sync)
			{
				SyncStat(stat);
			}
		}

		int StatsManager::GetCombinedStat(const Stat stat, bool ignoreLimits) const
		{
			return BattleStats.GetStat(stat);
		}

		int StatsManager::GetBattleStat(const Stat stat, bool ignoreLimits) const
		{
			int retstat = BattleStats.GetStat(stat);

			if (!ignoreLimits)
			{
				
			}

			return retstat;//BattleStats.GetStat(stat);
		}




		void StatsManager::SyncStat(const Stat stat)
		{
			int base = BaseStats[stat] + PermanentStatBoosts[stat] + AbilityStatAdders[stat] + EquipmentStatAdders[stat];
			if (AdditionalStatsAdders.size() > 0)
			{
				for (auto it = AdditionalStatsAdders.begin(); it != AdditionalStatsAdders.end(); ++it)
				{
					base += (*it).second[stat];
				}
			}
			float Mult = 1.f + PermanentStatMultipliers[stat] + AbilityStatMultipliers[stat] + EquipmentStatMultipliers[stat];
			if (AdditionalStatsMultipliers.size() > 0)
			{
				for (auto it = AdditionalStatsMultipliers.begin(); it != AdditionalStatsMultipliers.end(); ++it)
				{
					Mult += (*it).second[stat];
				}
			}
			Mult = std::max<float>(0.f, Mult);
			CombinedStats[stat] = static_cast<int>(static_cast<float>(base) * Mult);
			//CombinedStats[stat] = value;
		}
		void StatsManager::SyncStat(const int stat)
		{
			SyncStat(static_cast<Stat>(stat));
		}
		void StatsManager::SyncBattleStat(const Stat stat, bool SyncBase)
		{
			if (SyncBase)
				SyncStat(stat);
			BattleStats[stat] = static_cast<int>((static_cast<float>(CombinedStats[stat] + SEStatAdders[stat] + BattleStatAdders[stat]) * 
				std::max<float>(0.f, (1.f + SEStatMultipliers[stat] + BattleStatMultipliers[stat]))));
			//InBattleStats[stat] = CombinedStats[stat];
		}
		void StatsManager::SyncBattleStat(const int index, bool SyncBase)
		{
			SyncBattleStat(static_cast<Character::Stat>(index), SyncBase);
		}
		void StatsManager::SyncAllStats()
		{
			for (int i = 0; i < Character::StatCount; ++i)
			{
				SyncStat(i);
			}
		}
		void StatsManager::SyncAllBattleStats(bool SyncBase)
		{
			for (int i = 0; i < Character::StatCount; ++i)
			{
				SyncBattleStat(i, SyncBase);
			}
		}
	}
}