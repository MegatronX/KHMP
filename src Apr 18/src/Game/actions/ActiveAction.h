#pragma once
#ifndef _ACTIVEACTION_H_
#define _ACTIVEACTION_H_
//#include <battle/Action.h>
#include <battle/BattleCharacter.h>
namespace Game
{
	namespace Character
	{
		class BaseCharacter;
	}
	namespace Actions
	{
		class Action;
		struct ActiveAction
		{
			Battle::BattleCharacter* AttachedBattleCharacter;
			Character::BaseCharacter* AttachedCharacter;
			boost::shared_ptr<Game::Actions::Action> action;
			bool operator==(const ActiveAction& action)
			{
				return ((AttachedCharacter != NULL && action.AttachedCharacter != NULL &&
					(AttachedCharacter->GetID() == action.AttachedCharacter->GetID())) ||
					(AttachedBattleCharacter != NULL && action.AttachedBattleCharacter != NULL &&
					(AttachedBattleCharacter->GetID() == action.AttachedBattleCharacter->GetID())));
			}
			bool operator!=(const ActiveAction& action)
			{
				return (*this == action);
			}
		};
	}
}
#endif