#include <string>
#include <iostream>
#include <sfml/Graphics.hpp>
#include <sfml/System.hpp>
#include <Engine.h>
#include <boost/python.hpp>
#include <boost/bind.hpp>
#include <GameInstance.h>
#include <Graphics/Screens/BasicRMLScreen.h>
#include <Graphics/Rocket/PositionTransformer.h>
#include <Graphics/Rocket/FaderTransform.h>
#include <graphics/Screens/TitleScreen.h>
#include <minigames//triad/Deck.h>
#include <character/StatsManager.h>
#include <messaging/MessageQueueVisualizer.h>
#include <Graphics/Animation/FrameAnimation.h>
#include <Graphics/Animation/Animator.h>
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

void SetUpAnimationTest(::Graphics::Animator& Anim, Engine& GameEngine, boost::shared_ptr<sf::Texture>& texture)
{
	
	auto defaultAnim = ::Graphics::FrameAnimation::create();
	defaultAnim->AddFrame(1.f, sf::IntRect(0, 0, 128, 128));	
	Anim.AddAnimation("Standing", defaultAnim, sf::milliseconds(2000));

	auto idle = ::Graphics::FrameAnimation::create();
	for (int i = 0; i < 4; ++i)
	{
		idle->AddFrame(1.f, sf::IntRect(i * 128, 0, 128, 128));
	}
	Anim.AddAnimation("Idle", idle, sf::milliseconds(1400));

	Anim.SetDefaultAnimation(defaultAnim, sf::milliseconds(2000));
}

int main()
{
	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.setFramerateLimit(120);
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
		CommandThread.launch();

		Game::Graphics::MessageQueue MQueue;
		Game::Graphics::MessageQueueVisualizer::SetupEmoteDubDir(&GameEngine);
		MQueue.AddMessage("Hey Arian, we need to talk", "Ceira", Game::Graphics::MessageEmotion::Content);
		MQueue.AddMessage("I hate how we've been drifting apart. Why won't you talk to me?", "Ceira", Game::Graphics::MessageEmotion::Sad);
		MQueue.AddMessage("1", "Ceira", Game::Graphics::MessageEmotion::Angry);
		MQueue.AddMessage("2", "Ceira", Game::Graphics::MessageEmotion::Annoyed);
		MQueue.AddMessage("3", "Ceira", Game::Graphics::MessageEmotion::Curious);
		MQueue.AddMessage("4", "Ceira", Game::Graphics::MessageEmotion::Happy);
		MQueue.AddMessage("5", "Ceira", Game::Graphics::MessageEmotion::Hurt);
		MQueue.AddMessage("6", "Ceira", Game::Graphics::MessageEmotion::Laugh);
		MQueue.AddMessage("7", "Ceira", Game::Graphics::MessageEmotion::Scared);
		MQueue.AddMessage("7", "Ceira", Game::Graphics::MessageEmotion::Unsure);
		Game::Graphics::GameRocket::BasicRMLScreen overlay("Overlay", "TopOverlay.rml", GameEngine, GameEngine.GetUID());
		Game::Graphics::MessageQueueVisualizer Vis(&MQueue, &GameEngine, &overlay);
		//(boost::bind(&Graphics::Screens::ScreenManager::HandleKeyPressed, &ScreenManager, _1, _2, _3)
		GameEngine.GetInput().AddKeyPressedEvent(boost::bind(&Game::Graphics::MessageQueueVisualizer::HandleKeyPressed, &Vis, _1, _2, _3));
		GameEngine.GetInput().AddKeyReleasedEvent(boost::bind(&Game::Graphics::MessageQueueVisualizer::HandleKeyReleased, &Vis, _1, _2, _3));

		auto animSprite = GameEngine.GetContentManager().RequestAnimatedSprite("Ceira_Main", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Guardian, GameEngine.GetTime());
		animSprite->GetAnimator()->PlayAnimation("CastMagic", GameEngine.GetTime(), true);
		animSprite->setPosition(200, 200);
		//animSprite->PlayAni
		//::Graphics::Animator Anim;
		//auto texture = GameEngine.GetContentManager().RequestTexture("Ceira_Main", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Guardian, GameEngine.GetTime());
		//SetUpAnimationTest(Anim, GameEngine, texture);
		//Anim.PlayAnimation("Idle", GameEngine.GetTime(), true);
		//::Graphics::FrameAnimation Fanim;
		//sf::Sprite sprite(*texture);
		//sprite.
		
		sf::Text TextTest;
		TextTest.setString("Test");
		TextTest.setColor(sf::Color::Black);

		sf::Uint32 time = GameEngine.GetTime();
		std::cout << "First Time: " << time << std::endl;
		for(bool Running = true; Running; time = GameEngine.GetTime())
		{
			
			GameEngine.HandleWindowEvents(GameWindow, Running);
			//screen.Update(GameEngine.GetTime());
			//TitleScr.Update(GameEngine.GetTime());
			GameEngine.Update(time);
			//Anim.Update(time);
			Vis.Update(time);
			overlay.Update(time);
			animSprite->Update(time);

			GameWindow.clear();
			Vis.Draw(GameWindow);
			//Anim.Animate(sprite);
			GameWindow.draw(TextTest);
			overlay.Draw(GameWindow);
			GameEngine.Draw(GameWindow);
			
			animSprite->Draw(GameWindow);
			//TitleScr.Draw(GameWindow);
			//screen.Draw(GameWindow);
			
			GameWindow.display();
			//auto rml = overlay.GetDocument()->GetInnerRML();
		}
		GameWindow.close();
		CommandThread.terminate();
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