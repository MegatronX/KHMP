#pragma once
#ifndef _HITCOMPONENT_H_
#define _HITCOMPONENT_H_

#include <components/Component.h>
#include <actions/Action.h>
#include <character/BaseCharacter.h>
#include <battle/mechanics/Mechanics.h>

class Entity;
namespace Game
{
	namespace Battle
	{
		class HitComponent :public Components::Component
		{
		public:
			HitComponent(Entity* entity);

			bool IsHit(Character::BaseCharacter& target, Actions::Action& action, Mechanics& mechanics);
		};
	}
}

#endif