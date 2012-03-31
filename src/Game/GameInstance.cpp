#include "GameInstance.h"
#include <Engine.h>
//#include <Scripting/ItemModule.h>
//#include <Scripting/GameScripting.h>
//#include <Scripting/ItemModule.h>
namespace Game
{
	void GameInstance::MakeGameInstance()
	{
		try
		{
			PrimaryEngine->GetPythonScripter().AddScriptObject<GameInstance>("GameInstance", *this, PrimaryEngine->GetPythonScripter().GetModule("GameInstanceModule"));
			GenerateItems();
			//Initalize others

			readySig();
		}
		catch (boost::python::error_already_set)
		{
			PyErr_Print();
		}
	}
	GameInstance::GameInstance(Engine& engine, bool ThreadStart) : PrimaryEngine(&engine), MakeThread(&GameInstance::MakeGameInstance, this)
	{
		if (ThreadStart)
		{
			MakeThread.Launch();
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

	Items::ItemDatabase& GameInstance::GetItemLibrary()
	{
		return itemDB;
	}

	boost::signals2::connection GameInstance::AddGameReadySignal(const GameReadySignal::slot_type& event)
	{
		return readySig.connect(event);
	}
}