#pragma once
#ifndef _BASECHARACTER_H_
#define _BASECHARACTER_H_
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <boost/unordered_map.hpp>
#include <character/Stats.h>
#include <components/StatsComponent.h>
#include <components/ElementEffectivenessComponent.h>
#include <components/StatusEffectivenessComponent.h>
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
			virtual Components::Component* GetComponent(const std::string& index);// const;
			virtual RawClonePtr RawClone () const;
			
			Party* GetParty() const;

		private:
			Party* AttachedParty;
			Components::StatusEffectivenessComponent StatusEffectsComponent;
			Components::ElementEffectivenessComponent ElementEffectsComponent;
		};
	}
}

#endif