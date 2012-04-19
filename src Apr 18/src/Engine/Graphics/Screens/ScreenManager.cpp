#include "ScreenManager.h"
#include <Engine.h>
namespace Graphics
{
	namespace Screens
	{
		void ScreenManager::AddScreen(screen_ptr screen)
		{
			if (screen.get() != nullptr)
			{
				ScreenStack newStack(screen->GetScreenName(), screen->engine->GetUID(), true, true);
				newStack.AddScreen(screen);
				StackByName[newStack.GetScreenName()] = newStack;
				StackByID[newStack.GetUID()] = &StackByName[newStack.GetScreenName()];
				StacksInDrawOrder.push_back(&StackByName[newStack.GetScreenName()]);
			}
			
		}
		void ScreenManager::AddScreenToStack(screen_ptr screen, const std::string& stackName)
		{
			if (screen.get() != nullptr)
			{
				ScreenStack newStack(screen->GetScreenName(), screen->engine->GetUID(), true, true);
				newStack.AddScreen(screen);
				StackByName[newStack.GetScreenName()] = newStack;
				StackByID[newStack.GetUID()] = &StackByName[newStack.GetScreenName()];
				StacksInDrawOrder.push_back(&StackByName[newStack.GetScreenName()]);
			}

		}
		void ScreenManager::AddScreenStack(const std::string& name, const ScreenStack& stack, bool registerIndividualScreens)
		{

		}
		ScreenStack& ScreenManager::GetScreenStack(const std::string& name)
		{
			return *(*StacksInDrawOrder.begin());
		}

		bool ScreenManager::RegisterStackCreationFunction(const std::string& name)
		{
			return false;
		}
		ScreenStack ScreenManager::CreateStack(const std::string stackname, const std::string creationFunction, bool registerStack, bool registerIndividualSscreens)
		{
			//need to do a switch here
			return ScreenStack();
		}

		bool ScreenManager::HandleKeyPressed(const sf::Uint32 time, const Input::InputModule* inputModule, ::Input::InputActionResult& action)
		{
			bool handled = false;
			for (auto stack = StacksInDrawOrder.begin(); stack != StacksInDrawOrder.end(); ++stack)
			{
				handled |= (*stack)->HandleKeyPressed(time, inputModule, action);
			}
			return handled;
		}
		bool ScreenManager::HandleKeyReleased(const sf::Uint32 time, const Input::InputModule* inputModule, ::Input::InputActionResult& action)
		{
			bool handled = false;
			for (auto stack = StacksInDrawOrder.begin(); stack != StacksInDrawOrder.end(); ++stack)
			{
				handled |= (*stack)->HandleKeyReleased(time, inputModule, action);
			}
			return handled;
		}

		//Animate Draw
		void ScreenManager::Update(const sf::Uint32 time, const float TimeScale)
		{
			for (auto stack = StacksInDrawOrder.begin(); stack != StacksInDrawOrder.end(); ++stack)
			{
				(*stack)->Update(time, TimeScale);
			}
		}
		void ScreenManager::Update(const float time, const float TimeScale)
		{
			for (auto stack = StacksInDrawOrder.begin(); stack != StacksInDrawOrder.end(); ++stack)
			{
				(*stack)->Update(time, TimeScale);
			}
		}

		void ScreenManager::Draw(sf::RenderWindow &window)
		{
			for (auto stack = StacksInDrawOrder.begin(); stack != StacksInDrawOrder.end(); ++stack)
			{
				(*stack)->Draw(window);
			}
		}
		void ScreenManager::Draw(sf::RenderWindow &window, sf::Shader &shader)
		{
			for (auto stack = StacksInDrawOrder.begin(); stack != StacksInDrawOrder.end(); ++stack)
			{
				(*stack)->Draw(window, shader);
			}
		}

	}
}