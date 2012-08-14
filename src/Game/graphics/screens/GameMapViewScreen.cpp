#include "GameMapViewScreen.h"

namespace Game
{
	namespace Graphics
	{
		namespace Screens
		{



			GameMapViewScreen::GameMapViewScreen(Engine* engine) : Screen("Game Map Layer", engine, -1)
			{

			}
			GameMapViewScreen::GameMapViewScreen(Engine* engine, std::string &mapFile, sf::Vector2f &startPos, sf::RenderWindow* window, std::string &name, int layerID)
				: Screen(name, engine, layerID == -1 ? (engine != nullptr ? engine->GetUID() : -1) : layerID), LastInputUpdate(0), GameWindow(window)
			{
				game_map = boost::shared_ptr<Game::Mapping::GameMap>(new Game::Mapping::GameMap(engine->GetContentManager().GetMapDirectory() + mapFile, name, engine));//Game::Mapping::GameMap::LoadMapFromXML(mapFile, name);
				//map = TileMap::LoadMapFromXML(mapFile, name);
				//this->PrimaryWindow = window;
				CharacterView = sf::View(window->getView());
				//MapCharacter.SetMapPosition(startPos);


				//std::vector<Graphics::RowDescriptionTuple> rowDescriptors;
				//Down up left right

				//Graphics::RowDescriptionTuple newTuple(Graphics::RowClass::Down, 16, std::vector<int>(32, 32), 1, 0);

				//MapCharacter.characterSprite.AddTranslationEvent(std::string("MoveEvent"), &MapViewLayer::CharacterHookEvent);


				//MapChar.chTex.loadFromFile("..\\..\\..\\resources\\Graphics\\Sprites\\Characters\\Main\\ArianBase.png");
				//MapChar.chSpr.setTexture(MapChar.chTex);

				//MapChar.CharSpr.GetAnimator().

				MapChar.CharSpr.SetTexture(engine->GetContentManager().RequestTexture("ArianBase", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Guardian, engine->GetTime()));

				auto size = window->getSize();
				auto sprsize = sf::Vector2f(MapChar.CharSpr.GetBaseSprite().getTextureRect().width, MapChar.CharSpr.GetBaseSprite().getTextureRect().height);

				auto cen = FindTileBasedCenter(sf::Vector2f(size.x, size.y));

				

				MapChar.FollowInX = true;
				MapChar.FollowInY = true;
				MapChar.ViewOffset.x = -32;
				MapChar.ViewOffset.y = -sprsize.y + 32;
				MapChar.CharSpr.SetPosition(cen + MapChar.ViewOffset);
				CharacterView.setCenter(startPos);// + MapChar.ViewOffset);
				//CharacterView.setCenter(cen);
				MapChar.MapPosition = startPos;
				MapChar.MapTilePosition = sf::Vector2f(startPos.x / game_map->GetTileWidth(), startPos.y / game_map->GetTileHeight());
				MapChar.DrawLayer = 2;

				MapChar.AddFinishedEvent("MovementContinue", boost::bind(&GameMapViewScreen::ContinuedDirectionHandler, this, _1));

				game_map->PlayMusic();

			}

