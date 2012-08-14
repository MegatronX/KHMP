#pragma once
#include <battle/mechanics/TurnGenerator.h>

namespace Game
{
	namespace Battle
	{
		class QueueTurnGenerator : public TurnGenerator
		{
		public:
			QueueTurnGenerator(Entity* owner, const std::string& CType = "QueueTurnGenerator");

			virtual RawClonePtr RawClone() const override;

			virtual void GenerateNextCharacter(int GenCounter = 1);

		protected:
			virtual void HandleTimerOverflow(BattleCharacterComponent*, BattleMode);
		private:
			int GenCount;
		};
	}
}