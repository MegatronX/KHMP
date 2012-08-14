#include "Mechanics.h"
#include <set>
#include <algorithm>
#include <Entity.h>
#include <actions/Attack.h>
#include <actions/ActionModifierComponent.h>
#include <character/StatsManager.h>
#include <components/Component.h>
#include <components/ElementWeightComponent.h>
#include <components/ElementEffectivenessComponent.h>
#include <battle/BattleField.h>
#include <battle/DamageCalculationComponent.h>
#include <battle/HitComponent.h>
#include <battle/DamageSplitComponent.h>
#include <battle/PostUseComponent.h>
#include <battle/PreUseComponent.h>
#include <battle/UseComponent.h>
#include <battle/CriticalHitComponent.h>
#include <battle/AtkDefStatComponent.h>

#include <battle/mechanics/ATBTurnGenerator.h>
#include <battle/mechanics/QueueTurnGenerator.h>

#include <boost/algorithm/string.hpp>
namespace Game
{
	namespace Battle
	{
		const std::string PreUseIndex = "PreUseComponent";
		const std::string PostUseIndex = "PostUseComponent";
		const std::string UseIndex = "UseIndexComponent";

		Mechanics::Mechanics(BattleField* owner, unsigned int RandomSeed) : Component(owner, owner != nullptr ? owner->GetName() + "Mechanics" : "NoOwnerMechanics", "Mechanics"), Field(owner), RandomsEnabled(true), ActionInProgress(nullptr)
		{
			RNG.seed(RandomSeed);
			
			
		}
		void Mechanics::Init()
		{


		}
		bool Mechanics::ApplyStatusEffect(Character::BaseCharacter& target, const std::string& se, int turns, float seApplyRate)
		{
			return false;
		}
		
		void Mechanics::ProcessActionDefault(Actions::Action& action, bool InBattle)
		{
			//auto& blz = dynamic_cast<Actions::Attack&>(action);
			ActionInProgress = &action;
			PreUsePhase(action, InBattle);
			
			UsePhase(action, InBattle);
			
			PostUsePhase(action, InBattle);
			ActionInProgress = nullptr;
		}
		
		void Mechanics::PreUsePhase(Actions::Action& action, bool InBattle /* = true */)
		{
			auto puse = action.GetComponentAs<PreUseComponent*>(PreUseIndex);
			if (puse != nullptr)
			{
				puse->PreUse(action, *this, InBattle);
			}
			auto userset = action.Users.GetGroup();
			userset.insert(action.Targets.GetGroup().begin(), action.Targets.GetGroup().end());
			auto pse = GetEffectsWithCallCondition(CallCondition::PreUse, userset, !action.IgnoreTargetSE, !action.IgnoreUserAbil);
			for (auto effect = pse.begin(); effect != pse.end(); ++effect)
			{
				auto pusecomp = (*effect)->GetComponentAs<PreUseComponent*>(PreUseIndex);
				if (pusecomp != nullptr)
				{
					pusecomp->PreUse(action, *this, InBattle);
				}
				else
				{
					auto pmod = (*effect)->GetComponentAs<Actions::ActionModifierComponent*>(PreUseIndex);
					if (pmod != nullptr)
					{
						pmod->ModifyAction(action, *this);
					}
				}
			}
		}
		
		void Mechanics::PostUsePhase(Actions::Action& action, bool InBattle /* = true */)
		{
			//action.PushActionToTargets();
			for (auto target = action.Targets.GetGroup().begin(); target != action.Targets.GetGroup().end(); ++target)
			{
				auto localAct = (*target).second.action;
				auto use = localAct->GetComponentAs<PostUseComponent*>("UseComponent");
				if (use != nullptr)
				{
					use->PostUse(*localAct, *this, InBattle);
				}
				else
				{

				}
				
			}
			
		}

		void Mechanics::ActionStatKeeper(boost::shared_ptr<Actions::Action> action)
		{
			for (auto it = action->Users.GetGroup().begin(); it != action->Users.GetGroup().end(); ++it)
			{
				it->second.AttachedBattleCharacter->GetActionUseHistory().AddToHistory(action);
				//(*user).second.AttachedBattleCharacter->GetActionUseHistory().A
				//user.second->
				//(*user).second.AttachedBattleCharacter->
				//user->second.AttachedBattleCharacter->GetActionHistory().=
			}
		}
		
