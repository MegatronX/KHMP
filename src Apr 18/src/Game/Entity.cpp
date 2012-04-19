#include "Entity.h"
#include <boost/functional/hash.hpp>
namespace Game
{
	int Entity::EntityIDCounter = 0;
	boost::hash<std::string> Entity::StringHasher;
	Entity::Entity() : UID(-1), Type(0), Name("InvalidEntity")
	{

	}
	Entity::Entity(const std::string& name, const int type, const int ID) : UID(ID), Type(type), Name(name)
	{
		auto hasher = boost::hash<std::string>();
		NameHash = hasher(Name);
	}
	Entity::Entity(const Entity& entity)
	{
		this->Name = entity.Name;
		this->UID = EntityIDCounter++;
		this->Type = entity.Type;
		this->NameHash = entity.NameHash;
		ComponentCollection.rehash(entity.ComponentCollection.size());
		for (auto it = entity.ComponentCollection.begin(); it != entity.ComponentCollection.end(); ++it)
		{
			ComponentCollection[it->first] = it->second->Clone();
		}
	}
	int Entity::GetID() const
	{
		return UID;
	}
	const std::string& Entity::GetName() const
	{
		return Name;
	}
	std::string Entity::GetNameByVal() const
	{
		return Name;
	}
	int Entity::GetNameHash() const
	{
		return NameHash;
	}
	int Entity::GetType() const
	{
		return Type;
	}
	bool Entity::IsType(int type)
	{
		return (Type & type) > 0;
	}
	Components::Component* Entity::GetComponent(const std::string& index)// const
	{
		boost::mutex::scoped_lock l(mtx);
		auto it = ComponentCollection.find(index);
		if (it != ComponentCollection.end())
			return it->second.get();
		return nullptr;
	}
	bool Entity::HasComponent(const std::string& name) //const
	{
		return GetComponent(name) != nullptr;
	}
	bool Entity::RegisterComponent(const std::string& indexName, boost::shared_ptr<Components::Component> component, bool ReplaceExisting)
	{
		if (!ReplaceExisting && HasComponent(indexName) )
		{
			return false;
		}
		boost::mutex::scoped_lock l(mtx);
		ComponentCollection[indexName] = component;
		return true;
	}
	Entity::RawClonePtr Entity::RawClone() const
	{
		return new Entity(*this);
	}
	bool Entity::operator==(const Entity& entity) const
	{
		return this->UID == entity.UID;
	}
	bool Entity::operator!=(const Entity& entity) const
	{
		return !(*this == entity);
	}
	Entity& Entity::operator=(const Entity& ref)
	{
		if (this != &ref)
		{
			this->Name = ref.Name;
			this->NameHash = ref.NameHash;
			this->Type = ref.Type;
			this->UID = EntityIDCounter++;
			ComponentCollection.clear();
			ComponentCollection.rehash(ref.ComponentCollection.size());
			for (auto it = ref.ComponentCollection.begin(); it != ref.ComponentCollection.end(); ++it)
			{
				ComponentCollection[it->first] = it->second->Clone();
			}
		}
		return *this;
	}
	void Entity::AddType(int type)
	{
		Type |= type;
	}
	void Entity::RemoveType(int type)
	{
		if (IsType(type))
			Type = (Type & type) ^ type;
	}
}