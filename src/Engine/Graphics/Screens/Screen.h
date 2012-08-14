#pragma once
#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <system/Input/InputInterface.h>
#include <Graphics/AnimatedDraw.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <boost/unordered_map.hpp>
#include <Graphics/DrawManager.h>
class Engine;
namespace Graphics
{
	namespace Screens
	{
		class ScreenStack;
		class Screen : public virtual ::Input::InputInterface, public virtual AnimatedDraw
		{
		public:
			Screen(const std::string& name, ::Engine* engine, int id);
			virtual ~Screen();
			int GetID() const;
			const std::string& GetScreenName() const;
			void SetScreenName(const std::string& name);

			bool AddOwner(const std::string& name, ScreenStack* stack);
			bool RemoveOwner(const std::string& name);
			bool HasOwner(const std::string& name);
			const boost::unordered_map<std::string, ScreenStack*>& GetOwners() const;


			/*virtual bool HandleKeyPressed(const sf::Uint32 time, const Input::InputModule* inputModule, Input::PlayerInput pInput, Input::InputAction& action) override;
			virtual bool HandleKeyReleased(const sf::Uint32 time, const Input::InputModule* inputModule, Input::PlayerInput pInput, Input::InputAction& action) override;

			//Animate Draw
			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;
			virtual void Update(const float time, const float TimeScale = 1.0) override;

			virtual void Draw(sf::RenderWindow &window) override;
			virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) override;*/

			bool operator==(const Screen& screen) const;
			bool operator!=(const Screen& screen) const;
		protected:
			Engine* engine;
		private:
			//DrawManager DManager;
			int ScreenID;
			std::string ScreenName;
			bool DrawScreen;
			bool UpdateScreen;
			bool InputsEnabled;
			sf::Uint32 LastUpdate;
			boost::unordered_map<std::string, ScreenStack*> OwningStacks;

			friend class ScreenManager;
			//virtual bool HandleKeyPressed(const sf::Uint32 time, InputModule& inputModule, sf::Event::Key& keyEvent) = 0;
			//virtual bool HandleKeyReleased(const sf::Uint32 time, InputModule& inputModule, sf::Event::Key& keyEvent) = 0;
		};
		typedef boost::shared_ptr<Screen> screen_ptr;
	}
}


#endif