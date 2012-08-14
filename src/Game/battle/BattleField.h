#pragma once
#ifndef _BATTLEFIELD_H_
#define _BATTLEFIELD_H_
#include <Entity.h>
#include <character/Party.h>
#include <battle/BattleParty.h>
#include <battle/BattleCharacterComponent.h>
namespace Game
{
	namespace Battle
	{
		class Mechanics;
		class BattleField : public Entity
		{
		public:
			//BattleField(Character::bparty_ptr playerParty = Character::bparty_ptr(), Character::bparty_ptr enemyParty = Character::bparty_ptr());

			BattleField();

			BattleField(Character::bparty_ptr playerParty, Character::bparty_ptr enemyParty, const std::string& MechanicsType = "BaseMechanics", const std::string& TurnGenType = "ATB");

			BattleField(Character::bparty_ptr playerParty, const std::vector<Character::bparty_ptr>& enemyParties, const std::string& MechanicsType = "BaseMechanics", const std::string& TurnGenType = "ATB");

			BattleField(Character::bparty_ptr playerParty, const boost::unordered_map<std::string, Character::bparty_ptr>& enemyParties, const std::string& MechanicsType = "BaseMechanics", const std::string& TurnGenType ="ATB");

			virtual void InitBattle();

			virtual void PreBattlePhase();

			virtual void BattlePhase();

			virtual void PostBattlePhase();

			virtual Components::Component* GetComponent(const std::string& index) override;

			void AddEnemyParty( Character::bparty_ptr basePart, battleparty_ptr btlParty, const std::string& index);

			void SetPlayerParty(Character::bparty_ptr bp);

			void SetPlayerParty(battleparty_ptr btlp);

			void SetPlayerParty(Character::bparty_ptr bp, battleparty_ptr btlp);

			Character::bparty_ptr GetPlayerParty() const;

			battleparty_ptr GetBattlePlayerParty() const;

			Character::bparty_ptr GetEnemyParty(const std::string& index) const;

			battleparty_ptr GetBattleEnemyParty(const std::string& index) const;

			Mechanics& GetMechanics();

			TurnGenerator* GetTurnGenerator();
		private:
			Character::bparty_ptr PlayerParty;
			battleparty_ptr PlayerBattleParty;

			boost::shared_ptr<TurnGenerator> TurnGen;

			boost::unordered_map<std::string, Character::bparty_ptr > EnemyParties;
			boost::unordered_map<std::string, battleparty_ptr > EnemyBattleParties;

			boost::shared_ptr<Mechanics> BattleMechanics;

			static boost::shared_ptr<Mechanics> FallbackMechanics;
		};

		typedef boost::shared_ptr<BattleField> bfield_ptr;

		/*extern boost::shared_ptr<BattleField> MakeDefaultBattleField();

		extern boost::shared_ptr<BattleField> MakeDefaultBattleField(Character::bparty_ptr playerParty = Character::bparty_ptr(), Character::bparty_ptr enemyParty = Character::bparty_ptr());
		*/
	}
}

#endif