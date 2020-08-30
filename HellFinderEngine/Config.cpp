#include "Config.h"



void Config::saveConfiguration(std::map<std::string, int> &config)
{
	std::ofstream configFile("./res/" + defaultConfigFileName, std::ios_base::in | std::ios_base::trunc);
	//configFile << config.size() << std::endl;
	for (std::map<std::string, int>::iterator iter = config.begin(); iter != config.end(); iter++)
		configFile << iter->first.c_str() << "=" << iter->second << std::endl;
}

std::map<std::string, int> Config::loadConfiguration()
{
	//std::map<std::string, int> config;
	std::ifstream configFile("./res/" + defaultConfigFileName);
	if (!configFile.is_open())
	{
		createConfiguration();
		configFile.open(defaultConfigFileName);
	}
	int size = 0, pointer = 0, second = 0;
	char *buf = new char[50];
	char delimer = '=';
	std::string strBuf = "", tmp = "", first = "";
	while (!configFile.eof())
	{
		configFile.getline(buf, 50);
		strBuf = buf;
		if (strBuf.size() == 0)
			break;
		auto delimerPosition = std::find(strBuf.begin(), strBuf.end(), delimer);
		tmp.resize(delimerPosition - strBuf.begin(), ' ');
		std::copy(strBuf.begin(), delimerPosition, tmp.begin());
		first = tmp;
		tmp.resize(strBuf.end() - delimerPosition - 1, ' ');
		std::copy(delimerPosition + 1, strBuf.end(), tmp.begin());
		std::stringstream ss(tmp);
		ss >> second;
		config.insert(std::pair<std::string, int>(first, second));
	}
	return config;
}

void Config::createConfiguration()
{
	std::map<std::string, int> defaultConfig;
	defaultConfig.insert(std::pair<std::string, int>("iWindowWidth", 1600));
	defaultConfig.insert(std::pair<std::string, int>("iWindowHeight", 900));
	defaultConfig.insert(std::pair<std::string, int>("iFrameLimit", 60));
	defaultConfig.insert(std::pair<std::string, int>("fGameSpeed", 300));
	defaultConfig.insert(std::pair<std::string, int>("fGameTick", 40));
	defaultConfig.insert(std::pair<std::string, int>("EMPTY", 0));
	saveConfiguration(defaultConfig);
}

int Config::getParam(std::string key)
{
	mapT::iterator it = config.find(key);
	if (it != config.end())
		return it->second;
	return 0;
}

void Config::setParam(std::string key, int value)
{
	mapT::iterator it = config.find(key);
	if (it != config.end())
		it->second = value;
}

void Config::addParam(std::string key, int value)
{
	config.insert(std::pair<std::string, int>(key, value));
}

void Config::eraseParam(std::string key)
{
	config.erase(key);
}

std::map<std::string, int> Config::getParamMap()
{
	return config;
}

void Config::setParamMap(std::map<std::string, int> configMap)
{
	config = configMap;
}

void Config::save()
{
	saveConfiguration(config);
}

void Config::load()
{
	config = loadConfiguration();
}

Config::Config()
{
	config = loadConfiguration();
}

Config::Config(std::string configFileName)
{
	defaultConfigFileName = configFileName;
	config = loadConfiguration();
}
