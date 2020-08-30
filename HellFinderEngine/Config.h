#pragma once

#include <map>
#include <fstream>
#include <iterator>
#include <sstream>
#include <iostream>

class Config
{
private:
	typedef std::map<std::string, int>  mapT;
	std::map<std::string, int> config;
	std::pair<std::string, int> tmp;
	std::string defaultConfigFileName = "Config.cfg";

	void saveConfiguration(std::map<std::string, int> &);
	std::map<std::string, int> loadConfiguration();
	void createConfiguration();

public:
	int getParam(std::string key);
	void setParam(std::string key, int value);
	void addParam(std::string key, int value);
	void eraseParam(std::string key);
	std::map<std::string, int> getParamMap();
	void setParamMap(std::map<std::string, int> configMap);
	void save();
	void load();
	Config();
	Config(std::string configFileName);
};