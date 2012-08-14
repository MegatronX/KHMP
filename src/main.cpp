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
#include <Graphics/Sprites/Sprite.h>
#include <Graphics/Sprites/AnimatedSprite.h>
#include <Graphics/Animation/FrameAnimation.hpp>
#include <minigames//triad/Deck.h>
#include <character/StatsManager.h>
#include <character/Party.h>

#include <components/ElementWeightComponent.h>

#include <battle/BattleField.h>
#include <battle/mechanics/Mechanics.h>
#include <components/ApplyEffectComponent.h>
#include <battle/mechanics/ATBTurnGenerator.h>

#include <Graphics/Screens/MapViewLayer.h>
#include <graphics/Screens/GameMapViewScreen.h>
using namespace std;
using namespace Game;


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

void BattleTest(Engine& GameEngine, GameInstance& GameInst)
{
	int arStats[Character::StatCount] = {324, 34, 37, 32, 29, 28, 24, 34, 52, 40, 40, 200, 49};
	arStats[Character::Speed] = 128;
	std::string BattleCompIndex = "BattleCharacterComponent";
	auto Arian = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Arian", arStats));

	int crStats[Character::StatCount] = {314, 44, 39, 32, 31, 28, 24, 34, 47, 25, 20, 200, 49};
	crStats[Character::Speed] = 180;
	auto Ceira = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Ceira", crStats));



	auto ele = Arian->GetComponentAs<Components::ElementEffectivenessComponent*>("ElementEffectivenessComponent");
	ele->SetEffectivness(Elements::Ice, 2.f);

	int corrStat[] = {624, 34, 37, 32, 29, 28, 24, 34, 40, 20, 20, 200, 49};
	corrStat[Character::Speed] = 128;
	auto Corrupted = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Corrupted1", corrStat));

	int xaxStat[] = {624, 34, 37, 32, 29, 28, 24, 134, 140, 120, 120, 200, 49};
	auto Xax = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Xaxion", xaxStat));

	Character::bparty_ptr Party(new Character::BaseParty("PlayerParty"));

	Party->AddMember(Arian, "Arian");
	//Arian->SetParty(Party.get());
	Party->AddMember(Ceira, "Ceira");
	//Ceira->SetParty(Party.get());
	Character::bparty_ptr EnemyParty(new Character::BaseParty("EnemyParty"));
	EnemyParty->AddMember(Corrupted, Corrupted->GetName());
	EnemyParty->AddMember(Xax, Xax->GetName());

	auto bchar = boost::shared_ptr<Battle::BattleCharacterComponent>(new Battle::BattleCharacterComponent(Arian.get(), nullptr, Party.get()));
	Arian->RegisterComponent(BattleCompIndex, bchar);
	Arian->GetComponentAs<Character::StatsManager*>("StatsManager")->SyncAllBattleStats();

	bchar = boost::shared_ptr<Battle::BattleCharacterComponent>(new Battle::BattleCharacterComponent(Ceira.get(), nullptr, Party.get()));
	Ceira->GetComponentAs<Character::StatsManager*>("StatsManager")->SyncAllBattleStats();
	Ceira->RegisterComponent(BattleCompIndex, bchar);

	Corrupted->GetComponentAs<Character::StatsManager*>("StatsManager")->SyncAllBattleStats();
	bchar = boost::shared_ptr<Battle::BattleCharacterComponent>(new Battle::BattleCharacterComponent(Corrupted.get(), nullptr, EnemyParty.get()));
	Corrupted->RegisterComponent(BattleCompIndex, bchar);

	Xax->GetComponentAs<Character::StatsManager*>("StatsManager")->SyncAllBattleStats();
	bchar = boost::shared_ptr<Battle::BattleCharacterComponent>(new Battle::BattleCharacterComponent(Xax.get(), nullptr, EnemyParty.get()));
	Xax->RegisterComponent(BattleCompIndex, bchar);

	Battle::BattleField Field(Party, EnemyParty);
	Field.PreBattlePhase();
	Field.BattlePhase();

	//Field.GetTurnGenerator()->GenerateNextCharacter(520);

	int ContinueBattle = 0;
	auto start = GameEngine.GetTime();
	//while(true)
	//	sf::sleep(sf::milliseconds(50));
	try
	{
		auto haste = GameInst.GetSELibrary().GetStatusEffectClone("Haste");
		auto reflect = GameInst.GetSELibrary().GetStatusEffectClone("Reflect");


		Corrupted->GetStatusEffectsManager().AddStatusEffect(reflect, reflect->GetRecommendedTicks());
		auto comp0 = reflect->GetComponent("FinalizeTargetsModifier");
		auto hcomp = haste->GetComponentAs<Components::ApplyEffectComponent*>("ApplyEffectComponent");
		//hcomp->Apply(Arian.get());
		Arian->GetStatusEffectsManager().AddStatusEffect("Haste", 11);
		Arian->GetStatusEffectsManager().AddStatusEffect("God Mode", 12);
		Ceira->GetStatusEffectsManager().AddStatusEffect("Storm Drain", 9);
	}
	catch (const boost::python::error_already_set& ex)
	{
		PyErr_Print();
		std::string exp = "";
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
	}

	try
	{
		for(;ContinueBattle < 0; ++ContinueBattle)
		{
			//Battle Test
			auto blizzard = GameInst.GetActionLibrary().GetAction("Blizzard");
			blizzard->Targets.AddCharacter(Corrupted.get());
			blizzard->Targets.AddCharacter(Arian.get());
			blizzard->Users.AddCharacter(Arian.get());
			blizzard->Users.AddCharacter(Ceira.get());
			auto elecomp = blizzard->GetComponentAs<Components::ElementWeightComponent*>("ElementalWeightComponent");

			auto megiddo = GameInst.GetActionLibrary().GetAction("Megiddo Flame");

			megiddo->Targets.AddCharacter(Corrupted.get());
			megiddo->Users.AddCharacter(Arian.get());
			megiddo->Users.AddCharacter(Ceira.get());

			Field.GetMechanics().ProcessActionDefault(*blizzard);

			Field.GetMechanics().ProcessActionDefault(*megiddo);

			auto water = GameInst.GetActionLibrary().GetAction("Wateraga");
			water->Targets.AddCharacter(Corrupted.get());
			water->Targets.AddCharacter(Arian.get());
			water->Users.AddCharacter(Arian.get());

			Field.GetMechanics().ProcessActionDefault(*water);
		}
	}
	catch (const boost::python::error_already_set& ex)
	{
		PyErr_Print();
		std::string exp = "";
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
	}
}

