#include "StatsComponent.h"
#include "Entity.h"
namespace Game
{
	using namespace Character;
	namespace Components
	{
		StatComponent::StatComponent(Entity* owner) : Component(owner, "EmptyStatComponent" + owner->GetName(), "StatsComponent")
		{

		}
		StatComponent::StatComponent(Entity* owner, const std::string& name) : Component(owner, name, "StatsComponent")
		{

		}
		StatComponent::StatComponent(Entity* owner, int initialValue, const std::string& name) : Component(owner, name, "StatsComponent")
		{
			for (int i = 0; i < StatCount; ++i)
			{
				Stats[i] = initialValue;
			}
		}
		StatComponent::StatComponent(Entity* owner, const int InitialStats[StatCount], const std::string& name) : Component(owner, name, "StatsComponent")//: Stats(InitialStats)
		{
			for (int i = 0; i < StatCount; ++i)
				Stats[i] = InitialStats[i];
		}

		//NOTE that the copy constructor does NOT copy the signals
		StatComponent::StatComponent(const StatComponent& base) : Component(base)
		{
			for (int i = 0; i < StatCount; ++i)
				Stats[i] = base.Stats[i];
		}
		int StatComponent::GetStat(const Stat stat) const
		{
			return Stats[stat];
		}
		bool StatComponent::SetStat(const Stat stat, const int value)
		{
			if (stat >= 0 && stat < StatCount)
			{
				int prevVal = Stats[stat];
				Stats[stat] = value;
				DispatchStatChangedEvents(stat, prevVal, value);
				return true;
			}
			return false;
		}
		boost::signals::connection StatComponent::AddStatChangedEvent(const StatChangedSignal::slot_type& event)
		{
			return StatChangedEvent.connect(event);
		}
		void StatComponent::DispatchStatChangedEvents(Stat stat, int prevVal, int newVal)
		{
			(StatChangedEvent)(Component::GetName(), this, stat, prevVal, Stats[stat]);
		}
		StatComponent::~StatComponent()
		{
			//delete StatChangedEvent;
			//StatChangedEvent = nullptr;
		}
		StatComponent& StatComponent::operator=(const StatComponent& reference)
		{
			if (this == &reference)
				return *this;
			Component::operator=(reference);
			for (int i = 0; i < StatCount; ++i)
				Stats[i] = reference.Stats[i];
			return *this;
		}
		StatComponent::ClonePtr StatComponent::Clone() const
		{
			return StatComponent::ClonePtr(new StatComponent(*this));
		}
		int& StatComponent::operator[](const Stat stat)
		{
			return Stats[stat];
		}
		int& StatComponent::operator[](const int stat)
		{
			if (stat >= 0 && stat < StatCount)
				return Stats[stat];
#ifdef _DEBUG
			std::cerr << "Attempted to access a stat component stat with index " << stat << std::endl;
#endif
			return Stats[0];
		}
	}
}