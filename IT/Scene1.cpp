#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"

#include "dGrid.h"

#include <iostream>

#include "ResourceManager.h"

/*
        std::cout << std::endl <<
            entry.mto.getGloablBounds().left << " " <<
            entry.mto.getGloablBounds().top << " " <<
            entry.mto.getGloablBounds().width << " " <<
            entry.mto.getGloablBounds().height << " " << std::endl;
            
*/

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
    ResourceManager::loadTexture("meta_window", "meta_window.png");
    ResourceManager::loadTexture("test_ui", "ui_test.png");

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

    ResourceManager::loadGuiStyle("button_mto", GuiStyle(
        ResourceManager::getFont("mono_font"),
        1,
        sf::Color(0xff, 0xff, 0xff, 0x00), sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0xff, 0xff, 0xff, 0xff),
        sf::Color(0xff, 0xff, 0xff, 0x00), sf::Color(0xff, 0xff, 0xff, 0x00), sf::Color(0x00, 0x00, 0x00, 0xff)));

    mto_index = _MTO_texture_indexes({
        sf::Vector2i(3,0),
        sf::Vector2i(4,0),
        sf::Vector2i(5,0),
        sf::Vector2i(3,1),
        sf::Vector2i(4,1),
        sf::Vector2i(5,1),
        sf::Vector2i(3,2),
        sf::Vector2i(4,2),
        sf::Vector2i(5,2) });

    mto_index_two = _MTO_texture_indexes({
        sf::Vector2i(0,0),
        sf::Vector2i(1,0),
        sf::Vector2i(2,0),
        sf::Vector2i(0,1),
        sf::Vector2i(1,1),
        sf::Vector2i(2,1),
        sf::Vector2i(0,2),
        sf::Vector2i(1,2),
        sf::Vector2i(2,2) });

    tex_info = {
        ResourceManager::getTexture("test_ui"),                     // texture
        sf::Vector2f(8.0f,8.0f),                                    // element size
        sf::Vector2f(1.0f,1.0f),                                    // padding
        sf::Vector2f(1.0f,1.0f),                                    // offset
        sf::Vector2i(6,3)                                           // texture array size
    };

    spr_info = {
        sf::Vector2f(pos.x, pos.y * 1.3f),                          // position
        sf::Vector2f(200.0f, 200),                                  // size
        sf::Vector2f(1.0f, 1.0f),                                   // scale
        sf::Vector2f(100.0f, 100.0f),                               // origin
        sf::Vector2f(1.0f, 1.0f),                                   // add_scale
    };

    spr_info_two = {
        sf::Vector2f(400, 300.0f),                                  // position
        sf::Vector2f(128.0f, 32.0f),                                // size
        sf::Vector2f(1.0f, 1.0f),                                   // scale
        sf::Vector2f(64.0f, 16.0f),                                 // origin
        sf::Vector2f(1.0f, 1.0f),                                   // add_scale
    };

    mto_sprite = MultiTileObject(
        &tex_info,
        &spr_info,
        &mto_index
    );

    mto_sprite_two = MultiTileObject(
        &tex_info,
        &spr_info_two,
        &mto_index_two
    );

    //gui setup
    this->guiSys.emplace("menu", Gui(
        sf::Vector2f(128, 32), 14,
        1, 8, false, true, *ResourceManager::getGuiStyle("button_mto"),
        { std::make_pair("New game", "game_state"),
        std::make_pair("Options", "options_state"),
        std::make_pair("Exit","exit_state") },
        true,
        mto_sprite_two));
    this->guiSys.at("menu").setOrigin(this->guiSys.at("menu").gui_size.x * 0.5f,
                                        this->guiSys.at("menu").gui_size.y * 0.5f);
    this->guiSys.at("menu").setPosition(pos.x, pos.y * 1.3f);
    this->guiSys.at("menu").show();

    this->guiSys.emplace("text", Gui(
        sf::Vector2f(192 * 3, 32 * 3), 100,
        1, 5, false, true, *ResourceManager::getGuiStyle("header"),
        { std::make_pair("Main menu", "text") }));
    this->guiSys.at("text").setPosition(view->getCenter().x, view->getCenter().y * 0.7f);
    this->guiSys.at("text").setOrigin(192 * 3 * 0.5f, 32 * 3 * 0.5f);
    this->guiSys.at("text").show();

    tex.loadFromFile("../res/img/t1.png");
    tex_ico.loadFromFile("../res/img/icon.png");
    tex.setRepeated(true);

    sprite.setTexture(tex);
    sprite.setTextureRect(sf::IntRect(0, 0, 800, 32));
    sprite.setPosition(pos.x, pos.y * 0.4f);
    sprite.setScale(4, 4);
    sprite.setOrigin(sprite.getLocalBounds().width * 0.5f, sprite.getLocalBounds().height * 0.5f);

    ico.setTexture(tex_ico);
    ico.setOrigin(16,16);
    ico.setPosition(pos.x, pos.y * 0.4f);
    ico.setScale(4, 4);
    ico.setOrigin(ico.getLocalBounds().width * 0.5f, ico.getLocalBounds().height * 0.5f);

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
            this->view->setCenter(pos);
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), *this->view);
            this->guiSys.at("menu").setPosition(pos);
            break;
        }
        case sf::Event::KeyPressed:
        {
            if (event->key.code == sf::Keyboard::Escape)
            {
                //this->engine->window.close();
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
                        this->engine->_push(new SceneThree(this->engine));
                    }

                    if (msg == "options_state")
                    {
                        this->engine->_push(new SceneTwo(this->engine));
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
        case sf::Event::KeyReleased:
        {
            if (event->key.code == sf::Keyboard::Tilde)
            {
                this->engine->_debug_ = !this->engine->_debug_;
            }
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
    this->engine->window.draw(mto_sprite);
    //render gui
    for (auto gui : this->guiSys)
    {
        this->engine->window.draw(gui.second);
    }

    //debug
    if (this->engine->_debug_) 
        sfd::drawGrid(this->engine->window, 16, 9, sf::Color(0xff, 0xff, 0xaa, 0x33));

    return;
}

void SceneOne::cleanup()
{

}
