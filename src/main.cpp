#include <string>
#include <iostream>
#include <sfml/Graphics.hpp>
#include <sfml/System.hpp>
#include <Engine.h>
#include <boost/python.hpp>
#include <GameInstance.h>
#include <Graphics/Screens/BasicRMLScreen.h>
#include <Graphics/Rocket/PositionTransformer.h>
#include <Graphics/Rocket/FaderTransform.h>
#include <graphics/Screens/TitleScreen.h>
#include <minigames//triad/Deck.h>
#include <character/StatsManager.h>
static const std::string CommandHead = "from EngineModule import *\n";
void CommandLineIssuer(Engine* engine)
{
	std::string Command;//[256];
	while(true)
	{
		std::getline(std::cin, Command);
		engine->GetPythonScripter().RunString(CommandHead + Command);
	}
}

using namespace std;
using namespace Game;
int main()
{
	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.SetFramerateLimit(120);
		Engine GameEngine("Config.xml", &GameWindow, Res);
		Game::GameInstance GameInst(GameEngine, false);
		//GameEngine.GetPythonScripter().RunFile("TitleScreen.py");
		int x = 10;
		//Game::Graphics::GameRocket::BasicRMLScreen screen("Inv", "TitleScreen.rml", &GameEngine, GameEngine.GetUID());
		//Game::Graphics::Screens::TitleScreen TitleScr(&GameEngine);
		/*auto ceira = screen.GetDocument()->GetElementById(Rocket::Core::String("CeiraImg"));

		auto transformer = new Graphics::GameRocket::ElementTransformer(ceira);

		auto ptrans = Graphics::GameRocket::eletransform_ptr(new Graphics::GameRocket::PositionTransformer(transformer, sf::Vector2f(400, 200), GameEngine.GetTime(), GameEngine.GetTime() + 4000));
		auto ftrans = Graphics::GameRocket::eletransform_ptr(new Graphics::GameRocket::FaderTransform(nullptr, 255, 0, GameEngine.GetTime(), GameEngine.GetTime() + 5000));
		auto ftrans2 =  Graphics::GameRocket::eletransform_ptr(new Graphics::GameRocket::FaderTransform(nullptr, 0, 255, GameEngine.GetTime(), GameEngine.GetTime() + 5000));
		*/
		//auto obj = GameEngine.GetPythonScripter().RunFile("TitleScreen.py");
		
		/*ptrans->AddPostTransform(ftrans, 5000);
		ftrans->AddPostTransform(ftrans2, 5000);
		ftrans2->AddPostTransform(ftrans, 5000);
		transformer->AddTransformation(ptrans);
		//screen.AddNewTransform("Test Trans", transformer);
		transformer->SetTarget(ceira);
		Graphics::GameRocket::ElementTransformer* trans = new Graphics::GameRocket::ElementTransformer();
		Graphics::GameRocket::PositionTransformer* pTrans = new Graphics::GameRocket::PositionTransformer(GameEngine.GetTime(), GameEngine.GetTime() + 4000, sf::Vector2f(100, 0));
		Graphics::GameRocket::ElementTransformationInterface* col = new Graphics::GameRocket::FaderTransform(0, 255, GameEngine.GetTime(), GameEngine.GetTime() + 12000);

		trans->AddTransformation(pTrans);
		trans->AddTransformation(col);
		screen.AddNewTransform("Test Trans", trans);
		trans->SetTarget(screen.GetDocument()->GetElementById(Rocket::Core::String("CeiraImg")));
		pTrans->Initialize(trans);
		col->Initialize(trans);*/
		//trans->AddTransformation()
		//screen.Add

		int arStats[Character::StatCount] = {324, 34, 37, 32, 29, 28, 24, 34, 40, 20, 20, 200, 49};

		Character::BaseCharacter Arian("Arian", arStats);

		auto SManager = Arian.GetComponentAs<Character::StatsManager*>("StatsManager");
		SManager->SyncAllBattleStats();
		auto SEManager = Arian.GetComponentAs<StatusEffects::StatusEffectsManager*>("StatusEffectsManager");
		auto haste = GameInst.GetSELibrary().GetStatusEffect("Haste");
		SEManager->AddStatusEffect("Haste", DEFAULT_TURNS);
		SEManager->RemoveStatusEffect("Haste");
		Game::MiniGames::Triad::Test(&GameEngine);
		sf::Thread CommandThread(&CommandLineIssuer, &GameEngine);
		CommandThread.Launch();
		sf::Uint32 time = GameEngine.GetTime();
		std::cout << "First Time: " << time << std::endl;
		for(bool Running = true; Running; time = GameEngine.GetTime())
		{
			
			GameEngine.HandleWindowEvents(GameWindow, Running);
			//screen.Update(GameEngine.GetTime());
			//TitleScr.Update(GameEngine.GetTime());
			GameEngine.Update(time);
			
			GameWindow.Clear();
			GameEngine.Draw(GameWindow);
			//TitleScr.Draw(GameWindow);
			//screen.Draw(GameWindow);
			
			GameWindow.Display();

		}
		GameWindow.Close();
		CommandThread.Terminate();
	}
	catch (boost::python::error_already_set)
	{
		PyErr_Print();
	}
	catch (std::exception ex)
	{

	}
	return EXIT_SUCCESS;
}