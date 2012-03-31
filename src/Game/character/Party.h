#pragma once
#ifndef _PARTY_H_
#define _PARTY_H_
#include <Entity.h>
#include <character/BaseCharacter.h>

namespace Game
{
	namespace Character
	{
		template <class T>
		class PartyInterface : public Entity
		{
		public:
			typedef boost::shared_ptr<T> MemberPtr;
			typedef T* MemberRawPtr;
			PartyInterface(const std::string& name) : Entity(name, EntityTypes::CharacterEntity)
			{

			}
			/*virtual void AddMember(MemberPtr member, bool overwriteExisting = false)
			{
				if (member.get() != nullptr)
				{
					auto it = PartyMembers.find(member)
				}
			}*/
			virtual void AddMember(MemberPtr member, const std::string& index, bool overwriteExisting = false)
			{
				if (member.get() != nullptr)
				{
					auto it = PartyMembers.find(index);
					if (it != PartyMembers.end())
					{
						if (overwriteExisting)
						{
							PartyMembers.erase(it);
							PartyMembers[index] = member;
						}
					}
					else
					{
						PartyMembers[index] = member;
					}
				}
			}
			virtual bool RemoveMemberByName(const std::string& name)
			{
				bool Removed = false;
				auto it = PartyMembers.find(name);
				if (it != PartyMembers.end())
				{
					PartyMembers.erase(it);
					Removed = true;
				}
				return Removed;
			}
			virtual void RemoveMemberByMemberPtr(const MemberPtr member)
			{
				
			}

			std::vector<MemberRawPtr> GetPartyMembers() const
			{
				std::vector<MemberRawPtr> chars;
				for(auto it = PartyMembers.begin(); it != PartyMembers.end(); ++it)
				{
					chars.push_back(it->second.get());
				}
				return chars;
			}

		protected:
			boost::unordered_map<std::string, MemberPtr> PartyMembers;
			
		private:

		};


		class Party : public PartyInterface<Character::BaseCharacter>
		{
		public:
			Party(const std::string& name) : PartyInterface(name)
			{

			}

			
		};

		

	}
}

#endif