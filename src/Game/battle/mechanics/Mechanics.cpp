#include "Mechanics.h"
#include <Entity.h>
#include <actions/Attack.h>
#include <character/StatsManager.h>
#include <components/Component.h>
#include <battle/BattleField.h>
#include <battle/DamageCalculationComponent.h>
#include <battle/HitComponent.h>

#include <battle/PostUseComponent.h>
#include <battle/PreUseComponent.h>
#include <battle/UseComponent.h>

namespace Game
{
	namespace Battle
	{
		Mechanics::Mechanics(BattleField* owner) : Component(owner, owner != nullptr ? owner->GetName() + "Mechanics" : "NoOwnerMechanics", "Mechanics"), Field(owner)
		{

		}
		bool Mechanics::ApplyStatusEffect(Character::BaseCharacter& target, const std::string& se, int turns, float seApplyRate)
		{
			return false;
		}
		
		void Mechanics::ProcessActionDefault(Actions::Action& action, bool InBattle)
		{
			PreUsePhase(action, InBattle);
			
			UsePhase(action, InBattle);
			
			PostUsePhase(action, InBattle);
		}
		
		void Mechanics::PreUsePhase(Actions::Action& action, bool InBattle /* = true */)
		{
			auto puse = action.GetComponentAs<PreUseComponent*>("PreUseComponent");
			if (puse != nullptr)
			{
				puse->PreUse(action, *this, InBattle);
			}
		}
		
		void Mechanics::PostUsePhase(Actions::Action& action, bool InBattle /* = true */)
		{
			auto puse = action.GetComponentAs<PostUseComponent*>("PreUseComponent");
			if (puse != nullptr)
			{
				puse->PostUse(action, *this, InBattle);
			}
		}

		void Mechanics::UsePhase(Actions::Action& action, bool InBattle)
		{
			auto use = action.GetComponentAs<UseComponent*>("UseComponent");
			if (use != nullptr)
			{
				use->Use(action, *this, InBattle);
			}
			else
			{

			}
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
				return ApplyHitFormula(target, action);
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
				auto sm = (*it).GetComponentAs<Character::StatsManager>("StatsManagerComponent");
				if (sm != nullptr)
				{
					runningaccuracy += sm.GetInBattleStat(Character::Stat::Accuracy);
					usercount++;
				}
			}
			if (usercount > 0)
			{
				useraccuracy = runningaccuracy / usercount;
			}
			
			float evasion = 0.f;
			
			auto atk = dynamic_cast<Actions::Attack*>(&action);
			if (atk != nullptr)
			{
				auto sm = target.GetComponentAs<Character::StatsManager*>("StatsManagerComponent");
				if (sm != nullptr)
				{
					evasion = sm->GetBattleStat(Character::Stat::MgEvasion) * atk->GetMagicWeight() + sm->GetBattleStat(Character::Stat::Evasion) * atk->GetPhysicalWeight();
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
		int Mechanics::CalculateDamage(Character::BaseCharacter& target, const Actions::Action& action)
		{
			auto dmgoverride = action.GetComponentAs<DamageCalculationComponent*>("DamageCalculationComponent");
			if (dmgoverride != nullptr)
			{
				return dmgoverride->CalculateDamage(target, action, *this);
			}
			else
			{
				return ApplyDamageFormula(target, action);
			}
		}
		int Mechanics::ApplyDamageFormula(Character::BaseCharacter& target, Actions::Action& action)
		{
			int damage = 0;
			
			action.SetCalculatedDamage(damage);
			
			return damage;
		}
		
		void EnforceActionCosts(Character::BaseCharacter& user, Actions::Action& action)
		{
			//the action gets first priority to determine the cost of performing the action. If the action does not provide an override,
			//the user can attempt a cost override
			auto actoverride = action.GetComponentAs<ActionCostOverrideComponent*>("ActionCostOverrideComponent");
			if (actoverride != nullptr)
			{
				actovverride->EnforceActionCost(user, action);
			}
			else
			{
				auto costoverrides = user.GetComponentAs<ActionCostOverrideComponent*>("ActionCostOverrideComponent");
				if (costoverrides != nullptr)
				{
					costoverrides->EnforceActionCost(user, action);
				}
				else
				{
					auto sm = user.GetComponentAs<StatManager*>("StatManager");
					if (sm != nullptr)
					{
						if (action.GetMPCost() > 0)
							sm->SetCurrentStat(Stats.MP)(sm->GetCurrentStat(Stats.MP) - action.GetMPCost())
						if (action.GetSPCost() > 0)
							sm->SetCurrentStat(Stats.SP)
			
					}
				}
			}
		}
			
		int EnforceCalculatedDamage(Character::Character& target, Actions:Action& action, int calculatedDamage)
		{
			int inflictedDamage = 0;
			if (action.IsDamageCalculated() && calculatedDamage > 0)
			{
				auto sm = target.GetComponentAs<StatManager*>("StatManager");
				if (sm != nullptr)
				{
					int remHP = sm->GetCurrentStat(Stats.HP);
					if (calcualtedDamage > remHP)
						inflictedDamage = remHP;
					sm->SetCurrentStat(Stat.HP)(remHP - calculatedDamage);
				}
#ifdef DEBUG
				else
					std:cerr << "Could not find StatManager for " << target->GetName() << "\n";				
#endif
			}
			
			return inflictedDamage;
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