#pragma once
#ifndef _GRAPHICSMODULE_H_
#define _GRAPHICSMODULE_H_
#include "ScriptHelpers.h"
#include <Graphics/AnimatedDraw.h>
#include <Graphics/DrawInterface.h>
#include <Graphics/Screens/Screen.h>
using namespace ::Graphics;
namespace Scripting
{
	class DrawInterfaceWrap : public DrawInterface
	{
	public:
		DrawInterfaceWrap(PyObject* self, int priority = 0, bool drawing = true) : self(self), DrawInterface(priority, drawing)
		{

		}
		DrawInterfaceWrap(PyObject* self, const DrawInterface& src) : self(self), DrawInterface(src)
		{

		}
		DrawInterfaceWrap(PyObject* self, const DrawInterfaceWrap& src) : self(self), DrawInterface(src)
		{
		}
		void Draw(sf::RenderWindow &window) override
		{
			call_method<void>(self, "Draw", boost::ref(window));
		}
		void Draw(sf::RenderWindow &window, sf::Shader& shader) override
		{
			call_method<void>(self, "Draw", boost::ref(window), boost::ref(shader));
		}
	private:
		PyObject* self;
	};

	class AnimatedDrawWrap : public AnimatedDraw
	{
	public:
		AnimatedDrawWrap(PyObject* self, int priority = 0, bool paused = true) : self(self), AnimatedDraw(paused, priority)
		{

		}
		//??? not sure how to do this
		AnimatedDrawWrap(PyObject* self, const AnimatedDrawWrap& src) : self(self), AnimatedDraw(src)
		{

		}
		AnimatedDrawWrap(PyObject* self, const AnimatedDraw& src) : self(self), AnimatedDraw(src)
		{

		}
		void Update(const sf::Uint32 time, const float TimeScale = 1.0) override
		{
			call_method<void>(self, "Update", time, TimeScale);
		}
		void Update(const float time, const float TimeScale = 1.0) override
		{
			call_method<void>(self, "Update", time, TimeScale);
			
		}
	private:
		PyObject* self;
	};
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(RenderWindowDraw, Draw, 1, 2)
		//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(RenderWindowSetActive, SetActive, 0, 1)
	BOOST_PYTHON_MODULE(GraphicsModule)
	{
		class_<sf::RenderStates>("RenderStates", no_init)
			;
		/*enum_<sf::RenderStates>("RenderStates")
			.def("BlendMode", sf::RenderStates::BlendMode)
			;*/
		class_<sf::Vector2f>("Vector2f", init<>())
			.def(init<float, float>())
			.def_readwrite("x", &sf::Vector2f::x)
			.def_readwrite("y", &sf::Vector2f::y)
			//.def(-self)
			//.def(+self)
			.def(self + self)
			.def(self - self)
			.def(self += self)
			.def(self -= self)
			//.def(self * float())
			.def(self / float())
			;

		class_<sf::Vector2i>("Vector2i", init<>())
			.def(init<int, int>())
			.def_readwrite("x", &sf::Vector2i::x)
			.def_readwrite("y", &sf::Vector2i::y)
			.def(self + self)
			.def(self - self)
			.def(self += self)
			.def(self -= self)
			//.def(self * float())
			//.def(self / float())
			;
		
		class_<sf::Texture>("Texture", init<>())
			;
		class_<sf::Image>("Image", init<>())
			;
		class_<sf::Shader, boost::noncopyable>("Shader", init<>())
			.def("Bind", &sf::Shader::Bind)
			
			.def("IsAvailable", &sf::Shader::IsAvailable).staticmethod("IsAvailable")
			//.def("LoadFromFile", &sf::Shader::LoadFromFile)
			//.def("LoadFromMemory", &sf::Shader::LoadFromMemory)
			.def("Unbind", &sf::Shader::Unbind)
			;
		//(Rocket::Core::String (Element::*)() const)&Element::GetInnerRML
		class_<sf::RenderWindow, boost::noncopyable>("RenderWindow", no_init)
			.def("Capture", &sf::RenderWindow::Capture)
			.def("Clear", &sf::RenderWindow::Clear)
			.def("Close", &sf::RenderWindow::Close)
			.def("ConvertCoords", (sf::Vector2f (sf::RenderWindow::*)(unsigned int, unsigned int) const)&sf::RenderWindow::ConvertCoords)
			.def("ConvertCoords", (sf::Vector2f (sf::RenderWindow::*)(unsigned int, unsigned int, const sf::View&) const)&sf::RenderWindow::ConvertCoords)
			.def("Display", &sf::RenderWindow::Display)
			.def("Draw", (void (sf::RenderWindow::*)(const sf::Drawable&, const sf::RenderStates&))&sf::RenderWindow::Draw, (boost::python::arg("states") = sf::RenderStates::Default))
			.def("Draw", (void (sf::RenderWindow::*)(const sf::Vertex*, unsigned int, sf::PrimitiveType, const sf::RenderStates&))&sf::RenderWindow::Draw, (boost::python::arg("states") = sf::RenderStates::Default))
			.def("EnableKeyRepeat", &sf::RenderWindow::EnableKeyRepeat)
			.def("EnableVerticalSync", &sf::RenderWindow::EnableVerticalSync)
			.def("GetDefaultView", &sf::RenderWindow::GetDefaultView, return_value_policy<reference_existing_object>())
			.def("GetFrameTime", &sf::RenderWindow::GetFrameTime)
			.def("GetHeight", &sf::RenderWindow::GetHeight)
			.def("GetView", &sf::RenderWindow::GetView, return_value_policy<reference_existing_object>())
			.def("GetViewport", &sf::RenderWindow::GetViewport)
			.def("GetWidth", &sf::RenderWindow::GetWidth)
			.def("IsOpened", &sf::RenderWindow::IsOpened)
			.def("PopGLStates", &sf::RenderWindow::PopGLStates)
			.def("PushGLStates", &sf::RenderWindow::PushGLStates)
			.def("ResetGLStates", &sf::RenderWindow::ResetGLStates)
			.def("SetActive", &sf::RenderWindow::SetActive, (boost::python::arg("active") = true))
			.def("SetFrameLimit", &sf::RenderWindow::SetFramerateLimit)
			.def("SetJoystickThreshold", &sf::RenderWindow::SetJoystickThreshold)
			.def("SetPosition", &sf::RenderWindow::SetPosition)
			.def("SetSize", &sf::RenderWindow::SetSize)
			.def("SetTitle", &sf::RenderWindow::SetTitle)
			.def("SetView", &sf::RenderWindow::SetView)
			.def("Show", &sf::RenderWindow::Show)
			.def("ShowMouseCursor", &sf::RenderWindow::ShowMouseCursor)
			;
		
		/*class_<DrawInterfaceWrap>("DrawInterface", init<boost::python::optional<int, bool> >())
			.def(init<const DrawInterface&>())
			.def("Draw", pure_virtual((void (DrawInterface::*)(sf::RenderWindow&))&DrawInterface::Draw))
			.def("Draw", pure_virtual((void (DrawInterface::*)(sf::RenderWindow&, sf::Shader&))&DrawInterface::Draw))
			.def("IsDrawing", &DrawInterface::IsDrawing)
			.def("SetDrawing", &DrawInterface::SetDrawing)
			.def("GetDrawPriority", &DrawInterface::GetDrawPriority)
			;
		class_<AnimatedDrawWrap, bases<DrawInterfaceWrap> >("AnimatedDraw", init<boost::python::optional<int, bool> >())
			.def(init<const AnimatedDraw&>())
			.def(init<const AnimatedDrawWrap&>())
			.def("Update", pure_virtual((void (AnimatedDraw::*)(const sf::Uint32, const float))&AnimatedDraw::Update))
			.def("Update", pure_virtual((void (AnimatedDraw::*)(const float, const float))&AnimatedDraw::Update))
			.def("GetPause", &AnimatedDraw::GetPause)
			.def("SetPause", &AnimatedDraw::SetPause)
			;*/
	}
}

#endif