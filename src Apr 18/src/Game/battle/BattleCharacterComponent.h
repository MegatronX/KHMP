#pragma once
#ifndef _BATTLECHARACTERCOMPONENT_H_
#define _BATTLECHARACTERCOMPONENT_H_
#include <components/Component.h>
namespace Game
{
	class Entity;
	namespace Character
	{
		class BaseCharacter;
		class Party;
	}
	namespace Battle
	{
		class BattleParty;
		class BattleCharacterComponent : public Components::Component
		{
		public:
			BattleCharacterComponent(Entity* owner);

			BattleParty* GetBattleParty() const
			{
				return BParty;
			}
			Character::Party* GetBaseParty() const
			{
				return BaseParty;
			}
			virtual RawClonePtr RawClone() const override
			{
				return new BattleCharacterComponent(*this);
			}
		protected:
				BattleParty* BParty;
				Character::Party* BaseParty;
		};
	}
}
#endif