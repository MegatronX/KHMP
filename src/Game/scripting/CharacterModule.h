#pragma once

#include <character/BaseCharacter.h>
#include <character/StatsManager.h>
#include <character/PlayerParty.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
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

			class_<Character::BaseCharacter, bases<Entity> >("BaseCharacter", no_init)
				.def("GetStatsManager", &Character::BaseCharacter::GetStatsManager, return_value_policy<reference_existing_object>())
				.def("GetStatusEffectsManager", &Character::BaseCharacter::GetStatusEffectsManager, return_value_policy<reference_existing_object>())
				.def("__eq__", &Character::BaseCharacter::operator==)
				.def("__neq__", &Character::BaseCharacter::operator!=)
				//.def("__copy__", &generic__copy__<StatusEffectWrap>)
				//.def("__deepcopy__", &generic__deepcopy__<StatusEffectWrap>)
				//.def("GetCombinedStat", &Character::BaseCharacter::GetCombinedStat)
				//.def("GetLevel", &Character::BaseCharacter::GetLevel)
				//.def("GetName", &Character::BaseCharacter::GetName, return_value_policy<reference_existing_object>())
				//.def("GetStatus", &Character::BaseCharacter::GetStatus)
				;
			//bool (Components::Component::*IsType1)(const std::string&) = &Components::Component::IsType;
			//bool (Components::Component::*IsType2)(int) = &Components::Component::IsType;

			void (Character::StatsManager::*Sync1)(const Stat stat) = &Character::StatsManager::SyncStat;
			void (Character::StatsManager::*Sync2)(const int stat) = &Character::StatsManager::SyncStat;
			void (Character::StatsManager::*Sync3)(const Stat stat, bool SyncBase) = &Character::StatsManager::SyncBattleStat;
			void (Character::StatsManager::*Sync4)(const int stat, bool) = &Character::StatsManager::SyncBattleStat;
			class_<Character::StatsManager, boost::shared_ptr<Character::StatsManager>, bases<Components::Component>, boost::noncopyable >("StatsManager", no_init)
				.def("GetBaseStat", &Character::StatsManager::GetBaseStat)
				.def("GetAbilityAdder", &Character::StatsManager::GetAbilityStatAdder)
				.def("GetAbilityStatMultiplier", &Character::StatsManager::GetAbilityStatMultiplier)
				.def("GetAdditionalStatAdder", &Character::StatsManager::GetAdditionalStatAdder)
				.def("GetAdditionalStatMultiplier", &Character::StatsManager::GetAdditionalStatMultiplier)
				.def("GetBattleStat", &Character::StatsManager::GetBattleStat)
				.def("GetPermanentStatBoost", &Character::StatsManager::GetPermanentStatBoost)
				.def("GetPermanentStatMultiplier", &Character::StatsManager::GetPermanentStatMultiplier)
				.def("GetStatusEffectStatAdder", &Character::StatsManager::GetStatusEffectStatAdder)
				.def("GetStatusEffectStatMultiplier", &Character::StatsManager::GetStatusEffectStatMultiplier)
				.def("IncrementAbilityStatAdder", &Character::StatsManager::IncrementAbilityStatAdder, (boost::python::arg("sync") = true))
				.def("IncrementAbilityStatMultiplier", &Character::StatsManager::IncrementAbilityStatMultiplier, (boost::python::arg("sync") = true))
				.def("IncrementAdditionalStatAdder", &Character::StatsManager::IncrementAdditionalStatAdder, (boost::python::arg("sync") = true))
				.def("IncrementAdditionalStatMultiplier", &Character::StatsManager::IncrementAdditionalStatMultiplier, (boost::python::arg("sync") = true))
				.def("IncrementStatusEffectStatAdder", &Character::StatsManager::IncrementStatusEffectStatAdder, (boost::python::arg("sync") = true))
				.def("IncrementStatusEffectStatMultiplier", &Character::StatsManager::IncrementStatusEffectStatMultiplier, (boost::python::arg("sync") = true))
				.def("SyncAllStats", &Character::StatsManager::SyncAllStats)
				.def("SyncAllBattleStats", &Character::StatsManager::SyncAllBattleStats)
				.def("SyncStat", Sync1)
				.def("SyncStat", Sync2)
				.def("SyncBattleStat", Sync3, (boost::python::arg("SyncBase") = false))
				.def("SyncBattleStat", Sync4, (boost::python::arg("SyncBase") = false))
				;

			/*class_<boost::unordered_map<std::string, BaseParty::MemberPtr> >("BasePartyMemberMap")
				.def(map_indexing_suite<boost::unordered_map<std::string, BaseParty::MemberPtr> >())
				;*/

			class_<std::vector<int> > ("StatList")
				.def(vector_indexing_suite<std::vector<int> >())
				;

			class_<BaseParty, bases<Entity> >("BaseParty", init<const std::string&>())
				.def("AddMember", &BaseParty::AddMember)
				.def("RemoveMemberByName", &BaseParty::RemoveMemberByName)
				.def("removeMemberByMemberPtr", &BaseParty::RemoveMemberByMemberPtr)
				.def("GetRawPartyMembers", &BaseParty::GetRawPartyMembers)
				.def("GetPartyMembers", &BaseParty::GetPartyMembers, return_value_policy<reference_existing_object>())
				;
			
			class_<PlayerParty, bases<BaseParty> >("PlayerParty")
				.def("AddCharacter", &PlayerParty::AddCharacter)
				.def("RemoveCharacter", &PlayerParty::RemoveCharacter)
				.def("GetPlayerCharacterParty", &PlayerParty::GetPlayerCharacterParty)
				;
			//class_<Character::PlayerParty, bases
		}

	}
};
