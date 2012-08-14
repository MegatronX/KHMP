#pragma once
#ifndef _GAMEMAP_H_
#define _GAMEMAP_H_
#include <boost/shared_ptr.hpp>
#include <character/Party.h>
#include <character/BaseCharacter.h>
#include <boost/function.hpp>
#include <boost/python.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/signal.hpp>
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include <Engine.h>
#include <mapping/TileMap.h>
#include <system/input/InputModule.h>

#include <Graphics/Sprites/AnimatedSprite.h>

namespace Graphics
{
	namespace Screens
	{
		class MapViewLayer;
	}
}

namespace Game
{
	namespace Mapping
	{
		struct MapCharacter;
		typedef boost::function<void(MapCharacter*)> MovementFinished;
		struct MapCharacter : public ::Graphics::AnimatedDraw
		{
			MapCharacter();

			virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) override;
			virtual void Draw(sf::RenderWindow &window) override;
			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;

			void SlideMapPosition(const sf::Vector2f &TargetPos, const sf::Vector2i &tileAdder, sf::Uint32 slideTime, sf::Uint32 currentTime);

			bool AddFinishedEvent(const std::string& index, const MovementFinished& handler);
			bool RemoveFinishedEvent(const std::string& index);
			void DispatchFinishedEvents();

			::Graphics::AnimatedSprite CharSpr;
			sf::Vector2f TargetPosition;
			sf::Vector2f TranslationVector;
			sf::Vector2f MapPosition;
			sf::Vector2f MapTilePosition;
			sf::Vector2f ScreenPosition;
			sf::Vector2f Speed;
			sf::Vector2f ViewOffset;
			bool FollowInX;
			bool FollowInY;
			bool InTransit;

			int DrawLayer;

			sf::Uint32 TargetTime;
			sf::Uint32 LastUpdate;

			boost::unordered_map<std::string, MovementFinished> MoveFinishEvents;
		};
		typedef boost::mt19937 RNGType;
		class GameMap : public ::Mapping::TileMap
		{
		public:
			GameMap();
			GameMap(std::string &name, int tilesWide, int tilesHigh, int tilewidth, int tileheight);
			GameMap(std::string &file, std::string &name, Engine* engine);
			//GameMap(std::string &file, std::string &name);

			void PlayMusic();
			void PauseMusic();

			float GetEncounterRate() const;
			void SetEncounterRate(const float rate);

			static boost::shared_ptr<GameMap> LoadMapFromXML(std::string &file, std::string &mapName);

			virtual void Draw(sf::RenderWindow &window, MapCharacter &mapChar, sf::View &characterView);

			virtual void Draw(sf::RenderWindow &window, sf::Shader &shader, MapCharacter &mapChar, sf::View &characterView);

			//Character::party_ptr GetPlayerParty() const;
			//void SetParty(const Character::party_ptr party);

			friend class ::Graphics::Screens::MapViewLayer;
			//virtual void ReleaseResources();
			virtual ~GameMap();
		protected:
			bool UsePythonMove;
			bool UsePythonScriptClass;
			boost::python::object MapScriptClass;
			boost::python::object pythonMoveFunction;
			boost::python::object pythonActionFunction;
			std::vector<std::string> addedSounds;
			sf::Texture Background;
			sf::Sprite BackSprite;
			std::vector<Graphics::AnimatedSprite> Backgrounds;
			//boost::uniform_real<float> floatRange;
			//boost::variate_generator<RNGType&, boost::uniform_real<float> > gen;//(rng, floatRange);
		private:
			float EncounterRate;
			RNGType rng;
			boost::variate_generator<RNGType&, boost::uniform_real<float> > RandomFloatGen;
		};
		typedef boost::shared_ptr<GameMap> gmap_ptr;
	}
}


#endif