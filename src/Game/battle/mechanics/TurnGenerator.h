#pragma once
#ifndef _TURNGENERATOR_H_
#define _TURNGENERATOR_H_
#include <deque>
#include <vector>
#include <Entity.h>
#include <battle/BattleCharacterComponent.h>
#include <boost/signals2.hpp>
namespace Game
{
	namespace Battle
	{
		class BattleField;
		class Mechanics;

		typedef std::deque<BattleCharacterComponent*> TurnQueue;
		typedef std::vector<BattleCharacterComponent*> ReadyList;
		typedef boost::signals2::signal<void (ReadyList)> CharactersReadySignal;
		class TurnGenerator : public Components::Component
		{
		public:
			TurnGenerator(Entity* owner, const std::string& CType = "TurnGenerator");
			TurnGenerator(const TurnGenerator& tg);
			virtual RawClonePtr RawClone() const override;
			virtual void TrackCharacter(BattleCharacterComponent* character);
			virtual bool StopTrackingCharacter(const std::string& name);
			virtual bool StopTrackingCharacter(BattleCharacterComponent* character);

			BattleCharacterComponent* GetCharacter(const std::string& name);

			virtual void GenerateNextCharacter(int GenCounter = 1);

			virtual void TickCharacter(BattleCharacterComponent* character);

			const boost::unordered_map<std::string, BattleCharacterComponent*>& GetUpdateList() const;

			void SetGeneratorMode(const BattleMode mode);

			BattleMode GetGeneratorMode() const;

			boost::signals2::connection AddCharacterReadyEventHandler(const CharactersReadySignal::slot_type& event);

			//static boost::shared_ptr<TurnGenerator> MakeGenerator(const std::string& type);

			virtual ~TurnGenerator();
			//void
		protected:
			virtual void HandleTimerOverflow(BattleCharacterComponent*, BattleMode);

			BattleMode GeneratorMode;

			CharactersReadySignal ReadyCharSignal;

			boost::unordered_map<std::string, BattleCharacterComponent*> UpdateList;
			boost::unordered_map<std::string, boost::signals2::connection> TimerOverflowConnections;

			std::array<ReadyList, ModeCount> ReadyLists;
			std::array<TurnQueue, ModeCount> TurnQueues;
		private:
			

			Mechanics* ownerMechanics;
		};
	}
}

#endif