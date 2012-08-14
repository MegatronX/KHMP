#pragma once
#ifndef _GAMEINSTANCE_H_
#define _GAMEINSTANCE_H_
#include <items/ItemDatabase.h>
#include <statuseffects/StatusEffectsLibrary.h>
#include <actions/ActionLibrary.h>
#include <boost/signals2.hpp>
#include <boost/noncopyable.hpp>
#include <sfml/System.hpp>
#include <character/PlayerParty.h>
#include <gamestate/GameState.h>
class Engine;
namespace Game
{
	typedef boost::signals2::signal<void()> GameReadySignal;
	class GameInstance : boost::noncopyable
	{
	public:

		GameInstance(Engine& engine, bool ThreadStart = true);
		Items::ItemDatabase& GetItemLibrary();
		StatusEffects::StatusEffectsLibrary& GetSELibrary();
		Actions::ActionsLibrary& GetActionLibrary();
		boost::signals2::connection AddGameReadySignal(const GameReadySignal::slot_type& event);

		void MakeNewGame(const std::string& difficulty = "Standard");
		void LoadSave(const std::string& savefile, const std::string& savename);
		Character::PlayerParty& GetPlayerParty();
		//GameState& GetPlayerGameState();
	protected:
		void MakeGameInstance();
		void GenerateItems();
		void ReloadItemLibrary();

		void GenerateStatusEffects();
		void ReloadStatusEffectsLibrary();

		void GenerateActions();
		void ReloadActions();
	private:
		Items::ItemDatabase itemDB;
		StatusEffects::StatusEffectsLibrary SELib;
		Actions::ActionsLibrary ActLib;
		Character::PlayerParty PParty;
		Engine* PrimaryEngine;
		GameReadySignal readySig;
		sf::Thread MakeThread;
		//CurrentGameState PlayerState;
		std::string SelectedDifficulty;
	};
}

#endif