		void Mechanics::UsePhase(Actions::Action& action, bool InBattle)
		{
			auto effects = GetEffectsWithCallCondition(CallCondition::OutgoingAttack, action.Users.GetGroup(), !action.IgnoreTargetSE, !action.IgnoreTargetAbil);
			for (auto effect = effects.begin(); effect != effects.end(); ++effect)
			{
				auto pmod = (*effect)->GetComponentAs<Actions::ActionModifierComponent*>(OutgoingAttackIndexer);
				if (pmod != nullptr)
				{
					pmod->ModifyAction(action, *this);
				}
			}
			//Need to get all users party members, the subtract out users
			auto userset = action.Users.GetGroup();
			std::set<Character::BaseCharacter*> UserTeamMates;
			
			for (auto user = userset.begin(); user != userset.end(); ++user)
			{
				auto bchar = user->second.AttachedCharacter;
				if (bchar != nullptr)
				{
					for (auto teammate = bchar->GetParty()->GetPartyMembers().begin(); teammate != bchar->GetParty()->GetPartyMembers().end(); ++teammate)
					{
						//UserTeamMates.insert((*teammate).second);
					}
				}
			}

			auto pse = GetEffectsWithCallCondition(CallCondition::PartyMemberOutgoingAttack, userset, !action.IgnoreUserSE, !action.IgnoreUserAbil);
			for (auto effect = pse.begin(); effect != pse.end(); ++effect)
			{
				auto pmod = (*effect)->GetComponentAs<Actions::ActionModifierComponent*>(FinalizeTargettingIndexer);
				if (pmod != nullptr)
				{
					pmod->ModifyAction(action, *this);
				}
			}



			//userset = action.Users.GetGroup();
			pse = GetEffectsWithCallCondition(CallCondition::FinalizingTargets, userset, !action.IgnoreUserSE, !action.IgnoreUserAbil);
			auto tse = GetEffectsWithCallCondition(CallCondition::FinalizingTargets, action.Targets.GetGroup(), !action.IgnoreTargetSE, !action.IgnoreTargetAbil);
			pse.insert(pse.end(), tse.begin(), tse.end());
			std::sort(pse.begin(), pse.end(), [](const StatusEffects::StatusEffect* a, const StatusEffects::StatusEffect* b) -> bool { return a->GetPriority() > b->GetPriority(); }); 
			//userset.insert(action.Targets.GetGroup().begin(), action.Targets.GetGroup().end());

			//std::sort(pse.begin(), pse.end(), [](const StatusEffects::StatusEffect* a, const StatusEffects::StatusEffect* b) -> bool { return b->GetPriority() > a->GetPriority(); }); 
			//pse = GetEffectsWithCallCondition(CallCondition::FinalizingTargets, userset, !action.IgnoreTargetSE, !action.IgnoreUserAbil);
			for (auto effect = pse.begin(); effect != pse.end(); ++effect)
			{
				auto pmod = (*effect)->GetComponentAs<Actions::ActionModifierComponent*>(FinalizeTargettingIndexer);
				//pmod->SetOwner(*effect);
				if (pmod != nullptr)
				{
					pmod->ModifyAction(action, *this);
				}
			}

			action.PushActionToTargets();


			//Need to implement looking at party members have incoming attack



	/*		userset = action.Targets.GetGroup();
			auto pse = GetEffectsWithCallCondition(CallCondition::FinalizingTargets, userset, !action.IgnoreTargetSE, !action.IgnoreUserAbil);
			for (auto effect = pse.begin(); effect != pse.end(); ++effect)
			{
				auto pmod = (*effect)->GetComponentAs<Actions::ActionModifierComponent*>(IncomingAttackIndexer);
				if (pmod != nullptr)
				{
					pmod->ModifyAction(action, *this);
				}
			}*/


			for (auto target = action.Targets.GetGroup().begin(); target != action.Targets.GetGroup().end(); ++target)
			{
				auto localAct = (*target).second.action;
				localAct->Targets.AddCharacter(target->second.AttachedCharacter);
				std::vector<Character::BaseCharacter*> targetSet;
				targetSet.push_back(target->second.AttachedCharacter);
				auto tarSE = GetEffectsWithCallCondition(CallCondition::IncomingAttack, targetSet, !localAct->IgnoreTargetSE, !localAct->IgnoreTargetAbil);
				for (auto effect = tarSE.begin(); effect != tarSE.end(); ++effect)
				{
					auto pmod = (*effect)->GetComponentAs<Actions::ActionModifierComponent*>(IncomingAttackIndexer);
					if (pmod != nullptr)
					{
						pmod->ModifyAction(*localAct, *this);
					}
				}
				auto use = localAct->GetComponentAs<UseComponent*>("UseComponent");
				if (use != nullptr)
				{
					use->Use(*localAct, *this, InBattle);
				}
				else
				{
					bool hit = IsHit(*target->second.AttachedCharacter, *localAct);
					localAct->SetActionHits(hit);
					if (hit)
					{
						auto atk = dynamic_cast<Actions::Attack*>(localAct.get());
						if (atk != nullptr)
						{
							atk->SetAttackCritical(IsCritical(*target->second.AttachedCharacter, *atk));
							atk->SetCalculatedDamage(CalculateDamage(*target->second.AttachedCharacter, *atk));
						}
					}
				}
				tarSE = GetEffectsWithCallCondition(CallCondition::ApplyingDamage, targetSet, !localAct->IgnoreTargetSE, !localAct->IgnoreTargetAbil);
				for (auto effect = tarSE.begin(); effect != tarSE.end(); ++effect)
				{
					auto pmod = (*effect)->GetComponentAs<Actions::ActionModifierComponent*>(DamageFinalizerIndex);
					//pmod->SetOwner(*effect);
					if (pmod != nullptr)
					{
						//This modifier should exclusively change the calculated damage of the attack
						pmod->ModifyAction(action, *this);
					}
				}
			}
			
		}

