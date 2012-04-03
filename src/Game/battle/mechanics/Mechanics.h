#pragma once
#ifndef _MECHANICS_H_
#define _MECHANICS_H_
#include <cmath>
#include <components/Component.h>
#include <actions/ActiveAction.h>
#include <statuseffects/StatusEffect.h>
//#include "BattleField.h"
namespace Game
{
	namespace Actions
	{
		class Action;
	}
	namespace Character
	{
		class BaseCharacter;
	}
	/*namespace StatusEffects
	{
		class StatusEffect;
	}*/
	namespace Battle
	{
		class BattleField;
		class Mechanics : public Components::Component
		{
		public:
			Mechanics(BattleField* owner);
			virtual bool ApplyStatusEffect(Character::BaseCharacter& target, const std::string& se, int turns, float seApplyRate = 1.0f);
			virtual bool IsHit(Character::BaseCharacter& target, Actions::Action& action);
			virtual bool IsCritical(Character::BaseCharacter& target, Actions::Action& action);
			BattleField* GetField() const;
			virtual RawClonePtr RawClone() const override;
		private:
			BattleField* Field;
		};
		/*namespace Mechanics
		{
			class Mechanics_
			{
			public:

				int BasicPhysicalDamageCalc(const int atkStat, const int defStat, const int atkStr, const int atkReg)
				{
					double Dmg1 = (((atkStat * atkStat * atkStat) / 44) + 32) * (atkStr / atkReg);
					double Def1 = ((defStat - 1000.4) * (defStat - 1000.4)) / 110 + 16;
					double Dmg2 = (pow((Dmg1 * Def1) / 3800.0), (7.0 / 9.0)) + 100 (atkStat / defStat);
					double Dmg3 = (pow(Dmg2), (5.0 / 6.0)) * 2.1;
					return static_cast<int>(Dmg3);
					/*
					Dmg1 = (((AtkStat) ^ 3 / 32) + 32) * (16 / 16)
					Def1 = (((DefStat - 1000.4) ^ 2) / 110) + 16
					Dmg2 = ((Dmg1 * Def1) / 3800) ^ (7 / 9) + 100 * (AtkStat / DefStat)
					Dmg3 = ((DefStat)) ^ 2 / AtkStat
					If (Dmg3 > Dmg2) Then
					Dmg3 = 0
					End If
					Dmg4 = Dmg2 - Dmg3
					
				}
			protected:
			private:
			};
		}*/
	}
}

#endif