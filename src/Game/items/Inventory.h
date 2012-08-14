#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <boost/unordered_map.hpp>


#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>

#include <items/ItemDatabase.h>
#include <items/Item.h>
namespace Game
{
	namespace Items
	{
		typedef boost::signals2::signal<void (const Item*, int, int)> ItemAddedSignal;
		typedef boost::signals2::signal<void (const Item*, int, int)> ItemRemovedSignal;

		class InventoryComponent : public Components::Component
		{
		public:
			bool AddItem(boost::shared_ptr<Entity>& item, const int count = 1);
			bool AddItem(Item* item, const int count = 1);
			bool AddItem(Item& item, const int count = 1);
			bool AddItem(int itemID, const int count = 1);
			bool AddItem(const std::string& itemname, const int count = 1);

			
		private:
			boost::unordered_map<std::string, int> ItemCount;
			ItemAddedSignal ItemAddedEvents;
			ItemRemovedSignal ItemRemovedEvents;
			ItemDatabase* ItemDB;
		};
	}
}

#endif