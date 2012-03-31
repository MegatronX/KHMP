#pragma once
#ifndef _BATTLEPARTY_H_
#define _BATTLEPARTY_H_
#include <battle/BattleCharacterComponent.h>
#include <character/Party.h>
namespace Game
{
	namespace Character
	{
		Party;
	}
	namespace Battle
	{
		class BattleParty : public Character::PartyInterface<Battle::BattleCharacterComponent>
		{
		public:
			//Character::Party* GetBaseParty() con
		protected:
		private:
			Character::Party* BaseParty;
		};
		
	}
}

#endif