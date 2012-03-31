#include "BaseCharacter.h"

namespace Game
{
	namespace Character
	{
		
		Components::Component* BaseCharacter::GetComponent(const std::string& index)// const
		{
			const static int EleHash = StringHasher("ElementEffectivenessComponent");
			const static int StatusHash = StringHasher("StatusEffectivenessComponent");
			auto indexHash = StringHasher(index);
			if (EleHash == indexHash)
			{
				return const_cast<Components::ElementEffectivenessComponent*>(&ElementEffectsComponent);
			}
			else if (StatusHash == indexHash)
			{
				return const_cast<Components::StatusEffectivenessComponent*>(&StatusEffectsComponent);
			}
			else
			{
				return Entity::GetComponent(index);
			}
			return nullptr;
		}
		Entity::RawClonePtr BaseCharacter::RawClone() const
		{
			return new BaseCharacter(*this);
		}

		Party* BaseCharacter::GetParty() const
		{
			return AttachedParty;
		}

	}
}