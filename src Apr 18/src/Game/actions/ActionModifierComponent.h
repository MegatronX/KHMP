#pragma once
#ifndef _ACTIONMODIFIERCOMPONENT_H_
#define _ACTIONMODIFIERCOMPONENT_H_
#include <components/Component.h>
namespace Game
{
	namespace Battle
	{
		class Mechanics;
	}
	namespace Actions
	{
		class Action;
		class ActionModifierComponent : public Components::Component
		{
		public:
			ActionModifierComponent() : Component()
			{

			}
			ActionModifierComponent(Entity* owner) : Components::Component(owner, "ActionModifierComponent" + owner->GetName(), "ActionModiferComponent")
			{
				
			}
			ActionModifierComponent(Entity* owner, const std::string& name) : Components::Component(owner, name, "ActionModifierComponent")
			{

			}
			virtual bool ModifyAction(Action& action, Battle::Mechanics& mechanics)
			{
				return false;
			}

			virtual RawClonePtr RawClone() const override
			{
				return new ActionModifierComponent(*this);
			}
		};
	}
}

#endif