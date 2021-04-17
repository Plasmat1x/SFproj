#pragma once
#include <vector>
#include <utility>
#include <string>

#include <SFML/Graphics.hpp>
#include "MultiTileObject.h"

struct GuiStyle
{
    sf::Color bodyColor;
    sf::Color bodyHighlight;
    sf::Color borderColor;
    sf::Color borderHighlight;
    sf::Color textColor;
    sf::Color textHighlight;

    sf::Font* font;
    float borderSize;

    /// <summary>
    /// Stylesheet for GUI
    /// </summary>
    /// <param name="font"></param>
    /// <param name="borderSize"></param>
    /// <param name="bodyColor"></param>
    /// <param name="borderColor"></param>
    /// <param name="textColor"></param>
    /// <param name="bodyHighlight"></param>
    /// <param name="borderHighlight"></param>
    /// <param name="textHighlight"></param>
    GuiStyle(sf::Font* font,
        float borderSize,
        sf::Color bodyColor,
        sf::Color borderColor,
        sf::Color textColor,
        sf::Color bodyHighlight,
        sf::Color borderHighlight,
        sf::Color textHighlight)
    {
        this->bodyColor = bodyColor;
        this->borderColor = borderColor;
        this->textColor = textColor;
        this->bodyHighlight = bodyHighlight;
        this->borderHighlight = borderHighlight;
        this->textHighlight = textHighlight;
        this->font = font;
        this->borderSize = borderSize;
    }

    GuiStyle() {}
};

struct GuiEntry
{
    sf::RectangleShape shape;
    MultiTileObject mto;
    std::string message;
    sf::Text text;

    /// <summary>
    /// Style of gui
    /// </summary>
    /// <param name="message"></param>
    /// <param name="shape"></param>
    /// <param name="text"></param>
    GuiEntry(const std::string& message,
        sf::RectangleShape shape,
        sf::Text text)
    {
        this->message = message;
        this->shape = shape;
        this->text = text;
    }

    GuiEntry(const std::string& message,
        sf::RectangleShape shape,
        sf::Text text,
        MultiTileObject mto)
    {
        this->message = message;
        this->shape = shape;
        this->text = text;
        this->mto = mto;
    }

    GuiEntry() {}
};

class Gui : public sf::Transformable, public sf::Drawable
{
private:
    bool horizontal;
    GuiStyle style;
    sf::Vector2f dimension;
    int padding;
    float offset;
    unsigned int charSize;
    
    bool mto_enable = false;
    MultiTileObject mto;

public:
    std::vector<GuiEntry> entries;
    bool visible;
    bool text_centred;

    /// <summary>
    /// Create GUI
    /// </summary>
    /// <param name="dimension">size</param>
    /// <param name="charSize"></param>
    /// <param name="padding">between elements</param>
    /// <param name="offset"></param>
    /// <param name="horizontal"></param>
    /// <param name="text_centred"></param>
    /// <param name="style"></param>
    /// <param name="entries">elements</param>
    Gui(sf::Vector2f dimension,
        unsigned int charSize,
        int padding,
        float offset,
        bool horizontal,
        bool text_centred,
        GuiStyle& style,
        std::vector<std::pair<std::string, std::string>> entries)
    {
        visible = false;
        this->horizontal = horizontal;
        this->style = style;
        this->dimension = dimension;
        this->charSize = charSize;
        this->padding = padding;
        this->offset = offset;
        this->text_centred = text_centred;

        sf::RectangleShape shape;
        shape.setSize(dimension);
        shape.setFillColor(style.bodyColor);
        shape.setOutlineThickness(-style.borderSize);
        shape.setOutlineColor(style.borderColor);

        for (auto entry : entries)
        {
            sf::Text text;
            text.setString(entry.first);
            text.setFont(*style.font);
            text.setFillColor(style.textColor);
            //text.setCharacterSize(dimension.y - style.borderSize - padding);
            text.setCharacterSize(charSize);
            if (mto_enable)
            {
                this->entries.push_back(GuiEntry(entry.second, shape, text, mto));
            }
            else
            {
                this->entries.push_back(GuiEntry(entry.second, shape, text));
            }

        }

    }
    Gui(sf::Vector2f dimension,
        unsigned int charSize,
        int padding,
        float offset,
        bool horizontal,
        bool text_centred,
        GuiStyle& style,
        std::vector<std::pair<std::string, std::string>> entries,
        bool mto_enable,
        MultiTileObject mto)
    {
        this->mto_enable = mto_enable;
        this->mto = mto;
        
        Gui(dimension,
            charSize,
            padding, 
            offset,
            horizontal, 
            text_centred, 
            style, 
            entries);
    }

    sf::Vector2f getSize();
    
    void _setTexture(sf::Texture* texture);
    void _setMTO(MultiTileObject mto);

    int getEntry(const sf::Vector2f mousePos);

    void setEntryText(int entry, std::string text);

    void setDimensions(sf::Vector2f dimension);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void show();

    void hide();

    void highlight(const int entry);
    void highlight(const sf::Vector2f mousePos);

    std::string activate(const int entry);
    std::string activate(const sf::Vector2f mousePos);
};