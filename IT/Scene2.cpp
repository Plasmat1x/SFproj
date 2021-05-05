#include <iostream>
#include <iomanip>
#include "ResourceManager.h"
#include "Scene2.h"

#include<tinyxml/tinyxml.h>

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

    this->buf = *this->engine->config;

    mto_index = _MTO_texture_indexes({
    sf::Vector2i(3,0),
    sf::Vector2i(4,0),
    sf::Vector2i(5,0),
    sf::Vector2i(3,1),
    sf::Vector2i(4,1),
    sf::Vector2i(5,1),
    sf::Vector2i(3,2),
    sf::Vector2i(4,2),
    sf::Vector2i(5,2)});

    mto_index_two = _MTO_texture_indexes({
        sf::Vector2i(0,0),
        sf::Vector2i(1,0),
        sf::Vector2i(2,0),
        sf::Vector2i(0,1),
        sf::Vector2i(1,1),
        sf::Vector2i(2,1),
        sf::Vector2i(0,2),
        sf::Vector2i(1,2),
        sf::Vector2i(2,2)});

    tex_info = {
        ResourceManager::getTexture("test_ui"),                     // texture
        sf::Vector2f(8.0f,8.0f),                                    // element size
        sf::Vector2f(1.0f,1.0f),                                    // padding
        sf::Vector2f(1.0f,1.0f),                                    // offset
        sf::Vector2i(6,3)                                           // texture array size
    };

    spr_info = {
        sf::Vector2f(pos.x, pos.y),                                 // position
        sf::Vector2f(1280.0f, 720.0f),                              // size
        sf::Vector2f(1.0f, 1.0f),                                   // scale
        sf::Vector2f(640.0f, 360.0f),                               // origin
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

    mto_sprite_two.setSize(sf::Vector2f(800, 600));

    //gui setup
    this->guiSys.emplace("menu", Gui(
        sf::Vector2f(256, 32), 14,
        1, 5, true, true, *ResourceManager::getGuiStyle("button_mto"),
        { std::make_pair("Save", "save_state"),
        std::make_pair("Back","back_state") },
        true,
        mto_sprite_two));
    this->guiSys.at("menu").setPosition(pos.x, pos.y * 1.8f);
    this->guiSys.at("menu").setOrigin(this->guiSys.at("menu").gui_size.x * 0.5f, 
                                        this->guiSys.at("menu").gui_size.y * 0.5f);
    this->guiSys.at("menu").show();

    this->guiSys.emplace("text", Gui(
        sf::Vector2f(192 * 3, 32 * 3), 100,
        1, 5, false, true, *ResourceManager::getGuiStyle("header"),
        { std::make_pair("Options", "text") }));
    this->guiSys.at("text").setPosition(pos.x, pos.y * 0.2f);
    this->guiSys.at("text").setOrigin(192 * 3 * 0.5f, 32 * 3 * 0.5f);
    this->guiSys.at("text").show();

    //----------
    this->guiSys.emplace("conf_txt", Gui(
        sf::Vector2f(128, 32), 16,
        1, 5, false, true, *ResourceManager::getGuiStyle("text"),
        { 
            std::make_pair("Resolution", ""),
            std::make_pair("VSync", ""),
            std::make_pair("Full screen", ""),
            std::make_pair("txt param", ""),
            std::make_pair("txt param", ""),
            std::make_pair("txt param", "")
        }));
    this->guiSys.at("conf_txt").setPosition(pos.x * 0.8f, pos.y);
    this->guiSys.at("conf_txt").setOrigin(this->guiSys.at("conf_txt").gui_size.x * 0.5f,
        this->guiSys.at("conf_txt").gui_size.y * 0.5f);
    this->guiSys.at("conf_txt").show();

    this->guiSys.emplace("conf_bt", Gui(
        sf::Vector2f(128, 32), 14,
        1, 5, false, true, *ResourceManager::getGuiStyle("button_mto"),
        { 
            std::make_pair("bt param", "rs_bt"),
            std::make_pair("bt param", "vs_bt"),
            std::make_pair("bt param", "fs_bt"),
            std::make_pair("bt param", ""),
            std::make_pair("bt param", ""),
            std::make_pair("bt param", "")
        },
        true,
        mto_sprite_two));
    this->guiSys.at("conf_bt").setPosition(pos.x * 1.2f, pos.y);
    this->guiSys.at("conf_bt").setOrigin(this->guiSys.at("conf_bt").gui_size.x * 0.5f,
        this->guiSys.at("conf_bt").gui_size.y * 0.5f);
    this->guiSys.at("conf_bt").show();
  
      
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
                this->engine->window.setVerticalSyncEnabled(this->engine->config->v_sync);
                if (this->engine->config->full_screen)
                {
                    this->engine->window.create(sf::VideoMode(this->engine->config->width, this->engine->config->height), buf.app_name,
                        sf::Style::Fullscreen);
                }
                else
                {
                    this->engine->window.create(sf::VideoMode(this->engine->config->width, this->engine->config->height), buf.app_name,
                        sf::Style::Titlebar | sf::Style::Close);
                }

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
                        TiXmlDocument doc;
                        doc.LoadFile("Config.xml");

                        TiXmlElement* root = doc.FirstChildElement("config");;
                        root->SetAttribute("app", buf.app_name.c_str());

                        TiXmlElement* param = root->FirstChildElement("param");
                        param->SetAttribute("width", buf.width);
                        param = param->NextSiblingElement("param");
                        param->SetAttribute("height", buf.height);
                        param = param->NextSiblingElement("param");
                        param->SetAttribute("v_sync", buf.v_sync);
                        param = param->NextSiblingElement("param");
                        param->SetAttribute("frame_limit", buf.frame_limit);
                        param = param->NextSiblingElement("param");
                        param->SetAttribute("full_screen", buf.full_screen);

                        doc.SaveFile("Config.xml");
                        this->engine->_pop();
                        return;
                    }
                    if (msg == "back_state")
                    {
                        this->engine->window.setVerticalSyncEnabled(this->engine->config->v_sync);
                        if (this->engine->config->full_screen)
                        {
                            this->engine->window.create(sf::VideoMode(this->engine->config->width, this->engine->config->height), buf.app_name,
                                sf::Style::Fullscreen);
                        }
                        else
                        {
                            this->engine->window.create(sf::VideoMode(this->engine->config->width, this->engine->config->height), buf.app_name,
                                sf::Style::Titlebar | sf::Style::Close);
                        }

                        this->engine->_pop();
                        return;
                    }
                    if (msg == "rs_bt")
                    {
                        this->engine->window.create(sf::VideoMode(buf.width, buf.height), buf.app_name);
                    }
                    if (msg == "vs_bt")
                    {
                        buf.v_sync = !buf.v_sync;
                        this->engine->window.setVerticalSyncEnabled(buf.v_sync);
                    }
                    if (msg == "fs_bt")
                    {
                        if (!buf.full_screen)
                        {
                            this->engine->window.create(sf::VideoMode(buf.width, buf.height), buf.app_name,
                                sf::Style::Fullscreen);
                            buf.full_screen = !buf.full_screen;
                        }
                        else
                        {
                            this->engine->window.create(sf::VideoMode(buf.width, buf.height), buf.app_name,
                                sf::Style::Titlebar | sf::Style::Close);
                            buf.full_screen = !buf.full_screen;
                        }

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
    //std::ostringstream oss;
    oss.seekp(0);
    oss << this->buf.width << " x " << this->buf.height << "  ";
    this->guiSys.at("conf_bt").setEntryText(0, oss.str());

    oss.seekp(0);
    oss << this->buf.v_sync << "          ";
    this->guiSys.at("conf_bt").setEntryText(1, oss.str());

    oss.seekp(0);
    oss << this->buf.full_screen << "          ";
    this->guiSys.at("conf_bt").setEntryText(2, oss.str());
}

void SceneTwo::render(const float dt)
{
    this->engine->window.setView(*this->view);
    this->engine->window.clear(sf::Color::Black);
    //render scene obj
    this->engine->window.draw(mto_sprite);
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

