#pragma once
#include <character/BaseCharacter.h>
#include <Entity.h>
namespace Game
{
	namespace Battle
	{
		class BattleCharacter : public Entity
		{
		public:
		private:
			Character::BaseCharacter* WrappedCharacter;
		};
	}
}