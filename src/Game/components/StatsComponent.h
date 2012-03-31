#pragma once
#ifndef _CHARACTERSTATCOMPONENT_H_
#define _CHARACTERSTATCOMPONENT_H_
#include <character/Stats.h>
#include <components/Component.h>
#include <boost/signal.hpp>
#include <boost/signals2.hpp>
#include <boost/function.hpp>

namespace Game
{
	class Entity;
	namespace Character
	{
		class BaseCharacter;
	}
	namespace Components
	{
		
		class StatComponent; 

		typedef boost::signal<void (const std::string& compName, StatComponent*, Character::Stat stat, int oldVal, int newVal)> StatChangedSignal;
		
		class StatComponent : public Components::Component, public boost::signals::trackable
		{
		public:
			StatComponent(Entity* owner);
			StatComponent(Entity* owner, const std::string& name);
			StatComponent(Entity* owner, int initialValue, const std::string& name);
			StatComponent(Entity* owner, const int InitialStats[Character::StatCount], const std::string& name) ;

			//NOTE that the copy constructor does NOT copy the signals
			StatComponent(const StatComponent& base);
			int GetStat(const Character::Stat stat) const;
			bool SetStat(const Character::Stat stat, const int value);
			boost::signals::connection AddStatChangedEvent(const StatChangedSignal::slot_type& event);
			void DispatchStatChangedEvents(Character::Stat stat, int prevVal, int newVal);
			virtual ~StatComponent();
			StatComponent& operator=(const StatComponent& reference);
			virtual ClonePtr Clone() const override;
		protected:
			
			StatChangedSignal StatChangedEvent;
			int& operator[](const Character::Stat stat);
			int& operator[](const int stat);
		private:
			int Stats[Character::StatCount] ;
			friend class Character::BaseCharacter;
		};
	}
}
#endif