			void GameMapViewScreen::Draw(sf::RenderWindow &window)
			{
				//MapCharacter.characterSprite.SetColor(sf::Color(255, 255, 255, 255));
				sf::View prevView = window.getView();
				bool restoreView = false;
				/*for (auto it = Backgrounds.begin(); it != Backgrounds.end(); ++it)
				{
				it->Draw(window);
				}*/
				if (MapChar.FollowInX || MapChar.FollowInY)
				{
					restoreView = true;
					auto NewCen = prevView.getCenter(); 
					if (MapChar.FollowInX)
						NewCen.x = MapChar.MapPosition.x;
					if (MapChar.FollowInY)
						NewCen.y = MapChar.MapPosition.y;
					CharacterView.setCenter(NewCen);// + MapChar.ViewOffset);
					window.setView(CharacterView);

				}
				game_map->Draw(window, MapChar, prevView);//, MapCharacter, prevView);
				//map->Draw(window, MapCharacter, prevView);
				if (restoreView)
					window.setView(prevView);
			}
			void GameMapViewScreen::Draw(sf::RenderWindow &window, sf::Shader &shader)
			{

				sf::View prevView = window.getView();
				bool restoreView = false;
				/*for (auto it = Backgrounds.begin(); it != Backgrounds.end(); ++it)
				{
				it->Draw(window);
				}*/
				if (MapChar.FollowInX || MapChar.FollowInY)
				{
					restoreView = true;
					auto NewCen = prevView.getCenter(); 
					if (MapChar.FollowInX)
						NewCen.x = MapChar.MapPosition.x;
					if (MapChar.FollowInY)
						NewCen.y = MapChar.MapPosition.y;
					CharacterView.setCenter(NewCen);
					window.setView(CharacterView);

				}
				game_map->Draw(window, shader, MapChar, prevView);//, MapCharacter, prevView);
				//map->Draw(window, MapCharacter, prevView);
				if (restoreView)
					window.setView(prevView);
			}
			void GameMapViewScreen::Update(const sf::Uint32 time, const float timescale)
			{
				//InputModule* module = &(engine->GetInputModule());
				//HandleInputs(time, *(engine->GetInputModule()));
				/*for (auto it = Backgrounds.begin(); it != Backgrounds.end(); ++it)
				{
				it->Update(time, timescale);
				}*/
				game_map->Update(time, timescale);
				MapChar.Update(time, timescale);
				//map->Update(time);
				//MapCharacter.Update(time, timescale);
			}
			void GameMapViewScreen::Update(const float time, const float timescale)
			{
				Update(static_cast<sf::Uint32>(time * 1000), timescale);
			}
			//Not Finished
			sf::Vector2f GameMapViewScreen::FindTileBasedCenter(const sf::Vector2f windowSize, const sf::Vector2f offset)
			{
				int xTiles = (int)(windowSize.x / game_map->GetTileWidth());
				int yTiles = (int)(windowSize.y / game_map->GetTileHeight());
				return sf::Vector2f((xTiles * 0.5) * game_map->GetTileWidth() + offset.x, (yTiles * 0.5) * game_map->GetTileHeight() + offset.y);
			}
			void GameMapViewScreen::ChangeMaps(std::string &newMap, std::string &newmapname, MapExit &exit)
			{
				game_map = boost::shared_ptr<Game::Mapping::GameMap>(new Game::Mapping::GameMap(newMap, newmapname, engine));
				sf::Vector2f startPos(exit.get<5>(), exit.get<6>());
				/*MapCharacter.SetLayer(exit.get<7>());
				MapCharacter.SetMapPosition(startPos);
				MapCharacter.SetMapTilePosition(sf::Vector2f(startPos.x / game_map->GetTileWidth(), startPos.y / game_map->GetTileHeight()));
				MapCharacter.SetFollowInX(true);
				MapCharacter.SetFollowInY(true);
				CharacterView.SetCenter(startPos);*/
			}
			void GameMapViewScreen::ChangeMapViaMapExit(MapExit exit)
			{
				/*game_map->ReleaseResources();
				game_map = boost::shared_ptr<Game::Mapping::GameMap>(new Game::Mapping::GameMap(engine->GetContentManager()->GetMapDirectory() + exit.get<3>(), exit.get<4>(), engine));
				sf::Vector2f startPos(exit.get<5>() * game_map->GetTileWidth(), exit.get<6>() * game_map->GetTileHeight());
				MapCharacter.SetLayer(exit.get<7>());
				MapCharacter.SetMapPosition(startPos);
				MapCharacter.SetMapTilePosition(sf::Vector2f(startPos.x / game_map->GetTileWidth(), startPos.y / game_map->GetTileHeight()));
				MapCharacter.SetFollowInX(true);
				MapCharacter.SetFollowInY(true);
				game_map->PlayMusic();*/
			}
			static sf::Uint32 TransTime = 200;
			bool GameMapViewScreen::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
			{
				
				sf::Uint32 EffTime = TransTime;
				bool Handled = false;
				if (!MapChar.InTransit && actionResult.PInput == ::Input::P1Input)
				{
					switch(actionResult.IAction)
					{
					case ::Input::InputAction::Up:
						{
							sf::Vector2f targetPosition = sf::Vector2f(MapChar.MapPosition.x, boost::math::round(MapChar.MapPosition.y - game_map->GetTileHeight()));
							sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
							if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
							{
								sf::Vector2i adder = sf::Vector2i(0, 1);
								MapChar.SlideMapPosition(targetPosition, adder, EffTime, time);
							}
							else
							{
								MapChar.SlideMapPosition(MapChar.MapPosition, sf::Vector2i(0, 0), EffTime, time);
							}
						}
						MapChar.FollowInY = true;
						Handled = true;
						break;
					case ::Input::InputAction::Down:
						{
							sf::Vector2f targetPosition = sf::Vector2f(MapChar.MapPosition.x, boost::math::round(MapChar.MapPosition.y + game_map->GetTileHeight()));
							sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
							if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
							{
								sf::Vector2i adder = sf::Vector2i(0, -1);
								MapChar.SlideMapPosition(targetPosition, adder, EffTime, time);
							}
							else
							{
								MapChar.SlideMapPosition(MapChar.MapPosition, sf::Vector2i(0, 0), EffTime, time);
							}
						}
						MapChar.FollowInY = true;
						Handled = true;
						break;
					case ::Input::InputAction::Left:
						{
							sf::Vector2f targetPosition = sf::Vector2f(boost::math::round(MapChar.MapPosition.x - game_map->GetTileWidth()), MapChar.MapPosition.y);
							sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
							if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
							{
								sf::Vector2i adder = sf::Vector2i(-1, 0);
								MapChar.SlideMapPosition(targetPosition, adder, EffTime, time);
							}
							else
							{
								MapChar.SlideMapPosition(MapChar.MapPosition, sf::Vector2i(0, 0), EffTime, time);
							}
						}
						MapChar.FollowInX = true;
						Handled = true;
						break;
					case ::Input::InputAction::Right:
						{
							sf::Vector2f targetPosition = sf::Vector2f(boost::math::round(MapChar.MapPosition.x + game_map->GetTileWidth()), MapChar.MapPosition.y);
							sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
							if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
							{
								sf::Vector2i adder = sf::Vector2i(1, 0);
								MapChar.SlideMapPosition(targetPosition, adder, EffTime, time);
							}
							else
							{
								MapChar.SlideMapPosition(MapChar.MapPosition, sf::Vector2i(0, 0), EffTime, time);
							}
						}
						MapChar.FollowInX = true;
						Handled = true;
						break;
					}
				}
				return Handled;
			}
			bool GameMapViewScreen::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
			{
				return false;
			}
			void GameMapViewScreen::ContinuedDirectionHandler(Mapping::MapCharacter* ch)
			{
				if (engine != nullptr && !MapChar.InTransit)
				{
					sf::Uint32 EffTime = TransTime;
					auto time = engine->GetTime();
					auto &input = engine->GetInput();
					if (input.IsActionPushed(Input::PlayerInput::P1Input, Input::InputAction::Up))
					{
						sf::Vector2f targetPosition = sf::Vector2f(MapChar.MapPosition.x, boost::math::round(MapChar.MapPosition.y - game_map->GetTileHeight()));
						sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
						if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
						{
							sf::Vector2i adder = sf::Vector2i(0, 1);
							MapChar.SlideMapPosition(targetPosition, adder, EffTime, time);
						}
						else
						{
							MapChar.SlideMapPosition(MapChar.MapPosition, sf::Vector2i(0, 0), EffTime, time);
						}
						MapChar.FollowInY = true;
					}
					else if (input.IsActionPushed(Input::PlayerInput::P1Input, Input::InputAction::Down))
					{
						sf::Vector2f targetPosition = sf::Vector2f(MapChar.MapPosition.x, boost::math::round(MapChar.MapPosition.y + game_map->GetTileHeight()));
						sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
						if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
						{
							sf::Vector2i adder = sf::Vector2i(0, -1);
							MapChar.SlideMapPosition(targetPosition, adder, EffTime, time);
						}
						else
						{
							MapChar.SlideMapPosition(MapChar.MapPosition, sf::Vector2i(0, 0), EffTime, time);
						}
						MapChar.FollowInY = true;
					}
					else if (input.IsActionPushed(Input::PlayerInput::P1Input, Input::InputAction::Left))
					{
						sf::Vector2f targetPosition = sf::Vector2f(boost::math::round(MapChar.MapPosition.x - game_map->GetTileWidth()), MapChar.MapPosition.y);
						sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
						if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
						{
							sf::Vector2i adder = sf::Vector2i(-1, 0);
							MapChar.SlideMapPosition(targetPosition, adder, EffTime, time);
						}
						else
						{
							MapChar.SlideMapPosition(MapChar.MapPosition, sf::Vector2i(0, 0), EffTime, time);
						}
						MapChar.FollowInX = true;
					}
					else if (input.IsActionPushed(Input::PlayerInput::P1Input, Input::InputAction::Right))
					{
						sf::Vector2f targetPosition = sf::Vector2f(boost::math::round(MapChar.MapPosition.x + game_map->GetTileWidth()), MapChar.MapPosition.y);
						sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
						if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
						{
							sf::Vector2i adder = sf::Vector2i(1, 0);
							MapChar.SlideMapPosition(targetPosition, adder, EffTime, time);
						}
						else
						{
							MapChar.SlideMapPosition(MapChar.MapPosition, sf::Vector2i(0, 0), EffTime, time);
						}
						MapChar.FollowInX = true;
					}
				}
			}
		}
	}
}