#pragma once
#ifndef _BASICRMLSCREEN_H_
#define _BASICRMLSCREEN_H_
#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include <vector>
#include <graphics/Screens/GameScreen.h>
#include <Graphics/Rocket/ElementTransformer.h>
#include <Graphics/Rocket/ElementTransformInterface.h>
#include <boost/ptr_container/ptr_unordered_map.hpp>
class Engine;
namespace Game
{
	namespace Graphics
	{
		namespace GameRocket
		{
			typedef std::pair<boost::shared_ptr<::Graphics::GameRocket::ElementTransformer>, sf::Uint32> TransformPair;
			class BasicRMLScreen : public Screens::GameScreen
			{
			public:
				BasicRMLScreen(const std::string& name, const std::string& rmlDoc, Engine* engine, int id);
				BasicRMLScreen::BasicRMLScreen(const std::string& name, const std::string& rmlDoc, Engine& engine, int id);
				~BasicRMLScreen();
				virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) override;
				virtual void Draw(sf::RenderWindow &window) override;
				virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;
				virtual void Update(const float time, const float TimeScale = 1.0) override;
				virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionRes) override;
				virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionRes) override;
				Rocket::Core::Context* GetPageContext() const;
				Rocket::Core::ElementDocument* GetDocument() const;
				void AddNewTransform(const std::string& name, std::vector<::Graphics::GameRocket::ElementTransformationInterface*>& transforms, sf::Uint32 delay = 0);
				void AddNewTransform(const std::string& name, ::Graphics::GameRocket::ElementTransformer* transformer, sf::Uint32 delay = 0);
				void AddNewTransform(const std::string& name, boost::shared_ptr<::Graphics::GameRocket::ElementTransformer>& transformer, sf::Uint32 delay = 0);
			private:
				Rocket::Core::Context* pageContext;
				Rocket::Core::ElementDocument* Doc;
				boost::unordered_map<std::string,  TransformPair> ActiveTransforms;
			};
		}
	}
}
#endif