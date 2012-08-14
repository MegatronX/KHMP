#include "GameMap.h"
#include <io\xml\pugixml.hpp>
#include <boost\algorithm\string.hpp>
using namespace Graphics;
using namespace Mapping;
namespace Game
{
	namespace Mapping
	{

		MapCharacter::MapCharacter() : TargetPosition(0, 0), TranslationVector(0, 0), MapPosition(0, 0), MapTilePosition(0, 0), ScreenPosition(0, 0), ViewOffset(0, 0), Speed(0, 0), FollowInX( false), FollowInY(false),
			InTransit(false), DrawLayer(0), TargetTime(0), LastUpdate(0)
		{

		}
		void MapCharacter::Draw(sf::RenderWindow &window, sf::Shader &shader)
		{
			//Need to add shader support
			//window.draw(chSpr);
			CharSpr.Draw(window, shader);
		}
		void MapCharacter::Draw(sf::RenderWindow &window)
		{
			//window.draw(chSpr);
			CharSpr.Draw(window);
		}
		void MapCharacter::Update(const sf::Uint32 time, const float TimeScale)
		{
			if (InTransit)
			{
				sf::Uint32 elapsed = (LastUpdate > time) ? 0 : (time - LastUpdate);
				if (time < TargetTime)
				{
					MapPosition = MapPosition + TranslationVector * (float)elapsed;
				}
				else
				{
					InTransit = false;
					MapPosition = TargetPosition;
					TranslationVector = sf::Vector2f(0, 0);
					DispatchFinishedEvents();
				}
			}
			LastUpdate = time;
			CharSpr.Update(time, TimeScale);
		}

		void MapCharacter::SlideMapPosition(const sf::Vector2f &TargetPos, const sf::Vector2i &tileAdder, sf::Uint32 slideTime, sf::Uint32 currentTime)
		{
			MapTilePosition.x += tileAdder.x;
			MapTilePosition.y += tileAdder.y;

			TargetPosition = TargetPos;
			LastUpdate = currentTime;

			TargetTime = currentTime + slideTime;

			if (slideTime > 0)
			{
				InTransit = true;
				TranslationVector = (TargetPosition - MapPosition) / (float)slideTime;
			}
			else
			{
				MapPosition = TargetPos;
				TranslationVector = sf::Vector2f(0, 0);
			}
		}

		bool MapCharacter::AddFinishedEvent(const std::string& index, const MovementFinished& handler)
		{
			MoveFinishEvents[index] = handler;
			return true;
		}
		bool MapCharacter::RemoveFinishedEvent(const std::string& index)
		{
			bool removed = false;
			auto fd = MoveFinishEvents.find(index);
			if (fd != MoveFinishEvents.end())
			{
				MoveFinishEvents.erase(fd);
				removed = true;
			}
			return removed;
		}

		void MapCharacter::DispatchFinishedEvents()
		{
			for (auto ev = MoveFinishEvents.begin(); ev != MoveFinishEvents.end(); ++ev)
			{
				ev->second(this);
			}
		}

		GameMap::GameMap() : UsePythonMove(false), UsePythonScriptClass(false), EncounterRate(0.1f), rng(time(0)), RandomFloatGen(rng, boost::uniform_real<float>(0, 1))
		{
			
		}
		GameMap::GameMap(std::string &name, int tilesWide, int tilesHigh, int tilewidth, int tileheight) : TileMap(name, tilesWide, tilesHigh, tilewidth, tileheight), UsePythonMove(false), UsePythonScriptClass(false), EncounterRate(0.1f), rng(time(0)), RandomFloatGen(rng, boost::uniform_real<float>(0, 1))
		{

		}
		GameMap::GameMap(std::string &file, std::string &name, Engine* engine) : TileMap(file, name, engine), UsePythonMove(false), UsePythonScriptClass(false), EncounterRate(0.1f), rng(time(0)), RandomFloatGen(rng, boost::uniform_real<float>(0, 1))
		{
			std::string scriptFile = MapProperties["Script"];
			if (scriptFile != "")
			{
				engine->GetPythonScripter().AddScriptObject<GameMap>(std::string("CurrentMap"), *this, engine->GetPythonScripter().GetMappingModule());
				engine->GetPythonScripter().RunFile(scriptFile);
			}
			std::string MusicFile = MapProperties["Music"];
			if (MusicFile != "")
			{
				std::vector<std::string> fragments;
				boost::split(fragments, MusicFile, boost::is_any_of(","));
				switch(fragments.size())
				{
				case 1:
					engine->GetSoundSystem().AddSound(fragments[0], fragments[0], true);
					addedSounds.push_back(fragments[0]);
					break;
				case 2:
					engine->GetSoundSystem().AddSound(fragments[0], fragments[1], true);
					addedSounds.push_back(fragments[1]);
					break;
				case 3:
					engine->GetSoundSystem().AddSound(fragments[0], fragments[1], true, true, false, fragments[2].c_str());
					addedSounds.push_back(fragments[1]);
					break;
				}
			} 

			auto background = MapProperties.find("Background");
			if (background != MapProperties.end())
			{
				auto BackgroundString = background->second;
				std::vector<std::string> fragments;
				boost::split(fragments, BackgroundString, boost::is_any_of(","));
				switch(fragments.size())
				{
				case 1:
					Backgrounds.push_back(Graphics::AnimatedSprite(engine->GetContentManager().RequestTexture(fragments[0], Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Background, engine->GetTime())));
					break;
				}
			}
		}
		/*GameMap::GameMap(std::string &file, std::string &name) : TileMap(file, name)
		{

		}*/

