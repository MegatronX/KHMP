#pragma once
#ifndef _ACTION_H_
#define _ACTION_H_

#include <Entity.h>
#include <actions/ActionInterface.h>
#include <actions/ActiveAction.h>
namespace Game
{
	namespace Actions
	{
		class Action : public Entity//, public ActionInterface
		{
		public:
			Action();
			Action(const std::string& name, const int type = EntityTypes::ActionEntity);
			std::vector<ActiveAction> Users;
			std::vector<ActiveAction> Targets;

			bool IgnoreUserSE;
			bool IgnoreUserAbil;
			
			bool IgnoreTargetSE;
			bool IgnoreTargetAbil;

			/*virtual bool PreUse(Action* action) override;
			virtual bool Use(Action* action) override;
			virtual bool PostUse(Action* action) override;
			virtual bool BattlePreUse(Action* action, Battle::BattleField* field) override;
			virtual bool BattleUse(Action* action, Battle::BattleField* field) override;
			virtual bool BattlePostUse(Action* action, Battle::BattleField* field) override;*/
			RawClonePtr RawClone() const override;

			float GetAccuracy() const;
		protected:
			float Accuracy;
		};
	}
}

#endif