#include "Mechanics.h"
#include <Entity.h>
#include <components/Component.h>
#include <battle/BattleField.h>
namespace Game
{
	namespace Battle
	{
		Mechanics::Mechanics(BattleField* owner) : Component(owner, owner->GetName(), "Mechanics"), Field(owner)
		{

		}
		bool Mechanics::ApplyStatusEffect(Character::BaseCharacter& target, const std::string& se, int turns, float seApplyRate)
		{
			return false;
		}
		bool Mechanics::IsHit(Character::BaseCharacter& target, Actions::Action& action)
		{
			return false;
		}
		bool Mechanics::IsCritical(Character::BaseCharacter& target, Actions::Action& action)
		{
			return false;
		}
		BattleField* Mechanics::GetField() const
		{
			return Field;
		}
	}
}