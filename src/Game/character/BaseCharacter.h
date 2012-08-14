#pragma once
#ifndef _BASECHARACTER_H_
#define _BASECHARACTER_H_
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <boost/unordered_map.hpp>
#include <character/Stats.h>
#include <character/StatsManager.h>
#include <character/Party.h>
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

		class BaseCharacter : public Entity, boost::signals2::trackable
		{
		public:
			BaseCharacter();
			BaseCharacter(const std::string& characterName);
			BaseCharacter(const std::string& characterName, int baseStats[Character::StatCount]);
			BaseCharacter(const std::string& characterName, std::vector<int>& baseStats);
			virtual Components::Component* GetComponent(const std::string& index) override;// const;
			virtual RawClonePtr RawClone () const;
			
			PartyInterface<BaseCharacter>* GetParty() const;
			void SetParty(PartyInterface<BaseCharacter>* party);

			StatusEffects::StatusEffectsManager& GetStatusEffectsManager();
			Abilities::AbilityManager& GetAbilityManager();

			StatsManager& GetStatsManager();
		private:
			PartyInterface<BaseCharacter>* AttachedParty;

			StatusEffects::StatusEffectsManager SEManager;
			Abilities::AbilityManager AbilManager;

			StatsManager SManager;

			Components::StatusEffectivenessComponent StatusEffectsComponent;
			Components::ElementEffectivenessComponent ElementEffectsComponent;
		};


		typedef PartyInterface<BaseCharacter> BaseParty;
		typedef boost::shared_ptr<BaseParty> bparty_ptr;

	}
}

#endif