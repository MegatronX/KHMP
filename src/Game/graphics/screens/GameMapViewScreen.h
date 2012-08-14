#pragma once

#include <Graphics/Screens/MapViewLayer.h>

namespace Game
{
	namespace Graphics
	{
		namespace Screens
		{

			class GameMapViewScreen : public ::Graphics::Screens::Screen
			{
			public:
				GameMapViewScreen(Engine* engine);
				GameMapViewScreen(Engine* engine, std::string &mapFile, sf::Vector2f &startPos, sf::RenderWindow* window, std::string &name, int layerID = -1);
				//			MapViewLayer(Engine* engine, std::string &mapFile, sf::Vector2f &startPos, sf::RenderWindow* window, std::string &name, int layerID, bool draw, Game::Character::Party* party, bool drawcaller = true, bool updatecaller = true);
				//Animated Draw
				virtual void Draw(sf::RenderWindow &window) override;
				virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) override;
				virtual void Update(const float time, const float TimeScale = 1.0) override;
				virtual void Update(const sf::Uint32 time, const float timescale = 1.0) override;
				sf::Vector2f FindTileBasedCenter(const sf::Vector2f windowSize = sf::Vector2f(800, 600), const sf::Vector2f offset = sf::Vector2f(0, 0));
				void ChangeMaps(std::string &newMap, std::string &newmapname, MapExit &exit);
				void ChangeMapViaMapExit(MapExit exit);

				virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);
				virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);
			protected:
				void ContinuedDirectionHandler(Mapping::MapCharacter* ch);
				//boost::shared_ptr<TileMap> map;
				boost::shared_ptr<Game::Mapping::GameMap> game_map;
				sf::View CharacterView;
				//std::vector<Graphics::AnimatedSprite> Backgrounds;
				::Game::Mapping::MapCharacter MapChar;
				boost::shared_ptr<sf::RenderWindow> PrimaryWindow;
				sf::RenderWindow* GameWindow;
				
				//MapCharacterSprite MapCharacter;
				//Game::Character::Party* party;
			private:
				sf::Uint32 LastInputUpdate;
			};
		}
	}
}