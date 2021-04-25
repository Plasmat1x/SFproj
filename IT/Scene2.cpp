#include <iostream>
#include "ResourceManager.h"
#include "Scene2.h"


SceneTwo::SceneTwo(Engine* engine)
{
    init(engine);
}

void SceneTwo::init(Engine* engine)
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

    //gui setup
    this->guiSys.emplace("menu", Gui(
        sf::Vector2f(128, 32), 14,
        1, 5, true, true, *ResourceManager::getGuiStyle("button_mto"),
        { std::make_pair("Save", "save_state"),
        std::make_pair("Back","back_state") },
        true,
        MultiTileObject(ResourceManager::getTexture("meta_button"),
           sf::Vector2i(8,8), sf::Vector2i(3,3), 1)));
    this->guiSys.at("menu").setPosition(pos.x, pos.y * 1.5f);
    this->guiSys.at("menu").setOrigin(this->guiSys.at("menu").gui_size.x * 0.5f, 
                                        this->guiSys.at("menu").gui_size.y * 0.5f);
    this->guiSys.at("menu").show();

    this->guiSys.emplace("text", Gui(
        sf::Vector2f(192 * 3, 32 * 3), 100,
        1, 5, false, true, *ResourceManager::getGuiStyle("header"),
        { std::make_pair("Options", "text") }));
    this->guiSys.at("text").setPosition(pos.x, pos.y * 0.5f);
    this->guiSys.at("text").setOrigin(192 * 3 * 0.5f, 32 * 3 * 0.5f);
    this->guiSys.at("text").show();

    mto = MultiTileObject(
        ResourceManager::getTexture("meta_window"),
        sf::Vector2f(pos.x,pos.y),
        sf::Vector2f(1.0f, 1.0f),
        sf::Vector2f(80.0f, 60.0f),
        sf::Vector2i(8, 8),
        sf::Vector2i(3, 3),
        1);
   
    mto.setSize(sf::Vector2f(800, 600));
    mto.setOrigin(sf::Vector2f(mto.getGloablBounds().width * 0.5f, mto.getGloablBounds().height * 0.5f));
    
}

void SceneTwo::processInput()
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
            this->view->setCenter(pos);
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), *this->view);
            //this->guiSys.at("menu").setPosition(sf::Vector2f(pos.x, pos.y));
            //this->guiSys.at("menu").show();
            //this->guiSys.at("text").setPosition(sf::Vector2f(pos.x, this->guiSys.at("menu").getPosition().y));
            //this->guiSys.at("text").show();
            //this->mto.setPosition(pos);
            break;
        }
        case sf::Event::KeyPressed:
        {
            if (event->key.code == sf::Keyboard::Escape)
            {
                this->engine->_pop();
                return;
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

                    if (msg == "save_state")
                    {
                        this->engine->_pop();
                        return;
                    }
                    if (msg == "back_state")
                    {
                        this->engine->_pop();
                        return;
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

        case sf::Event::MouseMoved:
        {
            std::cout << "x = " << (int)mousePos.x << " | y = " << (int)mousePos.y << "    \r";

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
}

void SceneTwo::update(const float dt)
{

}

void SceneTwo::render(const float dt)
{
    this->engine->window.setView(*this->view);
    //this->engine->window.clear(sf::Color::Cyan);
    //render scene obj
    this->engine->window.draw(mto);
    //render gui
    for (auto gui : this->guiSys)
    {
        this->engine->window.draw(gui.second);
    }
    return;
}

void SceneTwo::cleanup()
{
}

