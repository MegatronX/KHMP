#pragma once
#ifndef _GAMEINSTANCE_H_
#define _GAMEINSTANCE_H_
#include <items/ItemDatabase.h>
#include <boost/signals2.hpp>
#include <boost/noncopyable.hpp>
#include <sfml/System.hpp>
class Engine;
namespace Game
{
	typedef boost::signals2::signal<void()> GameReadySignal;
	class GameInstance : boost::noncopyable
	{
	public:

		GameInstance(Engine& engine, bool ThreadStart = true);
		Items::ItemDatabase& GetItemLibrary();
		boost::signals2::connection AddGameReadySignal(const GameReadySignal::slot_type& event);
	protected:
		void MakeGameInstance();
		void GenerateItems();
		void ReloadItemLibrary();
	private:
		Items::ItemDatabase itemDB;
		Engine* PrimaryEngine;
		GameReadySignal readySig;
		sf::Thread MakeThread;
	};
}

#endif