		/*void GameMap::SetMoveFunction(MovementFunction &function)
		{

		}*/
		/*void GameMap::SetPythonMoveFunction(boost::python::object function)
		{
			pythonMoveFunction = function;
			UsePythonMove = true;
			UsePythonScriptClass = false;
		}
		void GameMap::SetMapPythonScriptClass(boost::python::object scriptClass)
		{
			MapScriptClass = scriptClass;
			UsePythonScriptClass = true;
			UsePythonMove = false;
		}
		void GameMap::CallMoveFunction(Character::Party &party, MapCharacterSprite &character)
		{
			try
			{
				bool DoEnemyEncounterTest = true;
				if (UsePythonMove)
					pythonMoveFunction(party, character);
				else if (UsePythonScriptClass)
					DoEnemyEncounterTest = MapScriptClass.attr("MoveFunction")(boost::ref(party), boost::ref(character));
				if (DoEnemyEncounterTest)
				{
					float RN = RandomFloatGen();
					if (EncounterRate > RN)
					{

					}
				}
			}
			catch (boost::python::error_already_set)
			{
				PyErr_Print();
			}
			
		}*/
		void GameMap::PlayMusic()
		{
			for(auto mapSounds = addedSounds.begin(); mapSounds != addedSounds.end(); ++mapSounds)
			{
				PrimaryEngine->GetSoundSystem().PlaySound(*mapSounds, 2);
			}
		}
		void GameMap::PauseMusic()
		{
			for(auto mapSounds = addedSounds.begin(); mapSounds != addedSounds.end(); ++mapSounds)
			{
				PrimaryEngine->GetSoundSystem().SetChannelPause(2);
			}
		}

		float GameMap::GetEncounterRate() const
		{
			return EncounterRate;
		}
		void GameMap::SetEncounterRate(const float rate)
		{
			EncounterRate = rate;
		}
		void GameMap::Draw(sf::RenderWindow &window, MapCharacter &mapChar, sf::View &characterView)
		{
			for (auto background = Backgrounds.begin(); background != Backgrounds.end(); ++background)
			{
				background->Draw(window);
			}
			bool characterDrawn = false;
			if (layers.size() > 0)
			{
				sf::Vector2f top = SnapToTiles(window.convertCoords(sf::Vector2i(0, 0)));
				auto size = window.getSize();
				sf::Vector2f bottom = SnapToTiles(window.convertCoords(sf::Vector2i(size.x, size.y)));
				int x_start = std::min((int)top.x - 1, tilesInX - 1);
				x_start = std::max(x_start, 0);
				int x_end = std::min((int)bottom.x + 1, tilesInX - 1);
				x_end = std::max(x_end, 0);

				int y_start = std::min((int)top.y - 1, tilesInY - 1);
				y_start = std::max(y_start, 0);
				int y_end = std::min((int)bottom.y + 1, tilesInY - 1);
				y_end = std::max(y_end, 0);

				//sf::Drawable tile;
				sf::Sprite* tile;
				sf::Vector2f position;
				int limit = tilesInY * tilesInX - 1;
				//charSprite.Draw(window);
				int layerCount = 0;
				for (auto layer = layers.begin(); layer != layers.end(); ++layer, ++layerCount)
				{
					for (int j = y_start; j < y_end; ++j)
					{
						for (int k = x_start; k < x_end; ++k)
						{
							int index = j * (*layer)->GetWidth() + k;
							position.x = k * tileWidth;
							position.y = j * tileHeight;
							if (index > limit)
								continue;
							int tileID = (*layer)->At(index);
							if (tileID <= 0)
								continue;
							for(auto tileset = tileSets.begin(); tileset != tileSets.end(); ++tileset)
							{
								if ((*tileset)->GetFirstGID() <= tileID && (*tileset)->GetEndGID() >= tileID)
								{
									tile = &((*tileset)->GetTile(tileID - (*tileset)->GetFirstGID()));
									tile->setPosition(position);
									window.draw((*tile));
									break;
								}
							}
						}
					}
					if(mapChar.DrawLayer <= layerCount && !characterDrawn)
					{
						sf::View tempView(window.getView());
						window.setView(characterView);
						mapChar.Draw(window);
						//charSprite.Draw(window);
						window.setView(tempView);
						characterDrawn = true;
					}
				}
			}
			if (!characterDrawn)
			{
				sf::View tempView(window.getView());
				window.setView(characterView);
				mapChar.Draw(window);
				//charSprite.Draw(window);
				window.setView(tempView);
				characterDrawn = true;
			}
		}

