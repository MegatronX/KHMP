#include "PythonScripter.h"
#include "EngineModule.h"
#include "GraphicsModule.h"
#include "RocketModule.h"
#include "ScreenModule.h"
#include <scripting/GameScripting.h>
#include <Scripting/EntityModule.h>
#include <Scripting/ItemModule.h>
#include <Scripting/ComponentModule.h>
#include <Scripting/GameInstanceModule.h>
#include <Scripting/CharacterModule.h>
#include <Scripting/ActionModule.h>
#include <Scripting/BattleModule.h>
#include <scripting/GameScreensModule.h>
using namespace boost::python;
using namespace Game;
using namespace Game::Scripting;
namespace Scripting
{
	PythonScripter::PythonScripter(const std::string& scriptPath) : ScriptPath(scriptPath)
	{
		PyImport_AppendInittab("EngineModule", initEngineModule);
		PyImport_AppendInittab("ItemModule", initItemModule);
		PyImport_AppendInittab("EntityModule", initEntityModule);
		PyImport_AppendInittab("GameInstanceModule", initGameInstanceModule);
		PyImport_AppendInittab("ComponentModule", initComponentModule);
		PyImport_AppendInittab("CharacterModule", initCharacterModule);
		PyImport_AppendInittab("ActionModule", initActionModule);
		PyImport_AppendInittab("BattleModule", initBattleModule);
		PyImport_AppendInittab("RocketModule", initRocketModule);
		PyImport_AppendInittab("GraphicsModule", initGraphicsModule);
		PyImport_AppendInittab("ScreenModule", initScreenModule);
		PyImport_AppendInittab("GameScreensModule", initGameScreensModule);
		Py_Initialize();
		MainModule = object((handle<>(borrowed(PyImport_AddModule("__main__")))));
		MainNamespace = MainModule.attr("__dict__");

		EngineModule = object( (handle<>(PyImport_ImportModule("EngineModule"))) );
		MainNamespace["EngineModule"] = EngineModule;

		auto EntityModule = object((handle<>(PyImport_ImportModule("EntityModule"))) );
		MainNamespace["EntityModule"] = EntityModule;
		AdditionalModules["EntityModule"] = EntityModule;

		auto ItemModule = object((handle<>(PyImport_ImportModule("ItemModule"))) );
		MainNamespace["ItemModule"] = ItemModule;
		AdditionalModules["ItemModule"] = ItemModule;

		auto GameInstanceModule = object((handle<>(PyImport_ImportModule("GameInstanceModule"))) );
		MainNamespace["GameInstanceModule"] = GameInstanceModule;
		AdditionalModules["GameInstanceModule"] = GameInstanceModule;

		auto ComponentModule = object((handle<>(PyImport_ImportModule("ComponentModule"))));
		MainNamespace["ComponentModule"] = ComponentModule;
		AdditionalModules["ComponentModule"] = ComponentModule;

		auto CharacterModule = object((handle<>(PyImport_ImportModule("CharacterModule"))));
		MainNamespace["CharacterModule"] = CharacterModule;
		AdditionalModules["CharacterModule"] = CharacterModule;

		auto BattleModule = object((handle<>(PyImport_ImportModule("BattleModule"))));
		MainNamespace["BattleModule"] =  BattleModule;
		AdditionalModules["BattleModule"] =  BattleModule;

		auto ActionModule = object((handle<>(PyImport_ImportModule("ActionModule"))));
		MainNamespace["ActionModule"] = ActionModule;
		AdditionalModules["ActionModule"] = ActionModule;

		/*auto RocketModule = object((handle<>(PyImport_ImportModule("RocketModule"))));
		MainNamespace["RocketModule"] = ActionModule;
		AdditionalModules["RocketModule"] = ActionModule;*/

		auto _RocketModule = object((handle<>(PyImport_ImportModule("RocketModule"))));
		MainNamespace["RocketModule"] = _RocketModule;
		AdditionalModules["RocketModule"] = _RocketModule;

		auto GraphicsModule = object((handle<>(PyImport_ImportModule("GraphicsModule"))));
		MainNamespace["GraphicsModule"] = GraphicsModule;
		AdditionalModules["GraphicsModule"] = GraphicsModule;

		auto ScreenModule = object((handle<>(PyImport_ImportModule("ScreenModule"))));
		MainNamespace["ScreenModule"] = ScreenModule;
		AdditionalModules["ScreenModule"] = ScreenModule;

		auto GameScreensModule = object((handle<>(PyImport_ImportModule("GameScreensModule"))));
		MainNamespace["GameScreensModule"] = GameScreensModule;
		AdditionalModules["GameScreensModule"] = GameScreensModule;
	}
	void PythonScripter::RunString(const std::string &scriptString)
	{
		try
		{
			//boost::python::object res(PyRun_String( scriptString.c_str(), Py_file_input, MainNamespace.ptr(), MainNamespace.ptr()));
			//return res;
			handle<> ignored(( PyRun_String( scriptString.c_str(), Py_file_input, MainNamespace.ptr(), MainNamespace.ptr())));
		}
		catch ( error_already_set )
		{
			PyErr_Print();
		}
	}
	/*boost::python::object PythonScripter::RunString(const std::string &scriptString)
	{

		try
		{
			boost::python::object res(PyRun_String( scriptString.c_str(), Py_file_input, MainNamespace.ptr(), MainNamespace.ptr()));
			return res;
			//handle<> ignored(( PyRun_String( scriptString.c_str(), Py_file_input, MainNamespace.ptr(), MainNamespace.ptr())));
		}
		catch ( error_already_set )
		{
			PyErr_Print();
		}
		return boost::python::object();
	}*/
	boost::python::object PythonScripter::RunFile(const std::string &file, bool useStoredPath)
	{
		try
		{
			std::string targetFile(file);
			if (useStoredPath)
				targetFile = ScriptPath + file;
			if (boost::filesystem::exists(targetFile))
			{
				object result = exec_file(targetFile.c_str(), MainNamespace, MainNamespace);

				return result;
			}
			else
			{
				std::cout << "File Does Not Exist: " << targetFile << " | Script Path: " << ScriptPath << std::endl;
				std::cout.flush();
			}
		}
		catch ( error_already_set )
		{
			PyErr_Print();
		}
		return boost::python::object();
	}
	boost::python::object& PythonScripter::GetMainModule()
	{
		return MainModule;
	}
	boost::python::object& PythonScripter::GetSFMLModule()
	{
		return SFMLModule;
	}
	boost::python::object& PythonScripter::GetEngineModule()
	{
		return EngineModule;
	}
	boost::python::object& PythonScripter::GetLibRocketModule()
	{
		return LibRocketModule;
	}
	boost::python::object& PythonScripter::GetRocketModule()
	{
		return RocketModule;
	}
	boost::python::object& PythonScripter::GetGraphicsModule()
	{
		return GraphicsModule;
	}
	boost::python::object& PythonScripter::GetModule(const std::string& name)
	{
		auto it = AdditionalModules.find(name);
		if (it != AdditionalModules.end())
		{
			return it->second;
		}
		return object();
	}
	void PythonScripter::AddModule(const std::string& name, boost::python::object& module)
	{

	}
	void PythonScripter::SetPath(const std::string &val)
	{
		ScriptPath = val;
	}

	PythonScripter::~PythonScripter()
	{
		Py_Finalize();
	}
}