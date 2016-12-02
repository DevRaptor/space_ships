#pragma once

#include <map>
#include <string>

class ResourceManager
{
public:
	ResourceManager()
	{
		LoadParameters();
	}
	~ResourceManager() { }

	bool GetBoolParameter(const std::string& name);
	int GetIntParameter(const std::string& name);
	float GetFloatParameter(const std::string& name);
	std::string GetStringParameter(const std::string& name);

private:
	std::map<std::string, std::string> parameters;

	void LoadParameters();
};
