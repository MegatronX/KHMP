#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <boost/unordered_map.hpp>
#include <Entity.h>

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>

#include <items/ItemDatabase.h>
namespace Game
{
	namespace Items
	{
		typedef boost::signals2::signal<void (const Entity*, int, int)> ItemAddedSignal;
		typedef boost::signals2::signal<void (const Entity*, int, int)> ItemRemovedSignal;

		class Inventory : public boost::noncopyable
		{
		public:
			bool AddItem(boost::shared_ptr<Entity>& item, const int count = 1);
			bool AddItem(Entity* item, const int count = 1);
			bool AddItem(Entity& item, const int count = 1);
			bool AddItem(int itemID, const int count = 1);
			bool AddItem(const std::string& itemname, const int count = 1);
		private:
			ItemAddedSignal ItemAddedEvents;
			ItemRemovedSignal ItemRemovedEvents;
			ItemDatabase* ItemDB;
		};
	}
}

#endif