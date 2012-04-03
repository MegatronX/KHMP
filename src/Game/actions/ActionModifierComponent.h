#pragma once
#ifndef _ACTIONMODIFIERCOMPONENT_H_
#define _ACTIONMODIFIERCOMPONENT_H_
#include <components/Component.h>
namespace Game
{
	namespace Actions
	{
		class Action;
	}
	namespace Battle
	{
		class Mechanics;
	}
	namespace Action
	{
		class ActionModifierComponent : public Components::Component
		{
		public:
			bool ModifyAction(Actions::Action& action, Battle::Mechanics& mechanics)
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