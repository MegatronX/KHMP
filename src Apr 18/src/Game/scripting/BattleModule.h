#pragma once
#include <boost/python.hpp>
#include <battle/mechanics/Mechanics.h>
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		BOOST_PYTHON_MODULE(BattleModule)
		{
			class_<Battle::Mechanics, boost::noncopyable>("Mechanics", no_init)
				;
		}
	}
}