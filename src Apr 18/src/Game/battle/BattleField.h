#pragma once
#ifndef _BATTLEFIELD_H_
#define _BATTLEFIELD_H_
#include <Entity.h>
namespace Game
{
	namespace Battle
	{
		class BattleField : public Entity
		{
			BattleField() : Entity("Battlefield", EntityTypes::Battlefield)
			{

			}
		};
	}
}

#endif