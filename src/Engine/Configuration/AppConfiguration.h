#pragma once
#ifndef _APPCONFIGURATION_H_
#define _APPCONFIGURATION_H_
#include <string>
#include <boost\unordered_map.hpp>
#include <IO\xml\pugixml.hpp>
enum SettingHierarchy
{
	BasicSetting,
	InputSetting
};

namespace Configuration
{
	class AppConfiguration
	{
	public:
		AppConfiguration();
		AppConfiguration(const std::string &configFile);
		void Initialize(const std::string &configFile);

		//Get Settings
		const std::string GetApplicationSetting(const std::string &lookup);
		const std::string GetApplicationSetting(const char* lookup);
	protected:
		boost::unordered_map<std::string, std::string> ApplicationSettings;
		bool InputsSet;
	private:
		friend class InputModule;
	};
}
#endif