#include <Graphics/Camera/Camera.h>

int main_()
{
	//Use to test sf::view manipulation

	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.setFramerateLimit(60);
		Engine GameEngine("Config.xml", &GameWindow, Res);
		Game::GameInstance GameInst(GameEngine, false);

		sf::Thread CommandThread(&CommandLineIssuer, &GameEngine);
		CommandThread.launch();
		sf::Texture kida;
		kida.loadFromFile("..\\..\\..\\resources\\Graphics\\Sprites\\kida.png");
		sf::Sprite KidaPlat(kida);

		sf::Texture yuko;
		yuko.loadFromFile("..\\..\\..\\resources\\Graphics\\Sprites\\Enemies\\Yuko.gif");
		
		sf::Sprite yukoSp(yuko);

		yukoSp.setPosition(kida.getSize().x * 0.3, kida.getSize().y * 0.3);

		sf::Uint32 time = GameEngine.GetTime();

		::Graphics::Camera cam;
		sf::View view;
		sf::View defaultView = GameWindow.getView();
		for(bool Running = true; Running; time = GameEngine.GetTime())
		{

			GameEngine.HandleWindowEvents(GameWindow, Running);
			GameEngine.Update(time);
			GameWindow.clear();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				cam.Rotate(sf::Vector3f(1.f, 0.f, 0.f));
				view.rotate(0.8f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				cam.Rotate(sf::Vector3f(-1.f, 0.f, 0.f));
				view.rotate(-0.8f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				cam.Rotate(sf::Vector3f(0.f, 1.f, 0.f));
				view.setSize(view.getSize().x, view.getSize().y -5.f);
				
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				cam.Rotate(sf::Vector3f(0.f, -1.f, 0.f));
				view.setSize(view.getSize().x, view.getSize().y + 5.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				cam.Rotate(sf::Vector3f(0.f, 0.f, 1.f));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			{
				cam.Rotate(sf::Vector3f(0.f, 0.f, -1.f));
			}
			auto trans = view.getTransform();
			auto pos = sf::Vector2f(yukoSp.getPosition());
			auto transpos = trans.transformPoint(pos);
			
			pos = sf::Vector2f(transpos.x * pos.x, transpos.y * pos.y);

			yukoSp.setPosition(pos);
			//cam.Set();
			GameWindow.setView(view);
			//GameEngine.Draw(KidaPlat);
			GameWindow.draw(KidaPlat);
			GameWindow.setView(defaultView);
			GameWindow.draw(yukoSp);
			
			//spr.Draw(GameWindow);
			//aspr.Draw(GameWindow);
			//ts->Draw(GameWindow);
			GameWindow.display();

			yukoSp.setPosition(pos);
		}

	}
	catch(std::exception ex)
	{

	}
	return EXIT_SUCCESS;
}

int main()
{
	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.setFramerateLimit(90);
		Engine GameEngine("Config.xml", &GameWindow, Res);
		Game::GameInstance GameInst(GameEngine, false);

		sf::Thread CommandThread(&CommandLineIssuer, &GameEngine);
		CommandThread.launch();

		sf::Uint32 time = GameEngine.GetTime();
		//Engine* engine, std::string &mapFile, sf::Vector2f &startPos, sf::RenderWindow* window, std::string &name, int layerID = -1
		auto lyptr = boost::shared_ptr<Game::Graphics::Screens::GameMapViewScreen>(new Game::Graphics::Screens::GameMapViewScreen(&GameEngine, std::string("Station1.tmx"), sf::Vector2f(20 * 32, 20 * 32), &GameWindow, std::string("Station"), GameEngine.GetUID()));
		//GameEngine.GetInput().AddKeyPressedEvent(boost::bind(::Graphics::Screens::MapViewLayer::HandleKeyPressed, ly.HandleKeyPressed, _1, _2, _3));

		::Graphics::Camera cam;
		sf::View view;
		sf::View defaultView = GameWindow.getView();
		GameEngine.GetScreenManager().AddScreen(lyptr);
		for(bool Running = true; Running; time = GameEngine.GetTime())
		{

			GameEngine.HandleWindowEvents(GameWindow, Running);
			GameEngine.Update(time);
			GameWindow.clear();
			
			GameEngine.Draw(GameWindow);
			//cam.Set();
			GameWindow.display();

		}

	}
	catch(std::exception ex)
	{

	}

	return EXIT_SUCCESS;
}

int main_primary()
{
	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.setFramerateLimit(60);
		Engine GameEngine("Config.xml", &GameWindow, Res);
		Game::GameInstance GameInst(GameEngine, false);

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





		/*auto SManager = Arian.GetComponentAs<Character::StatsManager*>("StatsManager");
		SManager->SyncAllBattleStats();
		auto SEManager = Arian.GetComponentAs<StatusEffects::StatusEffectsManager*>("StatusEffectsManager");
		auto haste = GameInst.GetSELibrary().GetStatusEffect("Haste");
		SEManager->AddStatusEffect("Haste", DEFAULT_TURNS);
		SEManager->RemoveStatusEffect("Haste");
		Game::MiniGames::Triad::Test(&GameEngine);*/
		sf::Thread CommandThread(&CommandLineIssuer, &GameEngine);
		CommandThread.launch();
		sf::Uint32 time = GameEngine.GetTime();
		std::cout << "First Time: " << time << std::endl;

		auto tx = GameEngine.GetContentManager().RequestTexture("Arian Test 2", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Guardian, GameEngine.GetTime());
		::Graphics::Sprite spr(tx);
		spr.SetPosition(100, 400);
		::Graphics::Sprite spr2(tx);
		spr2.SetPosition(100, 400);

		auto cr = GameEngine.GetContentManager().RequestTexture("Ceira", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Guardian, GameEngine.GetTime());

		::Graphics::AnimatedSprite aspr(cr, false);
		::Graphics::FrameAnimation idle;
		for (int i = 0; i < 4; ++i)
			idle.addFrame(1.f, sf::IntRect(128 * i, 0, 128, 128));

		aspr.GetAnimator().setDefaultAnimation(idle, sf::seconds(2.f));
		aspr.GetAnimator().addAnimation("Idle", idle, sf::seconds(2.f));
		aspr.GetAnimator().playAnimation("Idle");

		const Items::Item* bcryst = GameInst.GetItemLibrary().GetItemByName("Blazing Crystal");
		auto descr = bcryst->GetDescription();
		sf::Uint32 prev = time;

		sf::Clock frameClock;
		
		
		GameEngine.GetPythonScripter().RunFile("TitleScreen.py");
		auto ts = GameEngine.GetScreenManager().GetScreenStack("TitleScreen");
		try
		{

			for(bool Running = true; Running; time = GameEngine.GetTime())
			{

				GameEngine.HandleWindowEvents(GameWindow, Running);
				GameEngine.Update(time);
				GameWindow.clear();
				GameEngine.Draw(GameWindow);
				//spr.Draw(GameWindow);
				//aspr.Draw(GameWindow);
				//ts->Draw(GameWindow);
				GameWindow.display();


			}
		}
		catch (boost::python::error_already_set)
		{
			PyErr_Print();
			std::string exp = "";
		}
		GameWindow.close();
		CommandThread.terminate();
	}
	catch (const boost::python::error_already_set& ex)
	{
		PyErr_Print();
		std::string exp = "";
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
	}

	int gf;
	std::cin >> gf;
	return EXIT_SUCCESS;
}