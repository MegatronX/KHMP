#pragma once

#include <character/BaseCharacter.h>
#include <character/StatsManager.h>
#include <boost/python.hpp>
using namespace Game::Character;
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		BOOST_PYTHON_MODULE(CharacterModule)
		{
			enum_<Stat>("Stat")
				.value("Accuracy", Stat::Accuracy)
				.value("Agility", Stat::Agility)
				.value("Defense", Stat::Defense)
				.value("Evasion", Stat::Evasion)
				.value("HP", Stat::HP)
				.value("Luck", Stat::Luck)
				.value("Magic", Stat::Magic)
				.value("MgEvasion", Stat::MgEvasion)
				.value("MP", Stat::MP)
				.value("Skill", Stat::Skill)
				.value("SP", Stat::SP)
				.value("Speed", Stat::Speed)
				.value("Spirit", Stat::Spirit)
				.value("Strength", Stat::Strength)
				.value("Vitality", Stat::Vitality)
				;
			enum_<CharacterStatus>("CharacterStatus")
				.value("Normal", CharacterStatus::Normal)
				.value("Normal", CharacterStatus::Normal)
				;

			class_<Character::BaseCharacter>("BaseCharacter")
				.def("GetStatsManager", &Character::BaseCharacter::GetStatsManager, return_value_policy<reference_existing_object>())
				.def("GetStatusEffectsManager", &Character::BaseCharacter::GetStatusEffectsManager, return_value_policy<reference_existing_object>())

				//.def("GetCombinedStat", &Character::BaseCharacter::GetCombinedStat)
				//.def("GetLevel", &Character::BaseCharacter::GetLevel)
				//.def("GetName", &Character::BaseCharacter::GetName, return_value_policy<reference_existing_object>())
				//.def("GetStatus", &Character::BaseCharacter::GetStatus)
				;
			//bool (Components::Component::*IsType1)(const std::string&) = &Components::Component::IsType;
			//bool (Components::Component::*IsType2)(int) = &Components::Component::IsType;

			void (Character::StatsManager::*Sync1)(const Stat stat) = &Character::StatsManager::SyncStat;
			void (Character::StatsManager::*Sync2)(const int stat) = &Character::StatsManager::SyncStat;
			void (Character::StatsManager::*Sync3)(const int stat) = &Character::StatsManager::SyncBattleStat;
			void (Character::StatsManager::*Sync4)(const int stat) = &Character::StatsManager::SyncBattleStat;
			class_<Character::StatsManager, boost::shared_ptr<Character::StatsManager>, bases<Components::Component>, boost::noncopyable >("StatsManager", no_init)
				.def("GetAdditionalStat", &Character::StatsManager::GetAdditionalStat)
				.def("GetBaseStat", &Character::StatsManager::GetBaseStat)
				.def("GetBattleStat", &Character::StatsManager::GetBattleStat)
				.def("GetCombinedStat", &Character::StatsManager::GetCombinedStat)
				.def("SetAdditionalStat", &Character::StatsManager::SetAdditionalStat)
				.def("SetBaseStat", &Character::StatsManager::SetBaseStat)
				.def("SetBattleStat", &Character::StatsManager::SetBattleStat)
				.def("SyncAllStats", &Character::StatsManager::SyncAllStats)
				.def("SyncAllBattleStats", &Character::StatsManager::SyncAllBattleStats)
				.def("SyncStat", Sync1)
				.def("SyncStat", Sync2)
				.def("SyncBattleStat", Sync4)
				.def("SyncBattleStat", Sync4)
				//.def("SyncStat", &Character::StatsManager::SyncStat)
				//.def("", &Character::StatsManager:)
				//.def("", &Character::StatsManager:)
				;
		}

	}
};
