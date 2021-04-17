#pragma once
#include <map>
#include <string>

#include "Gui.h"

#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
    static std::map<std::string, sf::Image> images;
    /// <summary>
    /// default path "../res/img/" 
    /// </summary>
    /// <param name="key_name"></param>
    /// <param name="file_name"></param>
    /// <returns></returns>
    static sf::Image* loadImage(std::string key_name, std::string file_name);
    static sf::Image* getImage(std::string key_name);


    static std::map<std::string, sf::Font> fonts;
    /// <summary>
    /// default path "../res/fonts/" 
    /// </summary>
    /// <param name="key_name"></param>
    /// <param name="file_name"></param>
    /// <returns></returns>
    static sf::Font* loadFont(std::string key_name, std::string file_name);
    static sf::Font* loadFontFromOS(std::string key_name, std::string file_name);
    static sf::Font* getFont(std::string key_name);


    static std::map<std::string, GuiStyle> styles;
    /// <summary>
    /// 
    /// </summary>
    /// <param name="key_name"></param>
    /// <param name="file_name"></param>
    /// <returns></returns>
    static GuiStyle* loadGuiStyle(std::string key_name, GuiStyle style);
    static GuiStyle* getGuiStyle(std::string key_name);

    static std::map<std::string, sf::Texture> textures;

    static sf::Texture* loadTexture(std::string key_name, std::string file_name);
    static sf::Texture* getTexture(std::string key_name);

    static void cleanup();

private:
    ResourceManager() {}
};

