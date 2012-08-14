#pragma once
#include <character/Party.h>
#include <character/BaseCharacter.h>
#include <character/PlayerCharacterComponent.h>
namespace Game
{
	class GameInstance;
	class GameState;
	namespace Character
	{
		class PlayerParty : public PartyInterface<BaseCharacter>
		{
		public:
			PlayerParty();
			void AddCharacter(const std::string& name, boost::shared_ptr<BaseCharacter> character);

			void RemoveCharacter(const std::string& name);

			PartyInterface<PlayerCharacterComponent> GetPlayerCharacterParty();

		protected:
			PartyInterface<PlayerCharacterComponent> PlayerCharacterComponents;
			static std::string pcompindex;
			friend class GameInstance;
			friend class GameState;
		};

		
	}
	
}