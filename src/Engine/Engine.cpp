#include "Engine.h"


Engine::Engine() : IDIncrementer(0), Ready(false), baseRocketInterface(Rocket::Core::String("rml")), Running(true)
{
	srand(time(0));
	rng.seed(time(0));
}
Engine::Engine(const std::string& configFile, sf::RenderWindow* window, const sf::Vector2i Resolution_, bool AllowMultipleInputs) : 
	IDIncrementer(0), Ready(false), Resolution(Resolution_), baseRocketInterface(Rocket::Core::String("")), Running(true)
{
	srand(time(0));
	rng.seed(time(0));
	ApplicationConfiguration.Initialize(configFile);
	ContentManager.Initialize(ApplicationConfiguration);
	PScripter.SetPath(ApplicationConfiguration.GetApplicationSetting("ResourcesBaseDirectory") + ApplicationConfiguration.GetApplicationSetting("ScriptPath"));
	PScripter.AddScriptObject<Engine>("Engine", *this, PScripter.GetEngineModule());
	PrimarySoundSystem.SetAudioDirectory(ApplicationConfiguration.GetApplicationSetting(std::string("ResourcesBaseDirectory")) + ApplicationConfiguration.GetApplicationSetting(std::string("MusicSubDir")));
	PrimarySoundSystem.SetSoundEffectsDirectory(ApplicationConfiguration.GetApplicationSetting(std::string("ResourcesBaseDirectory")) + ApplicationConfiguration.GetApplicationSetting(std::string("SoundEffectsDir")));
	Input.Load(configFile, this);
	
	Input.AddKeyPressedEvent(boost::bind(&Graphics::Screens::ScreenManager::HandleKeyPressed, &ScreenManager, _1, _2, _3));
	Input.AddKeyReleasedEvent(boost::bind(&Graphics::Screens::ScreenManager::HandleKeyReleased, &ScreenManager, _1, _2, _3)); 
	baseRocketInterface.SetRootDirectory(this->ContentManager.GetHTMLDirectory().c_str());
	baseRocketRenderer.target = window;
	Rocket::Core::SetRenderInterface(&baseRocketRenderer);
	Rocket::Core::SetFileInterface(&baseRocketInterface);
	Rocket::Core::SetSystemInterface(&baseRocketSystem);
	Rocket::Core::Initialise();
	
	//Prep Font Database
	Rocket::Core::FontDatabase::LoadFontFace((this->ContentManager.GetFontDirectory() + "Chaney Normal.ttf").c_str(), "Chaney", Rocket::Core::Font::Style::STYLE_NORMAL, Rocket::Core::Font::Weight::WEIGHT_NORMAL);
	Rocket::Core::FontDatabase::LoadFontFace((this->ContentManager.GetFontDirectory() + "Chaney Italic.ttf").c_str(), "Chaney", Rocket::Core::Font::Style::STYLE_ITALIC, Rocket::Core::Font::Weight::WEIGHT_NORMAL);
	Rocket::Core::FontDatabase::LoadFontFace((this->ContentManager.GetFontDirectory() + "Chaney Bold.ttf").c_str(), "Chaney", Rocket::Core::Font::Style::STYLE_NORMAL, Rocket::Core::Font::Weight::WEIGHT_BOLD);
	Rocket::Core::FontDatabase::LoadFontFace((this->ContentManager.GetFontDirectory() + "Chaney Bold Italic.ttf").c_str(), "Chaney", Rocket::Core::Font::Style::STYLE_ITALIC, Rocket::Core::Font::Weight::WEIGHT_BOLD);

	Rocket::Core::FontDatabase::LoadFontFace((this->ContentManager.GetFontDirectory() + "Eurostile.ttf").c_str(), "Eurostile", Rocket::Core::Font::Style::STYLE_NORMAL, Rocket::Core::Font::Weight::WEIGHT_NORMAL);

	Ready = true;

}
Engine::~Engine()
{
	Rocket::Core::Shutdown();
}
int Engine::GetUID()
{
	return ++IDIncrementer;
}
bool Engine::IsReady() const
{
	return Ready;
}
void Engine::HandleWindowEvents(sf::RenderWindow &GameWindow, bool& ContinueRunning)
{
	sf::Event event;
	while(GameWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::LostFocus:
			{
				//PrimaryInput.SetActive(false);
			}
			break;
		case sf::Event::GainedFocus:
			{
				//PrimaryInput.SetActive(true);
			}
			break;
		case sf::Event::Closed:
			{
				ContinueRunning = false;
			}
			break;
		case sf::Event::KeyPressed:
			{
				Input.DispatchKeyPressedEvents(this->GetTime(), event.key);
			}
			break;
		case sf::Event::KeyReleased:
			{
				//std::cout << "Key Released in Engine\n";
				Input.DispatchKeyReleasedEvents(this->GetTime(), event.key);
			}
			break;
		case sf::Event::JoystickButtonPressed:
			{
				Input.DispatchJoystickKeyPressedEvents(this->GetTime(), event.joystickButton);
			}
			break;
		case sf::Event::JoystickButtonReleased:
			{
				Input.DispatchJoystickKeyReleasedEvents(this->GetTime(), event.joystickButton);
			}
			break;
		case sf::Event::JoystickMoved:
			{
				
			}
			break;
		}
	}
}
void Engine::DispatchInputs()
{

}

sf::Uint32 Engine::GetTime()
{
	return TimeModule.GetGameElapsedTime();
}
//Get Subsystems
Audio::SoundSystem& Engine::GetSoundSystem()
{
	return PrimarySoundSystem;
}
Scripting::PythonScripter& Engine::GetPythonScripter()
{
	return PScripter;
}
Configuration::AppConfiguration& Engine::GetApplicationConfiguration()
{
	return ApplicationConfiguration;
}
Time::GameTimeModule& Engine::GetGameTimeModule()
{
	return TimeModule;
}
Content::ContentManager& Engine::GetContentManager()
{
	return ContentManager;
}

Input::InputModule& Engine::GetInput()
{
	return Input;
}

Graphics::Screens::ScreenManager& Engine::GetScreenManager()
{
	return ScreenManager;
}

const sf::Vector2i& Engine::GetResolution() const
{
	return Resolution;
}
bool Engine::IsRunning() const
{
	return Running;
}

void Engine::Draw(sf::RenderWindow &window) 
{
	ScreenManager.Draw(window);
}
void Engine::Draw(sf::RenderWindow &window, sf::Shader &shader) 
{
	ScreenManager.Draw(window, shader);
}

void Engine::Update(const sf::Uint32 time, const float TimeScale)
{
	ScreenManager.Update(time, TimeScale);
}
void Engine::Update(const float time, const float TimeScale)
{
	Update(static_cast<sf::Uint32>(time * 0.001), TimeScale);
}