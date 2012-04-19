#pragma once

#include <components/Component.h>
#include <actions/Action.h>
#include <character/BaseCharacter.h>
#include <battle/mechanics/Mechanics.h>
namespace Game
{
	namespace Battle
	{
		class DamageCalculationComponent : Components::Component
		{
		public:
			DamageCalculationComponent(Entity* Owner);

			int CalculateDamage(Actions::Action& action, Character::BaseCharacter& target, Mechanics& mechanics);
		};
	}
}