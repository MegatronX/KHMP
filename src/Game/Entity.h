#pragma once
#ifndef _Entity_H_
#define _Entity_H_

#include <string>
#include <boost/functional.hpp>
#include <components/Component.h>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/thread/mutex.hpp>
namespace Game
{
	enum EntityTypes
	{
		ItemEntity = 1,
		CharacterEntity = 2,
		StatusEffectEntity = 4,
		AbilityEntity = 8,
		TileMapEntity = 16,
		ActionEntity = 32,
		PartyEntity = 64,
		BattlePartyEntity = 128,
		Battlefield = 256,
	};

	class Entity : public Cloneable<Entity> 
	{
	public:
		Entity();
		Entity(const std::string& name, const int type, const int ID = EntityIDCounter++);
		Entity(const Entity& entity);
		//Entity(const std::string& name, const std::string& type, const int ID = ++EntityIDCounter);
		int GetID() const;
		const std::string& GetName() const;
		std::string GetNameByVal() const;
		int GetNameHash() const;
		int GetType() const;
		bool IsType(int type);

		virtual Components::Component* GetComponent(const std::string& index);// const;
		template <typename T>
		T GetComponentAs(const std::string& name)// const
		{
			return dynamic_cast<T>(GetComponent(name));
		}
		bool HasComponent(const std::string& name); //const;
		bool RegisterComponent(const std::string& indexName, boost::shared_ptr<Components::Component> component, bool ReplaceExisting = true);
		bool RemoveComponent(const std::string& indexName);
		virtual RawClonePtr RawClone() const override;

		//Leave empty until use case arises
		bool DeleteComponent(const Components::Component* component);
		//Leave empty until use case arises
		bool DeleteComponent(const boost::shared_ptr<Components::Component>& component);

		void AddFlag(const std::string& flag);
		bool HasFlag(const std::string& flag);
		bool RemoveFlag(const std::string& flag);

		bool operator==(const Entity& entity) const;
		bool operator!=(const Entity& entity) const;
		Entity& operator=(const Entity& entity);
	protected:
		void AddType(int type);
		void RemoveType(int type);
		boost::unordered_map<std::string, boost::shared_ptr<Components::Component> > ComponentCollection;
		boost::unordered_set<std::string> FlagSet;

		static boost::hash<std::string> StringHasher;

	private:
		
		std::string Name;
		static int EntityIDCounter;
		int NameHash;
		int Type;
		int UID;
		boost::mutex mtx;
	};
	
}

#endif