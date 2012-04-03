#pragma once
#ifndef _CHARACTERSTAT_H_
#include <boost/unordered_map.hpp>
#include <string>
namespace Game
{
	namespace Character
	{
		const int StatCount = 13;
		enum Stat
		{
			HP = 0,
			MP = 1,
			SP = 2,
			Strength = 3,
			Vitality = 4,
			Defense = 4,
			Magic = 5,
			Spirit = 6,
			MgDefense = 6,
			Skill = 7,
			Speed = 8,
			Agility = 8,
			Evasion = 9,
			MgEvasion = 10,
			Accuracy = 11,
			Luck = 12,
			//None = 13 //Using this as an indexer will cause a segfault
		};

		extern const boost::unordered_map<Stat, std::string> StatNameLookup;
		extern const boost::unordered_map<std::string, Stat> NameStatLookup;
	}
}

#endif