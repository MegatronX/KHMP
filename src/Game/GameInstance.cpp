#include "GameInstance.h"
#include <Engine.h>
#include <statuseffects/StatusEffectsManager.h>
#include <items/Inventory.h>
//#include <Scripting/ItemModule.h>
//#include <Scripting/GameScripting.h>
//#include <Scripting/ItemModule.h>
namespace Game
{
	void GameInstance::MakeGameInstance()
	{
		try
		{
			PrimaryEngine->GetPythonScripter().AddScriptObject<GameInstance>("ActiveGame", *this, PrimaryEngine->GetPythonScripter().GetModule("GameInstanceModule"));
			GenerateItems();
			GenerateStatusEffects();
			GenerateActions();
			//Initalize others

			readySig();
		}
		catch (boost::python::error_already_set)
		{
			PyErr_Print();
		}
	}
	GameInstance::GameInstance(Engine& engine, bool ThreadStart) : PrimaryEngine(&engine), MakeThread(&GameInstance::MakeGameInstance, this), SelectedDifficulty("Standard")
	{
		if (ThreadStart)
		{
			MakeThread.launch();
		}
		else
		{
			MakeGameInstance();
		}
	}
	void GameInstance::ReloadItemLibrary()
	{
		itemDB.EmptyDatabase();
		PrimaryEngine->GetPythonScripter().RunFile(std::string("Items.py"));
	}
	void GameInstance::GenerateItems()
	{
		PrimaryEngine->GetPythonScripter().AddScriptObject<Items::ItemDatabase>("ItemLibrary", itemDB, PrimaryEngine->GetPythonScripter().GetModule("ItemModule"));
		PrimaryEngine->GetPythonScripter().RunFile(std::string("Items.py"));
	}
	void GameInstance::GenerateStatusEffects()
	{
		StatusEffects::StatusEffectsManager::SELibrary = &SELib;
		PrimaryEngine->GetPythonScripter().AddScriptObject<StatusEffects::StatusEffectsLibrary>("StatusEffectsLibrary", SELib, PrimaryEngine->GetPythonScripter().GetModule("StatusEffectsModule"));
		PrimaryEngine->GetPythonScripter().RunFile(std::string("StatusEffects.py"));
	}
	void GameInstance::ReloadStatusEffectsLibrary()
	{
		
	}

	void GameInstance::GenerateActions()
	{
		PrimaryEngine->GetPythonScripter().AddScriptObject<Actions::ActionsLibrary>("ActionLibrary", ActLib, PrimaryEngine->GetPythonScripter().GetModule("ActionModule"));
		PrimaryEngine->GetPythonScripter().RunFile(std::string("Actions.py"));
	}

	void GameInstance::ReloadActions()
	{

	}

	void GameInstance::MakeNewGame(const std::string& difficulty)
	{
		SelectedDifficulty = difficulty;
		PrimaryEngine->GetScreenManager().ClearStacks();
		PParty.RegisterComponent("Inventory Component", boost::shared_ptr<Items::InventoryComponent>(new Items::InventoryComponent()), true);
		PrimaryEngine->GetPythonScripter().RunFile("MakeNewGame.py");

	}
	void GameInstance::LoadSave(const std::string& savefile, const std::string& savename)
	{

	}
	Character::PlayerParty& GameInstance::GetPlayerParty()
	{
		return PParty;
	}
	/*GameState& GameInstance::GetPlayerGameState()
	{
		return PlayerState;
	}*/
	Items::ItemDatabase& GameInstance::GetItemLibrary()
	{
		return itemDB;
	}
	StatusEffects::StatusEffectsLibrary& GameInstance::GetSELibrary()
	{
		return SELib;
	}
	Actions::ActionsLibrary& GameInstance::GetActionLibrary()
	{
		return ActLib;
	}
	boost::signals2::connection GameInstance::AddGameReadySignal(const GameReadySignal::slot_type& event)
	{
		return readySig.connect(event);
	}
}