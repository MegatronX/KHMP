#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_
#include <ctime>
#include <ContentManagement/ContentManager.h>
#include <Audio/SoundSystem.h>
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>
#include <scripting/Python/PythonScripter.h>
#include <Time/GameTimeModule.h>
#include <sfml/Window.hpp>
#include <random>
#include <system/input/InputModule.h>
#include <graphics/Screens/ScreenManager.h>
#include <Rocket/Core.h>
#include <Graphics/Rocket/BaseFileInterface.h>
#include <Graphics/Rocket/LibRocketRenderInterace.h>
#include <Graphics/Rocket/RocketSystemInterface.h>
#include <Graphics/AnimatedDraw.h>
class Engine : public Graphics::AnimatedDraw, private boost::noncopyable
{
public:
	Engine();
	Engine(const std::string& configFile, sf::RenderWindow* window, const sf::Vector2i Resolution = sf::Vector2i(800, 600), bool AllowMultipleInputs = true);
	int GetUID();
	bool IsReady() const;

	void Engine::HandleWindowEvents(sf::RenderWindow &GameWindow, bool& ContinueRunning);
	void DispatchInputs();

	sf::Uint32 GetTime();
	//Get Subsystems
	Audio::SoundSystem& GetSoundSystem();
	Scripting::PythonScripter& GetPythonScripter();
	Configuration::AppConfiguration& GetApplicationConfiguration();
	Time::GameTimeModule& GetGameTimeModule();
	Content::ContentManager& GetContentManager();
	Input::InputModule& GetInput();
	Graphics::Screens::ScreenManager& GetScreenManager();
	const sf::Vector2i& GetResolution() const;
	bool IsRunning() const;

	//Draw Interface

	virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0);
	virtual void Update(const float time, const float TimeScale = 1.0);
	virtual void Draw(sf::RenderWindow &window);
	virtual void Draw(sf::RenderWindow &window, sf::Shader &shader);

	~Engine();

	//Random

	template <class T>
	T GetRandomInt()
	{
		return static_cast<T>(uint_dist(rng));
	}

	template <class T>
	T GetRandomInt(const std::uniform_int_distribution<T>& distr)
	{
		return distr(rng);
	}

	template <class T>
	T GetRandomDouble()
	{
		return static_cast<T>(double_dist(rng));
	}

	template <class T>
	T GetRandomDouble(const std::uniform_real_distribution<T>& distr)
	{
		distr(rng);
	}
protected:
private:
	/*Engine(const Engine& eng)
	{
	}
    Engine& operator=(const Engine& cng)
	{
		return *this;
	}*/	

	//Subsystems
	Audio::SoundSystem PrimarySoundSystem;
	Scripting::PythonScripter PScripter;
	Configuration::AppConfiguration ApplicationConfiguration;
	Content::ContentManager ContentManager;
	Time::GameTimeModule TimeModule;
	Input::InputModule Input;
	Graphics::Screens::ScreenManager ScreenManager;
	Graphics::RocketInterface::BaseFileInterface baseRocketInterface;
	Graphics::RocketInterface::RocketSFMLRenderer baseRocketRenderer;
	Graphics::RocketInterface::RocketSystemInterface baseRocketSystem;
	//Rocket::Core::RenderInterface* RocketRenderer;
	//Rocket::Core::FileInterface* RocketFile;
	//Rocket::Core::SystemInterface* RocketSystem;
	int IDIncrementer;
	bool Ready;
	bool Running;
	sf::Vector2i Resolution;

	//Random
	std::mt19937 rng;
	std::uniform_int_distribution<uint32_t> uint_dist;
	std::uniform_real_distribution<double> double_dist;
};
#endif