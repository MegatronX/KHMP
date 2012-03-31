#include "StatusEffect.h"

namespace Game
{
	namespace StatusEffects
	{

		StatusEffect::StatusEffect(Character::BaseCharacter * holder, const std::string& name, bool IsPos, const int priority, const int TickCount) : Holder(holder), RemainingTicks(TickCount), NetPositive(IsPos), Priority(priority), Entity(name, Entity::StringHasher("StatusEffect"))
		{

		}

		int StatusEffect::GetRemainingTicks() const
		{
			return RemainingTicks;
		}
		int StatusEffect::GetPriority() const
		{
			return Priority;
		}

		StatusEffect::RawClonePtr StatusEffect::RawClone() const
		{
			return new StatusEffect(*this);
		}

		void StatusEffect::SetRemainingTicks(const int ticks)
		{
			RemainingTicks = ticks;
		}
		bool StatusEffect::IsPositive() const
		{
			return NetPositive;
		}
		void StatusEffect::SetIsPositive(const bool pos)
		{
			NetPositive = pos;
		}
		const Character::BaseCharacter* StatusEffect::GetHolder() const
		{
			return Holder;
		}
		void StatusEffect::SetHolder(Character::BaseCharacter* holder)
		{
			Holder = holder;
		}
		void StatusEffect::SetPriority(const int prior)
		{
			Priority = prior;
		}
	}
}