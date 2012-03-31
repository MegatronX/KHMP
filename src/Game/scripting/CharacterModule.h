#pragma once

#include <character/BaseCharacter.h>
#include <boost/python.hpp>

using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		BOOST_PYTHON_MODULE(CharacterModule)
		{
			enum_<CharacterStatus>("CharacterStatus")
				.value("Normal", CharacterStatus::Normal)
				.value("Normal", CharacterStatus::Normal)
				;

			class_<Character::BaseCharacter>("BaseCharacter")
				//.def("GetCombinedStat", &Character::BaseCharacter::GetCombinedStat)
				//.def("GetLevel", &Character::BaseCharacter::GetLevel)
				//.def("GetName", &Character::BaseCharacter::GetName, return_value_policy<reference_existing_object>())
				//.def("GetStatus", &Character::BaseCharacter::GetStatus)
				;
		}

	}
};
