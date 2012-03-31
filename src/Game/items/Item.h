#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_
#include <Entity.h>
#include <components/UseComponent.h>
#include <boost/unordered_map.hpp>
#include <Utilities/Cloneable.h>
namespace Game
{
	namespace Items
	{
		class Item : public Entity
		{
		public:
			Item();
			Item(const Item& ref);
			Item(const std::string& itemName);

			//virtual ClonePtr Clone() const override;
			virtual RawClonePtr RawClone() const override;
			virtual ~Item();

			Item& operator=(const Item& base);
		protected:
			//Components::HealingComponent* ItemHealingComponent;
		private:
			
		};
	}
}

#endif