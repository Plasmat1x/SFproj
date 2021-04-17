#include "Scene1.h"

#include <iostream>

#include "ResourceManager.h"

SceneOne::SceneOne(Engine* engine)
{
    init(engine);
}

void SceneOne::init(Engine* engine)
{
    //core setup
    this->engine = engine;
    this->event = &engine->events;
    this->view = &engine->view;

    //view setup
    sf::Vector2f pos = sf::Vector2f(this->engine->window.getSize());
    this->view->setSize(pos);
    pos *= 0.5f;
    this->view->setCenter(pos);
   
    ResourceManager::loadFont("exotic_font", "MorrisRomanBlackAlt.ttf");
    ResourceManager::loadFontFromOS("mono_font", "CONSOLA");
    ResourceManager::loadFontFromOS("sans_font", "TIMES");
    ResourceManager::loadFontFromOS("serif_font", "ARIAL");

    ResourceManager::loadTexture("meta_button", "button_meta.png");

    ResourceManager::loadGuiStyle("button", GuiStyle(
        ResourceManager::getFont("serif_font"),
        1,
        sf::Color(0xff, 0xff, 0xff, 0xff), sf::Color(0x00, 0x00, 0x00, 0xff), sf::Color(0x00, 0x00, 0x00, 0xff),
        sf::Color(0x00, 0x00, 0x00, 0xff), sf::Color(0xff, 0xff, 0xff, 0xff), sf::Color(0xff, 0xff, 0xff, 0xff)));
    
    ResourceManager::loadGuiStyle("text", GuiStyle(
        ResourceManager::getFont("sans_font"),
        0,
        sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00, 0xff), sf::Color(0xff, 0xff, 0xff, 0xff),
        sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00, 0xff), sf::Color(0xff, 0xff, 0xff, 0xff)));
    
    ResourceManager::loadGuiStyle("header", GuiStyle(
        ResourceManager::getFont("exotic_font"),
        0,
        sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00, 0xff), sf::Color(0xff, 0xff, 0xff, 0xff),
        sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00, 0xff), sf::Color(0xff, 0xff, 0xff, 0xff)));

    ResourceManager::loadGuiStyle("button_textured", GuiStyle(
        ResourceManager::getFont("mono_font"),
        1,
        sf::Color(0xff, 0xff, 0xff, 0xff), sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0xff, 0xff, 0xff, 0xff),
        sf::Color(0xff, 0xff, 0xff, 0xff), sf::Color(0xff, 0xff, 0xff, 0x00), sf::Color(0x00, 0x00, 0x00, 0xff)));

    //gui setup
    this->guiSys.emplace("menu", Gui(
        sf::Vector2f(128, 37), 14,
        1, 5, false, true, *ResourceManager::getGuiStyle("button_textured"),
        { std::make_pair("New game", "game_state"),
        std::make_pair("Options", "options_state"),
        std::make_pair("Exit","exit_state")}));
    //this->guiSys.at("menu").setPosition(pos.x, pos.y * 1.2f);
    this->guiSys.at("menu").setPosition(view->getCenter().x, view->getCenter().y * 1.5f);
    //this->guiSys.at("menu").setOrigin(192 * 0.5f, 37 * 0.5f);
    this->guiSys.at("menu").setOrigin(this->guiSys.at("menu").getSize() * 0.5f);
    this->guiSys.at("menu")._setMTO(MultiTileObject(ResourceManager::getTexture("meta_button"),
        sf::Vector2i(4, 8),
        sf::Vector2i(3, 3)));
    this->guiSys.at("menu").show();

    this->guiSys.emplace("text", Gui(
        sf::Vector2f(192 * 3, 32 * 3), 100,
        1, 5, false, true, *ResourceManager::getGuiStyle("header"),
        { std::make_pair("Main menu", "text") }));
    //this->guiSys.at("text").setPosition(pos.x, pos.y * 0.5f + 80);
    this->guiSys.at("text").setPosition(view->getCenter().x, view->getCenter().y * 0.5f + 80);
    this->guiSys.at("text").setOrigin(192 * 3 * 0.5f, 32 * 3 * 0.5f);
    this->guiSys.at("text").show();

    tex.loadFromFile("../res/img/t1.png");
    tex_ico.loadFromFile("../res/img/icon.png");
    tex_button.loadFromFile("../res/img/button.png", sf::IntRect(40, 0, 37, 37));
    tex_button.setRepeated(true);
    tex.setRepeated(true);

    sprite.setTexture(tex);
    sprite.setTextureRect(sf::IntRect(0, 0, 200, 32));
    sprite.setPosition(0, 64);
    sprite.setScale(4, 4);

    ico.setTexture(tex_ico);
    ico.setOrigin(16,16);
    ico.setPosition(400, 128);
    ico.setScale(4, 4);

    this->guiSys.at("menu")._setTexture(&tex_button);
}

void SceneOne::processInput()
{
    sf::Vector2f mousePos = this->engine->window.mapPixelToCoords(
        sf::Mouse::getPosition(this->engine->window), *this->view);
    while (this->engine->window.pollEvent(*event))
    {
        switch (event->type)
        {
        case sf::Event::Closed:
        {
            engine->window.close();
            break;
        }
        case sf::Event::Resized:
        {
            this->view->setSize(event->size.width, event->size.height);
            sf::Vector2f pos = sf::Vector2f(event->size.width, event->size.height);
            pos *= 0.5f;
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), *this->view);
            this->guiSys.at("menu").setPosition(pos);
            break;
        }
        case sf::Event::KeyPressed:
        {
            if (event->key.code == sf::Keyboard::Escape)
            {
                this->engine->window.close();
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (event->mouseButton.button == sf::Mouse::Left)
            {
                for (auto const& [key, val] : guiSys)
                {
                    std::string msg = this->guiSys.at(key).activate(mousePos);

                    if (msg == "game_state")
                    {
                        std::cout << "next state start" << std::endl;
                    }

                    if (msg == "options_state")
                    {
                        std::cout << "next state options" << std::endl;
                    }

                    if (msg == "exit_state")
                    {
                        this->engine->window.close();
                    }
                }
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (event->mouseButton.button == sf::Mouse::Left)
            {

            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            for (auto const& [key, val] : guiSys)
            {
                this->guiSys.at(key).highlight(mousePos);
            }
            break;
        }
        default: break;
        }
    }
}

void SceneOne::update(const float dt)
{

}

void SceneOne::render(const float dt)
{
    this->engine->window.setView(*this->view);
    //this->engine->window.clear(sf::Color::Cyan);
    //render scene obj
    this->engine->window.draw(sprite);
    this->engine->window.draw(ico);
    //render gui
    for (auto gui : this->guiSys)
    {
        this->engine->window.draw(gui.second);
    }
    return;
}

void SceneOne::cleanup()
{

}