		void GameMap::Draw(sf::RenderWindow &window, sf::Shader &shader, MapCharacter &mapChar, sf::View &characterView)
		{
			for (auto background = Backgrounds.begin(); background != Backgrounds.end(); ++background)
			{
				background->Draw(window, shader);
			}
			bool characterDrawn = false;
			if (layers.size() > 0)
			{
				sf::Vector2f top = SnapToTiles(window.convertCoords(sf::Vector2i(0, 0)));
				auto size = window.getSize();
				sf::Vector2f bottom = SnapToTiles(window.convertCoords(sf::Vector2i(size.x, size.y)));
				int x_start = std::min((int)top.x - 1, tilesInX - 1);
				x_start = std::max(x_start, 0);
				int x_end = std::min((int)bottom.x + 1, tilesInX - 1);
				x_end = std::max(x_end, 0);

				int y_start = std::min((int)top.y - 1, tilesInY - 1);
				y_start = std::max(y_start, 0);
				int y_end = std::min((int)bottom.y + 1, tilesInY - 1);
				y_end = std::max(y_end, 0);

				//sf::Drawable tile;
				sf::Sprite* tile;
				sf::Vector2f position;
				int limit = tilesInY * tilesInX - 1;
				int layerCount = 0;
				for (auto layer = layers.begin(); layer != layers.end(); ++layer, ++layerCount)
				{
					//if((*current)
					for (int j = y_start; j < y_end; ++j)
					{
						for (int k = x_start; k < x_end; ++k)
						{
							int index = j * (*layer)->GetWidth() + k;
							position.x = k * tileWidth;
							position.y = j * tileHeight;
							if (index > limit)
								continue;
							int tileID = (*layer)->At(index);
							if (tileID <= 0)
								continue;
							for(auto tileset = tileSets.begin(); tileset != tileSets.end(); ++tileset)
							{
								if ((*tileset)->GetFirstGID() <= tileID && (*tileset)->GetEndGID() >= tileID)
								{
									tile = &((*tileset)->GetTile(tileID - (*tileset)->GetFirstGID()));
									tile->setPosition(position);
									window.draw((*tile));
									break;
								}
								//sf::Drawable tile = (*tileset).
							}
							//for (int l = 0; l 
						}
					}
					if(mapChar.DrawLayer <= layerCount && !characterDrawn)
					{
						sf::View tempView(window.getView());
						window.setView(characterView);
						mapChar.Draw(window, shader);
						window.setView(tempView);
						characterDrawn = true;
					}
				}
			}
		}

