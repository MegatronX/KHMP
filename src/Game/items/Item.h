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

			Item(const std::string& itemName, const std::string& description, const unsigned int itemValue);

			int GetValue() const;
			const std::string& GetDescription() const;

			//virtual ClonePtr Clone() const override;
			virtual RawClonePtr RawClone() const override;
			virtual ~Item();

			Item& operator=(const Item& base);
		protected:
			int BaseMunnyValue;
			std::string Description;

			//Components::HealingComponent* ItemHealingComponent;
		private:
			
		};
	}
}

#endif