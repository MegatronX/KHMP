#include "Stats.h"
#include <boost/assign.hpp>

namespace Game
{
	namespace Character
	{
		const boost::unordered_map<Stat, std::string> StatNameLookup = boost::assign::map_list_of
			(Stat::HP, "HP")
			(Stat::MP, "MP")
			(Stat::SP, "SP")
			(Stat::Strength, "Strength")
			(Stat::Vitality, "Vitality")
			(Stat::Magic, "Magic")
			(Stat::Spirit, "Spirit")
			(Stat::Skill, "Skill")
			(Stat::Speed, "Speed")
			(Stat::Agility, "Agility")
			(Stat::Evasion, "Evasion")
			(Stat::MgEvasion, "MgEvasion")
			(Stat::Accuracy, "Accuracy")
			(Stat::Luck, "Luck");
		extern const boost::unordered_map<std::string, Stat> NameStatLookup = boost::assign::map_list_of
			("HP", Stat::HP)
			("MP", Stat::MP)
			("SP", Stat::SP)
			("Strength", Stat::Strength)
			("Vitality", Stat::Vitality)
			("Magic", Stat::Magic)
			("Spirit", Stat::Spirit)
			("Skill", Stat::Skill)
			("Speed", Stat::Speed)
			("Agility", Stat::Agility)
			("Evasion", Stat::Evasion)
			("MgEvasion", Stat::MgEvasion)
			("Accuracy", Stat::Accuracy)
			("Luck", Stat::Luck);
	}
}