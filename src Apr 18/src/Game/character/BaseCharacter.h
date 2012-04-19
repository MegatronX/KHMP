#pragma once
#ifndef _BASECHARACTER_H_
#define _BASECHARACTER_H_
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <boost/unordered_map.hpp>
#include <character/Stats.h>
#include <character/StatsManager.h>
#include <components/StatsComponent.h>
#include <components/ElementEffectivenessComponent.h>
#include <components/StatusEffectivenessComponent.h>
#include <statuseffects/StatusEffectsManager.h>
#include <abilities/AbilityManager.h>
#include <Entity.h>
#include <deque>
namespace Game
{
	const int StatusCount = 2;
	enum CharacterStatus
	{
		Normal,
		Preview
	};
	namespace Character
	{
		class Party;
		class BaseCharacter : public Entity, boost::signals2::trackable
		{
		public:
			BaseCharacter();
			BaseCharacter(const std::string& characterName);
			BaseCharacter(const std::string& characterName, int baseStats[Character::StatCount]);
			virtual Components::Component* GetComponent(const std::string& index);// const;
			virtual RawClonePtr RawClone () const;
			
			Party* GetParty() const;

			StatusEffects::StatusEffectsManager& GetStatusEffectsManager();
			Abilities::AbilityManager& GetAbilityManager();

			StatsManager& GetStatsManager();
		private:
			Party* AttachedParty;

			StatusEffects::StatusEffectsManager SEManager;
			Abilities::AbilityManager AbilManager;

			StatsManager SManager;

			Components::StatusEffectivenessComponent StatusEffectsComponent;
			Components::ElementEffectivenessComponent ElementEffectsComponent;
		};
	}
}

#endif