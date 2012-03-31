#pragma once
#include <components/Component.h>
#include <components/UseComponent.h>
#include <battle/BattleField.h>
#include <battle/BattleCharacter.h>
#include <character/BaseCharacter.h>
#include <boost/python.hpp>
#include <Entity.h>
#include <vector>
#include <memory>
#include <scripting/Python/ScriptHelpers.h>
#include <Scripting/UseComponentWrap.h>
using namespace boost;
using namespace boost::python;

namespace Game
{
	namespace Scripting
	{
		template<class T>
		void CloneWrapper(PyObject* self)
		{
			//boost::shared_ptr<T> 
		}

		class ComponentWrap : public Components::Component
		{
		public:
			ComponentWrap(PyObject* self_) : self(self_), Components::Component()
			{

			}
			ComponentWrap(PyObject* self_, Entity* owner, bool valid) : self(self_), Components::Component(owner, valid)
			{

			}
			ComponentWrap(PyObject* self_, Entity* owner, const std::string& name, int type, bool valid = true) : self(self_), Components::Component(owner, name, type, valid)
			{

			}
			ComponentWrap(PyObject* self_, Entity* owner, const std::string& name, const std::string& type, bool valid = true ) : self(self_), Components::Component(owner, name, type, valid)
			{

			}
			ComponentWrap(PyObject* self_, const Components::Component& comp) : self(self_), Component(comp)
			{

			}
			Components::Component::ClonePtr Clone() const override
			{
				return call_method<Components::Component::ClonePtr>(self, "Clone");
			}
			Components::Component::ClonePtr CloneDefault() const
			{
				return this->Components::Component::Clone();
			}
			PyObject* self;
		};
		/*
		Component();
		Component(bool valid, const int id = ++ComponentIDCounter);
		Component(const std::string& name, int type, bool valid = true, const int id = ++ComponentIDCounter);
		Component(const std::string& name, const std::string& type, bool valid = true, const int id = ++ComponentIDCounter);



		*/
		BOOST_PYTHON_MODULE(ComponentModule)
		{
			class_<std::vector<Battle::BattleCharacter*> >("BattleCharacterVector")
				.def(vector_ptr_indexing_suite<std::vector<Battle::BattleCharacter*> >())
				;

			class_<std::vector<Character::BaseCharacter*> >("BaseCharacterVector")
				.def(vector_ptr_indexing_suite<std::vector<Character::BaseCharacter*> >())
				;

			bool (Components::Component::*IsType1)(const std::string&) = &Components::Component::IsType;
			bool (Components::Component::*IsType2)(int) = &Components::Component::IsType;

			class_<Components::Component, boost::shared_ptr<ComponentWrap> >("Component")
				.def(init<>())
				.def(init<const Components::Component&>())
				.def(init<Entity*, bool>())
				.def(init<Entity*, const std::string&, int, boost::python::optional<bool>  >())
				.def(init<Entity*, const std::string&, const std::string&, boost::python::optional<bool> >())
				.def("GetComponentType", &Components::Component::GetComponentType)
				.def("GetName", &Components::Component::GetNameByVal)
				.def("GetNameHash", &Components::Component::GetNameHash)
				.def("GetUID", &Components::Component::GetUID)
				.def("IsType", IsType1)
				.def("IsType", IsType2)
				.def("IsValid", &Components::Component::IsValid)
				.def("SetValid", &Components::Component::SetValid)
				//.def("SmartClone", &Components::Component::SmartClone)
				.def("Clone", &Components::Component::Clone, &ComponentWrap::Clone)
				.def("__eq__", &Components::Component::operator==)
				.def("__neq__", &Components::Component::operator!=)
				.def("__copy__", &generic__copy__<ComponentWrap>)
				.def("__deepcopy__", &generic__deepcopy__<ComponentWrap>)
				;

			class_<Components::UseComponent, boost::shared_ptr<UseComponentWrap>, bases<Components::Component> >("UseComponent")
				.def(init<>())
				.def(init<const std::string&,bool, bool>())
				.def(init<const Components::UseComponent&>())
				.def("BattleUse", &Components::UseComponent::BattleUse, &UseComponentWrap::BattleUseDefault)
				.def("Use", &Components::UseComponent::Use, &UseComponentWrap::UseDefault)
				.def("HasUse", &Components::UseComponent::HasUse)
				//.def("HasBattleUse", &Components::UseComponent::HasBattleUse)
				.def("Clone", &Components::UseComponent::Clone, &UseComponentWrap::Clone)
				.def("__copy__", &generic__copy__<UseComponentWrap>)
				.def("__deepcopy__", &generic__deepcopy__<UseComponentWrap>)
				;
/*
Component(bool valid = false);
Component(bool valid = false, const int id = ++ComponentIDCounter);
Component(const std::string& name, int type, bool valid = true, const int id = ++ComponentIDCounter);
Component(const std::string& name, const std::string& type, bool valid = true, const int id = ++ComponentIDCounter);
*/
		}
	}
}