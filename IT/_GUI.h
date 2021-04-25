#pragma once

#include <vector>
#include <utility>
#include <string>

#include <SFML/Graphics.hpp>
#include "MultiTileObject.h"

struct GUI_container 
{
    sf::Vector2f size;
    sf::Vector2f position;
    MultiTileObject sprite;
    std::vector<GUI_container*> child;
    GUI_container* parent;

    GUI_container(sf::Vector2f position, sf::Vector2f size, GUI_container* parent = nullptr) 
    {
        
        this->size = size;
        this->parent = parent;

        if (parent == nullptr)
        {     
            this->position = position;
        }
        else
        {
            this->position = parent->position + position;
            parent->child.push_back(this);
        }
    }
    GUI_container() {}

    void setSprite(MultiTileObject sprite)
    {
        this->sprite = sprite;
        this->sprite.setPosition(this->position);
        this->sprite.setSize(this->size);
    }
};

struct GUI_data
{
    bool horrizontal;
    bool visible;
    bool text_centred;

    int padding;
    unsigned int char_size;

    float offset;

    GUI_data(bool horrizontal,
        bool visible,
        bool text_centred,
        int padding,
        unsigned int char_size,
        float offset)
    {

    }
    GUI_data() {}
};

struct GUI_style
{
    sf::Color bodyColor;
    sf::Color bodyHighlight;
    sf::Color borderColor;
    sf::Color borderHighlight;
    sf::Color textColor;
    sf::Color textBorder;
    sf::Color textHighlight;
    sf::Color textBorderHighlight;


    sf::Font* font;
    float borderSize;
    float textBorderSize;
    
    GUI_style(sf::Font* font,
        float borderSize,
        float textBorderSize,
        sf::Color bodyColor,
        sf::Color borderColor,
        sf::Color textColor,
        sf::Color textBorder,
        sf::Color bodyHighlight,
        sf::Color borderHighlight,
        sf::Color textHighlight,
        sf::Color textBorderHighlight)
    {
        this->bodyColor = bodyColor;
        this->borderColor = borderColor;
        this->textColor = textColor;
        this->textBorder = textBorder;
        this->bodyHighlight = bodyHighlight;
        this->borderHighlight = borderHighlight;
        this->textHighlight = textHighlight;
        this->textBorderHighlight = textBorderHighlight;
        this->font = font;
        this->borderSize = borderSize;
        this->textBorderSize = textBorderSize;
    }

    GUI_style() {}
};

struct GUI_entry
{
    sf::RectangleShape shape;
    std::string message;
    sf::Text text;

    GUI_entry(const std::string& message,
        sf::RectangleShape shape,
        sf::Text text)
    {
        this->message = message;
        this->shape = shape;
        this->text = text;
    }
    GUI_entry(){}
};

class GUI_element
{
private:
    std::vector<GUI_entry> entries;
    std::vector<GUI_container> container;
    GUI_data* data;
    GUI_style* style;

public:

    GUI_element(GUI_data* data,
        GUI_style* style,
        sf::RectangleShape shape,
        std::vector<std::pair<std::string,std::string>> entries) 
    {
        this->style = style;
        this->data = data;
        
        for (auto entry : entries)
        {
            sf::Text text;
            text.setString(entry.first);
            text.setFont(*style->font);
            text.setFillColor(style->textColor);
            text.setCharacterSize(data->char_size);

            this->entries.push_back(GUI_entry(entry.second, shape, text));
        }
    }

    GUI_element() {}
};

