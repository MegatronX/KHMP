#include "QueueTurnGenerator.h"

namespace Game
{
	namespace Battle
	{
		QueueTurnGenerator::QueueTurnGenerator(Entity* owner, const std::string& CType) : TurnGenerator(owner, CType)
		{

		}

		QueueTurnGenerator::RawClonePtr QueueTurnGenerator::RawClone() const
		{
			return new QueueTurnGenerator(*this);
		}

		void QueueTurnGenerator::GenerateNextCharacter(int GenCounter)
		{

		}
		void QueueTurnGenerator::HandleTimerOverflow(BattleCharacterComponent* character, BattleMode mode)
		{


		}
	}
}