		//static function
		gmap_ptr GameMap::LoadMapFromXML(std::string &file, std::string &mapName)
		{
			using namespace pugi;
			xml_document mapDoc;
			xml_parse_result result = mapDoc.load_file(file.c_str());
			if (!result)
				std::cout << "Map Failed To Load. Error: " << result.description();
			for(xml_node map = mapDoc.child("map"); map; map = mapDoc.next_sibling("map"))
			{
				int width, height, tilewidth, tileheight;
				width = map.attribute("width").as_int();
				height = map.attribute("height").as_int();
				tilewidth = map.attribute("tilewidth").as_int();
				tileheight = map.attribute("tileheight").as_int();
				gmap_ptr tilemap = gmap_ptr(new GameMap(mapName, width, height, tilewidth, tileheight));
				//TileMap tilemap(mapName, width, height, tilewidth, tileheight);
				xml_node properties = map.child("properties");
				for (xml_node prop = properties.child("property"); prop; prop = prop.next_sibling("property"))
				{

				}

				for(xml_node tileset = map.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
				{
					int firstGID, tstilewidth, tstileheight;
					std::string name = tileset.attribute("name").value();
					firstGID = tileset.attribute("firstgid").as_int();
					tstilewidth = tileset.attribute("tilewidth").as_int();
					tstileheight = tileset.attribute("tileheight").as_int();
					xml_node imageFile =  tileset.child("image");
					std::string imageSource = imageFile.attribute("source").value();
					sf::Texture tileSetImage;
					if (tileSetImage.loadFromFile(imageSource))
					{
						::Mapping::tileset_ptr tileset = ::Mapping::tileset_ptr(new ::Mapping::TileSet(name, firstGID, tstilewidth, tstileheight, tileSetImage));
						tilemap->AddTileSet(tileset);
					}
					else
					{
						std::cerr << "Failed to load Image for tileset: " << name << std::endl;
					}
				}
				for(xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
				{
					std::string name;
					int lwidth, lheight;
					int drawOrder = 0;
					float opacity = 1;
					bool isCollision = false;
					CompType compression = CompType::NoCompression;
					StringEncoding encoding = StringEncoding::NoEncoding;
					std::vector<LayerProperty> layerPropertySet;
					boost::unordered_set<std::string> enforceOn;
					name = layer.attribute("name").value();
					lwidth = layer.attribute("width").as_int();
					lheight = layer.attribute("height").as_int();
					xml_node layerProperties = layer.child("properties");
					for (xml_node prop = layerProperties.child("property"); prop; prop = prop.next_sibling("property"))
					{
						std::string name, value;
						name = prop.attribute("name").value();
						value = prop.attribute("value").value();
						boost::to_lower(name);
						boost::to_lower(value);
						if ((name == "collision layer") && (value == "true"))
						{
							isCollision = true;
						}
						else if (name == "draw order")
						{
							drawOrder = atoi(value.c_str());
						}
						else if (name == "enforce on" && value.length() > 0)
						{
							std::vector<std::string> frags;
							boost::split(frags, value, boost::is_any_of(":;,"));
							for (unsigned int i = 0; i < frags.size(); ++i)
							{
								std::string target = frags[i];
								boost::trim(target);
								enforceOn.insert(target);
							}
						}
						else
						{
							LayerProperty prop(name, value);
							layerPropertySet.push_back(prop);
						}
					}
					xml_node data = layer.child("data");
					std::string encodingAttr = data.attribute("encoding").value();
					if (encodingAttr == "base64")
						encoding = StringEncoding::Base64;
					std::string compressAttr = data.attribute("compression").value();
					if (compressAttr == "gzip")
						compression = CompType::GZip;
					std::string dataString = data.child_value();
					boost::trim(dataString);
					if (encoding == StringEncoding::Base64)
						dataString = base64_decode(dataString);
					if (compression == CompType::GZip)
						dataString = GunzipString(dataString);
					if (isCollision)
					{
						col_layer_ptr colLayer = col_layer_ptr(new CollisionLayer(name, lwidth, lheight, tilewidth, tileheight, 
							dataString,enforceOn));
						colLayer->SetExtendedProperties(layerPropertySet);
						colLayer->SetDrawOrder(drawOrder);
						tilemap->AddCollisionLayer(colLayer);
					}
					else
					{
						layer_ptr layer = layer_ptr(new Layer(name, lwidth, lheight, tilewidth, tileheight, dataString));
						//Layer layer(name, lwidth, lheight, tilewidth, tileheight, dataString);
						layer->SetDrawOrder(drawOrder);
						layer->SetExtendedProperties(layerPropertySet);
						tilemap->AddLayer(layer);

					}
				}
				return tilemap;
			}
			return gmap_ptr();
		}

		GameMap::~GameMap()
		{
			
		}
	}
}