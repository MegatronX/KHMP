#pragma once
#ifndef _SCREENMODULE_H_
#define _SCREENMODULE_H_
#include <Scripting/Python/ScriptHelpers.h>
#include <Graphics/Screens/Screen.h>
using namespace ::Graphics::Screens;
class Engine;
namespace Scripting
{
	class ScreenWrap : public Screen
	{
	public:
		ScreenWrap(PyObject* self, const std::string& name, ::Engine* engine, int id) : self(self), Screen(name, engine, id)
		{

		}
		ScreenWrap(PyObject* self, const Screen& src) : self(self), Screen(src)
		{

		}
		void Draw(sf::RenderWindow &window, sf::Shader &shader) override
		{
			call_method<void>(self, "Draw", boost::ref(window), boost::ref(shader));
		}
		void Draw(sf::RenderWindow& window) override
		{
			call_method<void>(self, "Draw", boost::ref(window));
		}
		void DrawDefault(sf::RenderWindow& window, sf::Shader& shader)
		{
			Screen::Draw(window, shader);
		}
		void DrawDefault(sf::RenderWindow& window)
		{
			Screen::Draw(window);
		}
		void Update(const sf::Uint32 time, const float TimeScale = 1.0)
		{
			call_method<void>(self, "Update", time, TimeScale);
		}
		void UpdateDefault(const sf::Uint32 time, const float TimeScale = 1.0)
		{
			Screen::Update(time, TimeScale);
		}
		bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& iaction) override
		{
			return false;
			//call_method<bool>(self, "HandleKeyPressed", time, boost::python::ptr(inputModule), pinput, boost::ref(iaction));
		}
		bool HandleKeyPressedDefault(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& iaction)
		{
			return Screen::HandleKeyPressed(time, inputModule, boost::ref(iaction));
		}
		bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& iaction) override
		{
			return false;
			//call_method<bool>(self, "HandleKeyReleased", time, boost::python::ptr(inputModule), pinput, boost::ref(iaction));
		}
		bool HandleKeyReleasedDefault(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& iaction)
		{
			return Screen::HandleKeyReleased(time, inputModule, boost::ref(iaction));
		}
	private:
		PyObject* self;
	};
	BOOST_PYTHON_MODULE(ScreenModule)
	{
		class_<ScreenManager, boost::noncopyable>("ScreenManager", no_init)
			.def("AddScreen", &ScreenManager::AddScreen)
			;
		class_<Screen, boost::shared_ptr<ScreenWrap> >("Screen", init<const std::string&, ::Engine*, int>())
			.def("AddOwner", &Screens::Screen::AddOwner)
			.def("Draw", (void (Screens::Screen::*)(sf::RenderWindow&))&Screen::Draw, (void (Screens::Screen::*)(sf::RenderWindow&))&ScreenWrap::DrawDefault)
			.def("Draw", (void (Screens::Screen::*)(sf::RenderWindow&, sf::Shader&))&Screen::Draw, (void (Screens::Screen::*)(sf::RenderWindow&, sf::Shader&))&ScreenWrap::DrawDefault)
			.def("GetID", &Screens::Screen::GetID)
			.def("GetScreenName", &Screens::Screen::GetScreenName, return_value_policy<reference_existing_object>())
			.def("HandleKeyPressed", &Screens::Screen::HandleKeyPressed, &ScreenWrap::HandleKeyPressedDefault)
			.def("HandleKeyReleased", &Screens::Screen::HandleKeyReleased, &ScreenWrap::HandleKeyReleasedDefault)
			.def("HasOwner", &Screens::Screen::HasOwner)
			.def("IsAcceptingInputs", &Screens::Screen::IsAcceptingInputs)
			.def("SetScreenName", &Screens::Screen::SetScreenName)
			.def("Update", (void (Screens::Screen::*)(const sf::Uint32, float))&Screens::Screen::Update, &ScreenWrap::UpdateDefault, boost::python::arg("TimeScale") = 1.f)
			;
		/*class_<Screen, boost::noncopyable>("Screen", no_init)//init<const std::string&, ::Engine*, int>())
			.def("AddOwner", &Screens::Screen::AddOwner)
			.def("GetDrawPriority", &Screens::Screen::GetDrawPriority)
			.def("GetID", &Screens::Screen::GetID)
			.def("GetOwners", &Screens::Screen::GetOwners, return_value_policy<reference_existing_object>())
			.def("GetPause", &Screens::Screen::GetPause)
			.def("GetScreenName", &Screens::Screen::GetScreenName, return_value_policy<reference_existing_object>())
			.def("HasOwner", &Screens::Screen::HasOwner)
			//.def("", &Screens::Screen::IsAcceptingInputs)
			//.def("", &Screens::Screen::IsDrawing)
			.def("SetScreenName", &Screens::Screen::SetScreenName)
			//.def("", &Screens::Screen:)
			//.def("", &Screens::Screen:)
			;*/
		/*class_<Screen, bases<Graphics::AnimatedDraw, ::Input::InputInterface> >("Screen", init<const std::string&, ::Engine*, int>())
			.def("GetID", &Screen::GetID)
			.def("GetScreenName", &Screen::GetScreenName, return_value_policy<reference_existing_object>())
			.def("HasOwner", &Screen::HasOwner)
			.def("RemoveOwner", &Screen::RemoveOwner)
			.def("SetScreenName", &Screen::SetScreenName)
			;*/
	}
}

#endif