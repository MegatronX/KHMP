#include "Screen.h"
#include <Engine.h>
namespace Graphics
{
	namespace Screens
	{
		Screen::Screen(const std::string& name, Engine* engine, int id) : ScreenName(name), engine(engine), ScreenID(id)
		{

		}
		Screen::~Screen()
		{

		}
		int Screen::GetID() const
		{
			return ScreenID;
		}
		const std::string& Screen::GetScreenName() const
		{
			return ScreenName;
		}
		void Screen::SetScreenName(const std::string& name)
		{
			ScreenName = name;
		}

		bool Screen::AddOwner(const std::string& name, ScreenStack* stack)
		{
			OwningStacks[name] = stack;
			return true;
		}
		bool Screen::RemoveOwner(const std::string& name)
		{
			auto it = OwningStacks.find(name);
			if (it != OwningStacks.end())
			{
				OwningStacks.erase(it);
				return true;
			}
			return false;
		}
		bool Screen::HasOwner(const std::string& name)
		{
			return OwningStacks.find(name) != OwningStacks.end();
		}
		const boost::unordered_map<std::string, ScreenStack*>& Screen::GetOwners() const
		{
			return OwningStacks;
		}
		bool Screen::operator==(const Screen& screen) const
		{
			return ScreenID == screen.ScreenID;
		}
		bool Screen::operator!=(const Screen& screen) const
		{
			return !((*this) == screen);
		}
	}
}