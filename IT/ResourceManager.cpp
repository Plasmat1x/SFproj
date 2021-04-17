#include "ResourceManager.h"

std::map<std::string, sf::Image> ResourceManager::images;
std::map<std::string, sf::Font>  ResourceManager::fonts;
std::map<std::string, GuiStyle> ResourceManager::styles;
std::map<std::string, sf::Texture> ResourceManager::textures;

sf::Image* ResourceManager::loadImage(std::string key_name, std::string file_name)
{
    sf::Image image;
    std::string path = "../res/img/";
    
    image.loadFromFile(path + file_name);
    
    images[key_name] = image;
    return &images[key_name];
}

sf::Image* ResourceManager::getImage(std::string key_name)
{
    return &images[key_name];
}

sf::Font* ResourceManager::loadFont(std::string key_name, std::string file_name)
{
    sf::Font font;
    std::string path = "../res/fonts/";

    font.loadFromFile(path + file_name);

    fonts[key_name] = font;
    return &fonts[key_name];
}

sf::Font* ResourceManager::loadFontFromOS(std::string key_name, std::string file_name)
{
    sf::Font font;
    std::string path = "C:/windows/fonts/";
    font.loadFromFile(path + file_name + ".ttf");
    fonts[key_name] = font;
    return &fonts[key_name];
}

sf::Font* ResourceManager::getFont(std::string key_name)
{
    return &fonts[key_name];
}

GuiStyle* ResourceManager::loadGuiStyle(std::string key_name, GuiStyle style)
{
    styles[key_name] = style;
    return &styles[key_name];
}

GuiStyle* ResourceManager::getGuiStyle(std::string key_name)
{
    return &styles[key_name];
}

sf::Texture* ResourceManager::loadTexture(std::string key_name, std::string file_name)
{
    sf::Texture tex;
    std::string path = "../res/img/";

    tex.loadFromFile(path + file_name);
    textures[key_name] = tex;

    return &textures[key_name];
}

sf::Texture* ResourceManager::getTexture(std::string key_name)
{
    return &textures[key_name];
}

void ResourceManager::cleanup()
{
}
