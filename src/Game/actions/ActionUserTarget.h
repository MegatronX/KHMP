#pragma once

//#include <actions/Action.h>
#include <character/BaseCharacter.h>
#include <character/Party.h>
#include <battle/BattleParty.h>
#include <battle/BattleCharacterComponent.h>
namespace Game
{
	namespace Actions
	{
		class Action;
		struct ActionUserTarget
		{
			Battle::BattleCharacterComponent* AttachedBattleCharacter;
			Character::BaseCharacter* AttachedCharacter;
			boost::shared_ptr<Action> action;
			ActionUserTarget()
			{
			}
			ActionUserTarget(Battle::BattleCharacterComponent* bchar) : AttachedBattleCharacter(bchar)
			{
				if (bchar != nullptr)
				{
					AttachedCharacter = dynamic_cast<Character::BaseCharacter*>((bchar->GetOwner()));
				}
			}
			ActionUserTarget(Character::BaseCharacter* participant) : AttachedCharacter(participant)
			{
				if (participant != nullptr)
				{
					auto bchar = participant->GetComponentAs<Battle::BattleCharacterComponent*>("BattleCharacterComponent");
					if (bchar != nullptr)
						AttachedBattleCharacter = bchar;
				}
			}

			void SetCharacter(Character::BaseCharacter* character)
			{
				AttachedCharacter = character;

			}

			bool operator==(const ActionUserTarget& user)
			{
				return ((AttachedCharacter != NULL && user.AttachedCharacter != NULL &&
					(AttachedCharacter->GetID() == user.AttachedCharacter->GetID())) ||
					(AttachedBattleCharacter != NULL && user.AttachedBattleCharacter != NULL &&
					(AttachedBattleCharacter->GetUID() == user.AttachedBattleCharacter->GetUID())));
			}
			bool operator!=(const ActionUserTarget& action)
			{
				return !(*this == action);
			}

		};

		class ActionGroup : public Entity
		{
		public:
			ActionGroup() : InvalidCharacterCount(0)
			{

			}
			ActionGroup(Character::BaseParty& sourceParty) : InvalidCharacterCount(0)
			{

			}
			ActionGroup(Battle::BattleParty& sourceParty) : InvalidCharacterCount(0)
			{

			}
			ActionGroup(Character::BaseCharacter& character) : InvalidCharacterCount(0)
			{

			}

			void AddCharacter(Character::BaseCharacter* character, bool Validate = true)
			{
				if (character != nullptr)
				{
					Group[character->GetName()] = ActionUserTarget(character);
				}
				
			}

			void AddBattleCharacter(Battle::BattleCharacterComponent* bcharacter, bool Validate = true)
			{
				if (bcharacter != nullptr)
				{
					auto character = dynamic_cast<Character::BaseCharacter*>(bcharacter->GetOwner());
					AddCharacter(character, Validate);
				}
			}

			boost::unordered_map<std::string, ActionUserTarget>& GetGroup()
			{
				return Group;
			}
			int GroupSize() const
			{
				return Group.size();
			}
			ActionUserTarget* GetFirst()
			{
				return &((Group.begin()->second));
			}

			ActionUserTarget* GetMember(const std::string& index)
			{
				auto it = Group.find(index);
				if (it != Group.end())
					return &(it->second);
				return nullptr;
			}

			bool AddMember(ActionUserTarget& ref)
			{
				if (ref.AttachedCharacter != nullptr)
				{
					return AddMember(ref, ref.AttachedCharacter->GetName());
				}
				return false;
			}

			bool AddMember(ActionUserTarget* ref)
			{
				if (ref != nullptr && ref->AttachedCharacter != nullptr)
				{
					return AddMember(*ref, ref->AttachedCharacter->GetName());
				}
				return false;
			}

			bool AddMember(ActionUserTarget& ref, const std::string& index)
			{
				Group[index] = ActionUserTarget(ref);
				return true;
			}


			bool RemoveMember(const std::string& index)
			{
				auto it = Group.find(index);
				if (it != Group.end())
				{
					Group.erase(it);
					return true;
				}
				return false;
			}

			bool RemoveMember(const ActionUserTarget* targ)
			{
				if (targ != nullptr)
				{
					for (auto it = Group.begin(); it != Group.end(); ++it)
					{
						if (it->second == *targ)
						{
							Group.erase(it);
							return true;
						}
					}
				}
				return false;
			}

			void Clear()
			{
				Group.clear();
			}

			ActionUserTarget* GetAt(int index)
			{
				if (index > Group.size() - 1)
					return nullptr;
				int tindex = 0;
				auto it = Group.begin();
				for (; it != Group.end() && tindex < index; ++tindex, ++it)
				{

				}
				return &(it->second);
			}

			ActionUserTarget& operator[](const std::string& index)
			{
				return Group[index];
			}

			
		protected:
		private:
			int InvalidCharacterCount;
			//std::vector<ActionUserTarget> Group;
			boost::unordered_map<std::string, ActionUserTarget> Group;
		};

		/*class ActionTargets : public Entity
		{
		public:
			ActionTargets(Character::Party& sourceParty)
			{

			}
			ActionTargets(Battle::BattleParty& sourceParty)
			{

			}
			ActionTargets(Character::BaseCharacter& character)
			{
				Targets.push_back(ActionTarget(&character));
			}

			void AddTarget(Character::BaseCharacter* character, bool Validate = true)
			{

			}

			void AddBattleTarget(Battle::BattleCharacter* bcharacter, bool Validate = true)
			{

			}

			std::vector<ActionTarget>& GetTargets()
			{
				return Targets;
			}

			ActionTarget& GetFirst()
			{
				return *(Targets.begin());
			}
			ActionTarget& GetTarget(const int index)
			{
				return Targets[index];
			}

			ActionTarget& operator[](const int index)
			{
				return Targets[index];
			}
		protected:
		private:
			std::vector<ActionTarget> Targets;
		};*/


	}
}