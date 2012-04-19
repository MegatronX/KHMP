#include "BaseCharacter.h"

namespace Game
{
	namespace Character
	{
		BaseCharacter::BaseCharacter() : Entity("DummyCharacter", CharacterEntity), ElementEffectsComponent(this), 
			SEManager(this), AbilManager(this), SManager(this)
		{

		}
		BaseCharacter::BaseCharacter(const std::string& characterName) : Entity(characterName, CharacterEntity), ElementEffectsComponent(this), 
			SEManager(this), AbilManager(this), SManager(this)
		{

		}
		BaseCharacter::BaseCharacter(const std::string& characterName, int baseStats[Character::StatCount]) : Entity(characterName, CharacterEntity), ElementEffectsComponent(this), 
			SEManager(this), AbilManager(this), SManager(this, baseStats)
		{

		}
		Components::Component* BaseCharacter::GetComponent(const std::string& index)// const
		{
			const static int EleHash = StringHasher("ElementEffectivenessComponent");
			const static int StatusHash = StringHasher("StatusEffectivenessComponent");
			const static int SEMHash = StringHasher("StatusEffectsManager");
			const static int AbilHash = StringHasher("AbilityManager");
			const static int StatsM = StringHasher("StatsManager");
			auto indexHash = StringHasher(index);
			if (EleHash == indexHash)
			{
				return const_cast<Components::ElementEffectivenessComponent*>(&ElementEffectsComponent);
			}
			else if (StatusHash == indexHash)
			{
				return const_cast<Components::StatusEffectivenessComponent*>(&StatusEffectsComponent);
			}
			else if (SEMHash == indexHash)
			{
				return const_cast<StatusEffects::StatusEffectsManager*>(&SEManager);
			}
			else if (AbilHash == indexHash)
			{
				return const_cast<Abilities::AbilityManager*>(&AbilManager);
			}
			else if (StatsM == indexHash)
			{
				return &SManager;
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

		StatusEffects::StatusEffectsManager& BaseCharacter::GetStatusEffectsManager()
		{
			return SEManager;
		}
		Abilities::AbilityManager& BaseCharacter::GetAbilityManager()
		{
			return AbilManager;
		}

		StatsManager& BaseCharacter::GetStatsManager()
		{
			return SManager;
		}
	}
}