		bool Mechanics::IsHit(Character::BaseCharacter& target, Actions::Action& action)
		{
			auto hitoverride = action.GetComponentAs<HitComponent*>("HitComponent");
			if (hitoverride != nullptr)
			{
				return hitoverride->IsHit(target, action, *this);
			}
			else
			{
				return ApplyHitFormula(target, action);
			}
			return false;
		}
		const float minchance = 0.12f;
		bool Mechanics::ApplyHitFormula(Character::BaseCharacter& target, Actions::Action& action)
		{
			bool Hit = false;
			float actionaccuracy = action.GetAccuracy();
			float useraccuracy = 0.75f;
			float runningaccuracy = 0;
			auto usercount = 0;
			for (auto it = action.Users.GetGroup().begin(); it != action.Users.GetGroup().end(); ++it)
			{
				auto sm = (*it).second.AttachedCharacter->GetComponentAs<Character::StatsManager*>("StatsManager");
				if (sm != nullptr)
				{
					runningaccuracy += sm->GetBattleStat(Character::Stat::Accuracy);
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
			float chance = std::max(useraccuracy * action.GetAccuracy() - evasion, minchance);
			Hit = chance >= GenerateFloat(0.f, 1.f);
			return Hit;
		}
		bool Mechanics::IsCritical(Character::BaseCharacter& target, Actions::Action& action)
		{
			auto critoverride = action.GetComponentAs<CriticalHitComponent*>("CriticalHitComponent");
			if (critoverride != nullptr)
			{
				return critoverride->IsCritical(target, action, *this);
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
			if (!action.HasFlag("NoCrits"))
			{
				if (!action.HasFlag("AlwaysCrits"))
				{
					auto atk = dynamic_cast<Actions::Attack*>(&action);
					if (atk != nullptr)
					{
						float critChance = atk->GetCriticalChance();
						return critChance >= GenerateFloat(0.f, 1.f);
					}
				}
				else
				{
					critical = true;
				}
			}
			return critical;
		}
		int Mechanics::CalculateDamage(Character::BaseCharacter& target, Actions::Action& action)
		{
			auto dmgoverride = action.GetComponentAs<DamageCalculationComponent*>("DamageCalculationComponent");
			if (dmgoverride != nullptr)
			{
				return dmgoverride->CalculateDamage(action, target, *this);
			}
			else
			{
				return ApplyDamageFormula(target, action);
			}
		}
		int Mechanics::ApplyDamageFormula(Character::BaseCharacter& target, Actions::Action& action)
		{
			float eff = DetermineElementalMultiplier(target, action);
			float split = DetermineDamageSplit(action, ActionInProgress != nullptr ? ActionInProgress->Targets.GroupSize() : 1, true);

			int AtkStat = 0;
			int DefStat = 0;
			int AtkRating = 100;
			int ArmorRating = 100;
			auto statExtract = action.GetComponentAs<AtkDefStatComponent*>("StatExtraction");
			if (statExtract != nullptr)
			{
				AtkStat = statExtract->GetAttackerStat(action, target, *this);
				DefStat = statExtract->GetDefenderStat(action, target, *this);
			}
			else
			{
				if (action.Users.GroupSize() > 1)
				{
					for (auto it = action.Users.GetGroup().begin(); it != action.Users.GetGroup().end(); ++it)
					{
						auto sm = it->second.AttachedCharacter->GetComponentAs<Character::StatsManager*>("StatsManager");
						auto atk = dynamic_cast<Actions::Attack*>(&action);
						if (atk != nullptr)
						{
							AtkStat += static_cast<int>(atk->GetPhysicalWeight() * static_cast<float>(sm->GetBattleStat(Character::Stat::Strength)) + atk->GetMagicWeight() * static_cast<float>(sm->GetBattleStat(Character::Stat::Magic)));
						}
						else
							AtkStat += sm->GetBattleStat(Character::Stat::Strength);
					}
					AtkStat /= action.Users.GroupSize();
				}

				auto sm = target.GetComponentAs<Character::StatsManager*>("StatsManager");
				auto atk = dynamic_cast<Actions::Attack*>(&action);
				if (atk != nullptr)
				{
					DefStat = static_cast<int>(atk->GetPhysicalWeight() * static_cast<float>(sm->GetBattleStat(Character::Stat::Strength)) + atk->GetMagicWeight() * static_cast<float>(sm->GetBattleStat(Character::Stat::Magic)));
				}
				else
					DefStat = sm->GetBattleStat(Character::Stat::Strength);

				//Extract Weapon and armor data here
			}





			return 0;
		}
		void Mechanics::ReadyCharacter(Character::BaseCharacter& character, BattleCharacterComponent& battlecharactercomponent, BattleField& field)
		{

		}

		std::vector<StatusEffects::StatusEffect*> Mechanics::GetEffectsWithCallCondition(CallCondition cc, std::vector<Actions::ActionUserTarget>& characters, bool IncludeSE, bool IncludeAbil)
		{
			return std::vector<StatusEffects::StatusEffect*>();
		}

		std::vector<StatusEffects::StatusEffect*> Mechanics::GetEffectsWithCallCondition(CallCondition cc, std::vector<Character::BaseCharacter*>& characters, bool IncludeSE, bool IncludeAbil)
		{
			return std::vector<StatusEffects::StatusEffect*>();
		}

		std::vector<StatusEffects::StatusEffect*> Mechanics::GetEffectsWithCallCondition(CallCondition cc, boost::unordered_map<std::string, Actions::ActionUserTarget>& characters, bool IncludeSE, bool IncludeAbil)
		{
			return std::vector<StatusEffects::StatusEffect*>();
		}

		int Mechanics::GenerateInt(const int min, const int max, float bias)
		{
			if (RandomsEnabled)
			{
				if (bias >= 0.99f && bias <= 1.01f)
				{
					boost::uniform_real<> uni(min, max);
					return uni(RNG);
				}
			}
			return static_cast<int>((min + max) * 0.5);
		}

		float Mechanics::GenerateFloat(const float min, const float max, float bias)
		{
			if (RandomsEnabled)
			{
				if (bias >= 0.99f && bias <= 1.01f)
				{
					boost::uniform_real<> uni(min, max);
					return uni(RNG);
				}
			}
			return (min + max) * 0.5f;
		}

		float Mechanics::DetermineElementalMultiplier(Character::BaseCharacter& character, Actions::Action& action)
		{
			if(action.HasFlag("IgnoreElements"))
				return 1.f;
			auto eleWeight = action.GetComponentAs<Components::ElementWeightComponent*>("ElementalWeightComponent");
			if (eleWeight != nullptr)
			{
				auto DefenderEle = character.GetComponentAs<Components::ElementEffectivenessComponent*>("ElementEffectivenessComponent");
				if (DefenderEle != nullptr)
				{
					float eff = 0.f;
					eleWeight->Moderate();
					for (auto element = eleWeight->GetElementWeights().begin(); element != eleWeight->GetElementWeights().end(); ++element)
					{
						eff += element->second * DefenderEle->GetEffectiveness(element->first);
					}
					return eff;
				}
			}
			return 1.f;
		}

		float Mechanics::DetermineDamageSplit(Actions::Action& action, int Targets, bool inBattle)
		{
			auto splitOverride = action.GetComponentAs<DamageSplitComponent*>("DamageSplitComponent");
			if (splitOverride != nullptr)
			{
				return splitOverride->DetermineDamageSplit(action, Targets, inBattle);
			}
			else
			{
				if (Targets < 2)
					return 1.f;
				else
					return 1.f / std::sqrt(float(Targets));
			}
		}

		bool Mechanics::AreRandomsEnabled() const
		{
			return RandomsEnabled;
		}

		void Mechanics::SetRandomEnabled(const bool Enabled)
		{
			RandomsEnabled = Enabled;
		}

		BattleField* Mechanics::GetField() const
		{
			return Field;
		}

		int Mechanics::PhysicalDamageForumla(Actions::Action& action, Character::BaseCharacter& character, const int AtkStat, const int DefStat, const int AtkRating, const int ArmorRating)
		{
			for (auto character = action.Users.GetGroup().begin(); character != action.Users.GetGroup().end(); ++character)
			{

			}

			if (!action.HasFlag("IgnoreArmor"))
			{

			}
			return 0;
		}

		int Mechanics::MagicDamageForumla(Actions::Action& action, Character::BaseCharacter& character, const int AtkStat, const int DefStat, int AtkRating, int ArmorRating)
		{
			return 10;
		}


		Mechanics::RawClonePtr Mechanics::RawClone() const
		{
			return new Mechanics(*this);
		}
	}
}