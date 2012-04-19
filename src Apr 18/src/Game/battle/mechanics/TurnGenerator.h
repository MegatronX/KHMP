#pragma once
#ifndef _TURNGENERATOR_H_
#define _TURNGENERATOR_H_
#include <deque>
#include <vector>
#include <Entity.h>
#include <battle/BattleCharacterComponent.h>
namespace Game
{
	namespace Battle
	{
		class BattleField;

		typedef std::deque<BattleCharacterComponent*> TurnQueue;
		typedef std::vector<BattleCharacterComponent*> ReadyList;
		class TurnGenerator : public Entity
		{
		public:
		};
	}
}

#endif