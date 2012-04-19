#pragma once
#include <components/UseComponent.h>
#include <boost/python.hpp>
namespace Game
{
	namespace Character
	{
		class BaseCharacter;

	}
	namespace Battle
	{
		class BattleCharacter;
	}
	namespace Scripting
	{

		class UseComponentWrap : public Components::UseComponent
		{
		public:
			UseComponentWrap(PyObject* self_);
			UseComponentWrap(PyObject* self_, const std::string& name, bool hasUse, bool hasBattleUse);
			UseComponentWrap(PyObject* self_, const Components::UseComponent& cmp);
			bool Use(Actions::Action* action) override;
			bool UseDefault(Actions::Action* action);
			bool BattleUse(Actions::Action* action, Battle::BattleField* field) override;
			bool BattleUseDefault(Actions::Action* action, Battle::BattleField* field);
			Components::UseComponent::ClonePtr Clone() const override;
			Components::UseComponent::ClonePtr CloneDefault() const;
			PyObject* self;


		private:

		};
	}
}
