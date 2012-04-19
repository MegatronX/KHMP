#include "Action.h"
#include <components/ActionUseComponent.h>
#include <algorithm>
namespace Game
{
	using namespace Components;
	namespace Actions
	{
		Action::Action() : Entity(), ActionInterface(true, true, true, true, true, true)
		{

		}
		Action::Action(const std::string& name, const int type) : Entity(name, type), ActionInterface(true, true, true, true, true, true)
		{

		}
		/*bool Action::PreUse(Action* action)//, ActionInterface(true, true, true, true, true, true)
		{
			std::vector<Actions::ActionInterface*> comps;
			comps.reserve(10);
			for (auto comp = ComponentCollection.begin(); comp != ComponentCollection.end(); ++comp)
			{
				auto compPtr = dynamic_cast<ActionUseComponent*>(comp->second.get());
				if ((compPtr) != nullptr && compPtr->ImplementsPreUse())
				{
					comps.push_back(compPtr);
				}
			}
			if (comps.size() < 0)
			{
				for (auto comp = comps.begin(); comp != comps.end(); ++comp)
				{
					(*comp)->PreUse(this);
				}
				return true;
			}
			return false;
		}
		bool Action::Use(Action* action)
		{
			std::vector<Actions::ActionInterface*> comps;
			comps.reserve(10);
			for (auto comp = ComponentCollection.begin(); comp != ComponentCollection.end(); ++comp)
			{
				auto compPtr = dynamic_cast<ActionUseComponent*>(comp->second.get());
				if ((compPtr) != nullptr && compPtr->ImplementsUse())
				{
					comps.push_back(compPtr);
				}
			}
			if (comps.size() < 0)
			{
				for (auto comp = comps.begin(); comp != comps.end(); ++comp)
				{
					(*comp)->Use(this);
				}
				return true;
			}
			return false;
		}
		bool Action::PostUse(Action* action)
		{
			std::vector<Actions::ActionInterface*> comps;
			comps.reserve(10);
			for (auto comp = ComponentCollection.begin(); comp != ComponentCollection.end(); ++comp)
			{
				auto compPtr = dynamic_cast<ActionUseComponent*>(comp->second.get());
				if ((compPtr) != nullptr && compPtr->ImplementsPostUse())
				{
					comps.push_back(compPtr);
				}
			}
			if (comps.size() < 0)
			{
				for (auto comp = comps.begin(); comp != comps.end(); ++comp)
				{
					(*comp)->PostUse(this);
				}
				return true;
			}
			return false;
		}

		bool Action::BattlePreUse(Action* action, Battle::BattleField* field)
		{
			return false;
		}
		bool Action::BattleUse(Action* action, Battle::BattleField* field)
		{
			return false;
		}
		bool Action::BattlePostUse(Action* action, Battle::BattleField* field)
		{
			return false;
		}*/

		Action::RawClonePtr Action::RawClone() const
		{
			return new Action(*this);
		}

		float Action::GetAccuracy() const
		{
			return this->Accuracy;
		}
	}
}