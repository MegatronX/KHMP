#include "BattleField.h"
#include <battle/mechanics/BaseMechanics.h>
#include <battle/mechanics/ATBTurnGenerator.h>

#include <boost/algorithm/string.hpp>

namespace Game
{
	namespace Battle
	{
		const static std::string BattleComponentIndex("BattleCharacterComponent");
		boost::shared_ptr<Mechanics> BattleField::FallbackMechanics(new Mechanics(nullptr));
		/*BattleField::BattleField(Character::bparty_ptr playerParty, Character::bparty_ptr enemyParty) : Entity("Battlefield", EntityTypes::Battlefield), PlayerParty(playerParty), BattleMechanics(new BaseMechanics(this))
		{
			if (enemyParty.get() != nullptr)
			{
				EnemyParties[enemyParty->GetName()] = enemyParty;
			}
			
		}*/

		BattleField::BattleField() : Entity("Battlefield", EntityTypes::Battlefield)
		{

		}

		BattleField::BattleField(Character::bparty_ptr playerParty, Character::bparty_ptr enemyParty, const std::string& MechanicsType, const std::string& TurnGenType) : Entity("Battlefield", EntityTypes::Battlefield), PlayerParty(playerParty)
		{
			if (enemyParty.get() != nullptr)
			{
				EnemyParties[enemyParty->GetName()] = enemyParty;
			}

			if (MechanicsType == "BaseMechanics")
			{
				BattleMechanics = boost::shared_ptr<Mechanics>(new BaseMechanics(this));
			}
			else
			{
				BattleMechanics = FallbackMechanics;
			}

			auto lgen = boost::algorithm::to_lower_copy(TurnGenType);
			if (lgen == "atbturngenerator" || lgen == "atb")
			{
				TurnGen = boost::shared_ptr<TurnGenerator>(new ATBTurnGenerator(this));
			}
			else
			{

			}

		}

		BattleField::BattleField(Character::bparty_ptr playerParty, const std::vector<Character::bparty_ptr>& enemyParties, const std::string& MechanicsType, const std::string& TurnGenType) : Entity("Battlefield", EntityTypes::Battlefield), PlayerParty(playerParty)
		{
			for (auto party = enemyParties.begin(); party != enemyParties.end(); ++party)
			{
				if ((*party).get() != nullptr)
				{
					EnemyParties[(*party)->GetName()] = *party;
				}
			}

			if (MechanicsType == "BaseMechanics")
			{
				BattleMechanics = boost::shared_ptr<Mechanics>(new BaseMechanics(this));
			}
			else
			{
				BattleMechanics = FallbackMechanics;
			}

			auto lgen = boost::algorithm::to_lower_copy(TurnGenType);
			if (lgen == "atbturngenerator" || lgen == "atb")
			{
				TurnGen = boost::shared_ptr<TurnGenerator>(new ATBTurnGenerator(this));
			}
			else
			{

			}
		}

		BattleField::BattleField(Character::bparty_ptr playerParty, const boost::unordered_map<std::string, Character::bparty_ptr>& enemyParties, const std::string& MechanicsType, const std::string& TurnGenType) : Entity("Battlefield", EntityTypes::Battlefield), PlayerParty(playerParty), EnemyParties(enemyParties)
		{
			if (MechanicsType == "BaseMechanics")
			{
				BattleMechanics = boost::shared_ptr<Mechanics>(new BaseMechanics(this));
			}
			else
			{
				BattleMechanics = FallbackMechanics;
			}
			auto lgen = boost::algorithm::to_lower_copy(TurnGenType);
			if (lgen == "atbturngenerator" || lgen == "atb")
			{
				TurnGen = boost::shared_ptr<TurnGenerator>(new ATBTurnGenerator(this));
			}
			else
			{

			}
		}

		void BattleField::InitBattle()
		{

		}

		void BattleField::BattlePhase()
		{
			
			if (PlayerBattleParty.get() != nullptr && TurnGen.get() != nullptr)
			{
				for(auto it = PlayerBattleParty->GetPartyMembers().begin(); it != PlayerBattleParty->GetPartyMembers().end(); ++it)
				{
					TurnGen->TrackCharacter(it->second.get());
				}
				for (auto it = EnemyBattleParties.begin(); it != EnemyBattleParties.end(); ++it)
				{
					for (auto eparty = it->second->GetPartyMembers().begin(); eparty != it->second->GetPartyMembers().end(); ++eparty)
					{
						TurnGen->TrackCharacter(eparty->second.get());
					}
				}
			}
		}

