#pragma once
#include <actions/Action.h>
#include <actions/ActiveAction.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <scripting/Python/ScriptHelpers.h>
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		struct ActionWrap : public Actions::Action
		{
			ActionWrap(PyObject* self_) : self(self_)
			{

			}
			ActionWrap(PyObject* self_, const std::string& name) : self(self_), Actions::Action(name)
			{

			}
			ActionWrap(PyObject* self_, const Actions::Action& action) : self(self_), Actions::Action(action)
			{

			}
			ClonePtr Clone() const override
			{
				return call_method<ClonePtr>(self, "Clone");
			}
			ClonePtr CloneDefault() const
			{
				return this->Actions::Action::Clone();
			}
			PyObject* self;
		};
		BOOST_PYTHON_MODULE(ActionModule)
		{
			class_<std::vector<Actions::ActiveAction> >("ActiveActionList")
				.def(vector_indexing_suite<std::vector<Actions::ActiveAction> >())
				;

			class_<Actions::Action, boost::shared_ptr<ActionWrap>, bases<Entity> >("Action")
				.def(init<>())
				.def(init<const std::string&>())
				.def(init<const Actions::Action&>())
				.def_readwrite("Users", &Actions::Action::Users)
				.def_readwrite("Targets", &Actions::Action::Targets)
				.def("Clone", &Actions::Action::Clone, &ActionWrap::CloneDefault)
				.def("__copy__", &generic__copy__< ActionWrap >)
				.def("__deepcopy__", &generic__deepcopy__< ActionWrap >)
				;

			class_<Actions::ActiveAction>("ActiveAction")
				.add_property("AttachedCharacter", 
							make_getter(&Actions::ActiveAction::AttachedCharacter, return_value_policy<reference_existing_object>()),
							make_setter(&Actions::ActiveAction::AttachedCharacter, return_value_policy<reference_existing_object>()))
				.def_readwrite("Action", &Actions::ActiveAction::action)
				
				;
		}
	}
}