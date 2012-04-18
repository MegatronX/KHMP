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
		
		void Mechanics::ProcessActionDefault(Actions::Action& action)
		{
			PreUsePhase(action);
			
			
			PostUsePhase(action);
		}
		
		
		bool Mechanics::IsHit(Character::BaseCharacter& target, Actions::Action& action)
		{
			auto hitoverride = action.GetComponentAs<HitComponent>("HitComponent");
			if (hitoverride != nullptr)
			{
				return hitoverride.IsHit(target, action, *this);
			}
			else
			{
				return ApplyHitFormulat(target, action);
			}
			return false;
		}
		bool Mechanics::ApplyHitFormula(Character::BaseCharacter& target, Actions::Action& action)
		{
			float actionaccuracy = action.GetAccuracy();
			float useraccuracy = 0.75f;
			float runningaccuracy = useraccuracy;
			auto usercount = 0;
			for (auto it = action.Users.GetPartyMembers().begin(); it != action.Users.GetPartyMembers().end(); ++it)
			{
				auto sm = (*it).GetComponentAs<Character::StatsManagerComponent>("StatsManagerComponent");
				if (sm != nullptr)
				{
					runningaccuracy += sm.GetInBattleStat(Stat::Accuracy);
					usercount++;
				}
			}
			if (usercount > 0)
			{
				useraccuracy = runningaccuracy / usercount;
			}
			
			float evasion = 0.f;
			
			auto atk = dynamic_cast<Attack*>(&action);
			if (atk != nullptr)
			{
				auto sm = target.GetComponentAs<CharacteR:StatsManagerComponent>("StatsManagerComponent");
				if (sm != nullptr)
				{
					evasion = sm.GetInBattleStat(Stat::MgEvasion) * atk->GetMagicWeight() + sm.GetInBattleStat(Stat::Evasion) * atk->GetPhysicalWeight();
				}	
			}
			
		}
		bool Mechanics::IsCritical(Character::BaseCharacter& target, Actions::Action& action)
		{
			auto critoverride = action.GetComponetAs<CriticalHitComponent>("CriticalHitComponent");
			if (critoverride != nullptr)
			{
				return critoverride.IsCritical(target, action, *this);
			}
			else
			{
				return ApplyCriticalFormula(target, action);
			}
			return false;
		}
		bool Mechanics::ApplyCriticalFormula(Character::BaseCharacter& target, Actions::Action& action)
		{
			bool critical = false;
			auto atk = dynamic_cast<Attack*>(&action);
			if (atk != nullptr)
			{
				float critChance = atk->GetCriticalChance()
			}
			return critical;
		}
		int Mechanics::CalculateDamage(Character::BaseCharacter& target, const Action& action)
		{
			auto dmgoverride = action.GetComponentAs<DamageCalculationComponent>("DamageCalculationComponent");
			if (dmgoverride != nullptr)
			{
				return dmgoverride.CalculateDamage(target, action, *this);
			}
			else
			{
				return ApplyDamageFormula(target, action, *this);
			}
		}
		int Mechanics::ApplyDamageFormula(Character::BaseCharacter& target, const Action& action)
		{
			return 0;
		}
		BattleField* Mechanics::GetField() const
		{
			return Field;
		}
		Mechanics::RawClonePtr Mechanics::RawClone() const
		{
			return new Mechanics(*this);
		}
	}
}