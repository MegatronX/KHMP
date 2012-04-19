#pragma once
#ifndef _STATUSEFFECTSMODULE_H_
#define _STATUSEFFECTSMODULE_H_
#include <boost/python.hpp>
#include <statuseffects/StatusEffect.h>
#include <scripting/Python/ScriptHelpers.h>
#include <components/ApplyEffectComponent.h>
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		class StatusEffectWrap : public StatusEffects::StatusEffect
		{
		public:
			StatusEffectWrap(PyObject* self_, Character::BaseCharacter* holder, const std::string& name, bool pos, const int priority, const int ticks) : self(self_),
				StatusEffect(holder, name, pos, priority, ticks)
			{

			}
			StatusEffectWrap(PyObject* self, const StatusEffects::StatusEffect& ref) : self(self), StatusEffect(ref)
			{

			}
			StatusEffects::StatusEffect::ClonePtr Clone() const override
			{
				return call_method<StatusEffects::StatusEffect::ClonePtr>(self, "Clone");
			}
			StatusEffects::StatusEffect::ClonePtr CloneDefault() const
			{
				return this->StatusEffects::StatusEffect::Clone();
			}
			PyObject* self;
		};

		class ApplyEffectWrap : public Components::ApplyEffectComponent
		{
		public:
			ApplyEffectWrap(PyObject* self, Entity* owner) : self(self), Components::ApplyEffectComponent(owner)
			{

			}
			ApplyEffectWrap(PyObject* self, const Components::ApplyEffectComponent& eff) : self(self), Components::ApplyEffectComponent(eff)
			{

			}
			virtual void Apply(Character::BaseCharacter* character) override
			{
				call_method<void>(self, "Apply", ptr(character));
			}
			virtual void ApplyDefault(Character::BaseCharacter* character)
			{
				this->Components::ApplyEffectComponent::Apply(character);
			}
			virtual void UnApply(Character::BaseCharacter* character) override
			{
				call_method<void>(self, "UnApply", ptr(character));
			}
			virtual void UnApplyDefault(Character::BaseCharacter* character)
			{
				this->Components::ApplyEffectComponent::UnApply(character);
			}
			Components::ApplyEffectComponent::ClonePtr Clone() const override
			{
				return call_method<Components::ApplyEffectComponent::ClonePtr>(self, "Clone");
			}
			Components::ApplyEffectComponent::ClonePtr CloneDefault() const
			{
				return this->Components::ApplyEffectComponent::Clone();
			}
			PyObject* self;
		};


		BOOST_PYTHON_MODULE(StatusEffectsModule)
		{
			class_<StatusEffects::StatusEffect, bases<Entity> >("StatusEffect", init<Character::BaseCharacter*, const std::string&, boost::python::optional<bool, const int, const int> >())
				.def(init<const StatusEffects::StatusEffect&>())
				.def("SetHolder", &StatusEffects::StatusEffect::SetHolder)
				.def("Clone", &StatusEffects::StatusEffect::Clone, &StatusEffectWrap::CloneDefault)
				.def("__eq__", &StatusEffects::StatusEffect::operator==)
				.def("__neq__", &StatusEffects::StatusEffect::operator!=)
				.def("__copy__", &generic__copy__<StatusEffectWrap>)
				.def("__deepcopy__", &generic__deepcopy__<StatusEffectWrap>)
				;

			class_<StatusEffects::StatusEffectsLibrary, noncopyable>("StatusEffectsLibrary", no_init)

				.def("AddStatusEffect", &StatusEffects::StatusEffectsLibrary::AddStatusEffect)
				;

			class_<Components::ApplyEffectComponent, boost::shared_ptr<ApplyEffectWrap>, bases<Components::Component> >("ApplyEffectComponent", init<Entity*>())
				.def(init<const Components::ApplyEffectComponent&>())
				.def("Apply", &Components::ApplyEffectComponent::Apply, &ApplyEffectWrap::ApplyDefault)
				.def("UnApply", &Components::ApplyEffectComponent::UnApply, &ApplyEffectWrap::UnApplyDefault)
				.def("Clone", &ApplyEffectWrap::Clone)//, &ApplyEffectWrap::CloneDefault)
				.def("__copy__", &generic__copy__<ApplyEffectWrap>)
				.def("__deepcopy__", &generic__deepcopy__<ApplyEffectWrap>)
				;
		}
	}
}
#endif