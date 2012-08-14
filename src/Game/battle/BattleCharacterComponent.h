#pragma once
#ifndef _BATTLECHARACTERCOMPONENT_H_
#define _BATTLECHARACTERCOMPONENT_H_
#include <components/Component.h>
//#include <character/Party.h>
#include <character/BaseCharacter.h>
#include <battle/ActionHistory.h>
#include <array>
#include <boost/signals2.hpp>
namespace Game
{
	class Entity;
	namespace Character
	{
	//	class BaseCharacter;
	}
	namespace Battle
	{
		const int ModeCount = 2;
		const int MaxTimer = 25500;
		enum BattleMode
		{
			Real = 0,
			Sim = 1
		};
		class BattleCharacterComponent;

		typedef boost::signals2::signal<void (BattleCharacterComponent*, BattleMode) > TimerOverflowSignal;

		class BattleCharacterComponent : public Components::Component
		{
		public:
			BattleCharacterComponent(Entity* owner, Character::PartyInterface<BattleCharacterComponent>* bparty = nullptr, Character::BaseParty* baseparty = nullptr, const std::string& ctype = "BattleCharacterComponent") : Component(owner, owner != nullptr ? owner->GetName() + ctype : "NoOwner" + ctype, ctype), CharacterMode(Real), BParty(bparty), CharacterBaseParty(baseparty), stats(nullptr)
			{
				auto ch = dynamic_cast<Character::BaseCharacter*>(owner);
				if (ch != nullptr)
				{
					stats = &ch->GetStatsManager();
				}
				for (unsigned int i = 0; i < TickCounts.size(); ++i)
				{
					TickCounts[i] = 0;
					OverflowRatio[i] = 0;
				}
			}
			BattleCharacterComponent(const BattleCharacterComponent& bc) : Component(bc), TickCounts(bc.TickCounts), OverflowRatio(bc.OverflowRatio), CharacterMode(bc.CharacterMode), stats(bc.stats), BParty(bc.BParty),
				CharacterBaseParty(bc.CharacterBaseParty)
			{

			}
			Character::PartyInterface<BattleCharacterComponent>* GetBattleParty() const
			{
				return BParty;
			}
			Character::BaseParty* GetBaseParty() const
			{
				return CharacterBaseParty;
			}
			virtual RawClonePtr RawClone() const override
			{
				return new BattleCharacterComponent(*this);
			}
			
			BattleMode GetCharacterMode() const
			{
				return CharacterMode;
			}
			void SetCharacterMode(const BattleMode mode)
			{
				CharacterMode = mode;
			}

			int GetTimerValue() const
			{
				return TickCounts[CharacterMode];
			}
			int GetTimerValue(const BattleMode mode) const
			{
				return TickCounts[mode];
			}
			float GetTimerRatio() const
			{
				return OverflowRatio[CharacterMode];
			}
			float GetTimerRatio(const BattleMode mode) const
			{
				return OverflowRatio[mode];
			}
			/*boost::signals2::connection AddTimerOverflowEventHandler(const TimerOverflowSignal::slot_type& handler)
			{
				return TimerOverflow.connect(handler);
			}*/
			void IncrementTimer(const int inc)
			{
				TickCounts[CharacterMode] += inc;
				if ((TickCounts[CharacterMode] + stats->GetBattleStat(Character::Stat::Speed)) > MaxTimer)
				{
					int x = 0;
				}
				while (TickCounts[CharacterMode] >= MaxTimer)
				{
					//TickCounts[CharacterMode] -= MaxTimer;
					if (stats != nullptr)
					{
						if (stats->GetBattleStat(Character::Stat::Speed) > 0)
						{
							if (this->GetOwner()->GetName() == "Arian")
							{
								int x = 0;
							}
							OverflowRatio[CharacterMode] = static_cast<float>(TickCounts[CharacterMode] - MaxTimer) / static_cast<float>(stats->GetBattleStat(Character::Stat::Speed));
							if (OverflowRatio[CharacterMode] >= 1.f)
							{
								int y = 0;
								float sp = static_cast<float>(stats->GetBattleStat(Character::Stat::Speed));
								y = 10;
								std::cout << sp << std::endl;
							}
						}
						else
						{
							OverflowRatio[CharacterMode] = 0;
						}
						
					}
					TimerOverflow(this, CharacterMode);
				}
			}

			ActionHistory& GetActionUseHistory()
			{
				return ActionUseHistory;
			}

			ActionHistory& GetActionBitByHistory()
			{
				return ActionHitByHistory;
			}

			Character::StatsManager* GetStatManager()
			{
				return stats;
			}

			boost::signals2::connection AddTimerOverflowEventHandler(const TimerOverflowSignal::slot_type& event)
			{
				return TimerOverflow.connect(event);
			}

		protected:
			TimerOverflowSignal TimerOverflow;

			bool AIControlled;

			std::array<int, ModeCount> TickCounts;
			std::array<float, ModeCount> OverflowRatio;

			BattleMode CharacterMode;
			Character::StatsManager* stats;
			Character::PartyInterface<BattleCharacterComponent>* BParty;
				//BattleParty* BParty;
			Character::BaseParty* CharacterBaseParty;
			friend class Mechanics;
			friend class TurnGenerator;

			ActionHistory ActionUseHistory;
			ActionHistory ActionHitByHistory;
		};


		typedef Character::PartyInterface<BattleCharacterComponent> BattleParty;
		typedef boost::shared_ptr<BattleParty> battleparty_ptr;
	}
}
#endif