		void BattleField::PreBattlePhase()
		{
			PlayerBattleParty = battleparty_ptr(new BattleParty("PlayerBattleParty"));
			if (PlayerParty.get() != nullptr)
			{
				for (auto member = PlayerParty->GetPartyMembers().begin(); member != PlayerParty->GetPartyMembers().end(); ++member)
				{
					if (member->second.get() != nullptr)
					{
						boost::shared_ptr<BattleCharacterComponent> bcharcomp(new BattleCharacterComponent(member->second.get(), PlayerBattleParty.get(), PlayerParty.get()));
						member->second->RegisterComponent(BattleComponentIndex, bcharcomp);
						member->second->SetParty(PlayerParty.get());
						PlayerBattleParty->AddMember(bcharcomp, member->second->GetName());
						BattleMechanics->ReadyCharacter(*(member->second), *bcharcomp, *this);
					}
				}
			}
			for (auto eparty = EnemyParties.begin(); eparty != EnemyParties.end(); ++eparty)
			{
				auto ebparty = battleparty_ptr(new BattleParty(eparty->second->GetName() + "BattleParty"));
				for (auto enemy = eparty->second->GetPartyMembers().begin(); enemy != eparty->second->GetPartyMembers().end(); ++enemy)
				{
					boost::shared_ptr<BattleCharacterComponent> bcharcomp(new BattleCharacterComponent(enemy->second.get(), ebparty.get(), eparty->second.get()));
					enemy->second->RegisterComponent(BattleComponentIndex, bcharcomp);
					enemy->second->SetParty(eparty->second.get());
					//PlayerBattleParty->AddMember(bcharcomp, member->second->GetName());
					ebparty->AddMember(bcharcomp, enemy->second->GetName());
					BattleMechanics->ReadyCharacter(*(enemy->second), *bcharcomp, *this);
				}
				EnemyBattleParties[ebparty->GetName()] = ebparty;
			}
			BattleMechanics->Init();
		}

		void BattleField::PostBattlePhase()
		{

		}

		Components::Component* BattleField::GetComponent(const std::string& index)
		{
			if (index == "Mechanics")
				return BattleMechanics.get();
			else
				return Entity::GetComponent(index);
		}

		void BattleField::AddEnemyParty( Character::bparty_ptr basePart, battleparty_ptr btlParty, const std::string& index)
		{
			EnemyParties[index] = basePart;
			EnemyBattleParties[index] = btlParty;
		}

		void BattleField::SetPlayerParty(Character::bparty_ptr bp)
		{
			PlayerParty = bp;
		}

		void BattleField::SetPlayerParty(battleparty_ptr btlp)
		{
			PlayerBattleParty = btlp;
		}

		void BattleField::SetPlayerParty(Character::bparty_ptr bp, battleparty_ptr btlp)
		{
			PlayerParty = bp;
			PlayerBattleParty = btlp;
		}

		Character::bparty_ptr BattleField::GetPlayerParty() const
		{
			return PlayerParty;
		}

		battleparty_ptr BattleField::GetBattlePlayerParty() const
		{
			return PlayerBattleParty;
		}

		Character::bparty_ptr BattleField::GetEnemyParty(const std::string& index) const
		{
			auto it = EnemyParties.find(index);
			if (it != EnemyParties.end())
			{
				return it->second;
			}
			return Character::bparty_ptr();
		}

		battleparty_ptr BattleField::GetBattleEnemyParty(const std::string& index) const
		{
			auto it = EnemyBattleParties.find(index);
			if (it != EnemyBattleParties.end())
			{
				return it->second;
			}
			return battleparty_ptr();
		}

		Mechanics& BattleField::GetMechanics()
		{
			return *BattleMechanics.get();
		}

		TurnGenerator* BattleField::GetTurnGenerator()
		{
			return TurnGen.get();
		}

		/*bfield_ptr MakeDefaultBattleField()
		{
			auto field = boost::make_shared<BattleField>();
			return field;
		}
		boost::shared_ptr<BattleField> MakeDefaultBattleField(Character::bparty_ptr playerParty, Character::bparty_ptr enemyParty)
		{
			auto field = boost::make_shared<BattleField>(playerParty, enemyParty);
			return field;
		}*/
	}
}