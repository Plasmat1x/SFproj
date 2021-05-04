#include "Gui.h"
#include <iostream>

void Gui::init(sf::Vector2f dimension,
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

        if (horizontal)
        {
            gui_size.x += dimension.x + offset;
            gui_size.y = dimension.y;
        }
        else
        {
            gui_size.x = dimension.x;
            gui_size.y += dimension.y + offset;
        }
    }
}

sf::Vector2f Gui::getSize()
{
    return sf::Vector2f(this->dimension.x, this->dimension.y * this->entries.size());
}

int Gui::getEntry(const sf::Vector2f mousePos)
{
    if (entries.size() == 0) return -1;
    if (!this->visible) return -1;

    for (int i = 0; i < this->entries.size(); ++i)
    {
        sf::Vector2f point = mousePos;
        point += this->entries[i].shape.getOrigin();
        point -= this->entries[i].shape.getPosition();

        if (point.x < 0 || point.x > this->entries[i].shape.getScale().x * this->dimension.x) continue;
        if (point.y < 0 || point.y > this->entries[i].shape.getScale().y * this->dimension.y) continue;
        return i;
    }

    return -1;
}

void Gui::setEntryText(int entry, std::string text)
{
    if (entry >= entries.size() || entry < 0) return;
    entries[entry].text.setString(text);
    return;
}

void Gui::setDimensions(sf::Vector2f dimension)
{
    this->dimension = dimension;
    for (auto& entry : entries)
    {
        entry.shape.setSize(dimension);
        //entry.text.setCharacterSize(dimension.y - style.borderSize - padding);
        entry.text.setCharacterSize(charSize);
    }
    return;
}

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!visible) return;

    for (auto entry : this->entries)
    {
        target.draw(entry.shape);
        if (mto_enable)
        {
            target.draw(entry.mto);
        }
        target.draw(entry.text);
    }

    return;
}

void Gui::_setTexture(sf::Texture* texture)
{
    for (auto& entry : this->entries)
    {
        entry.shape.setTexture(texture);
    }
}

void Gui::_setMTO(MultiTileObject mto)
{
    this->mto = mto;
    this->mto_enable = true;

    this->mto.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y));

}

void Gui::show()
{
    sf::Vector2f _offset(0.0f, 0.0f);
    this->visible = true;
    for (auto& entry : this->entries)
    {
        sf::Vector2f origin = this->getOrigin();
        origin -= _offset;

        entry.shape.setOrigin(origin);
        entry.text.setOrigin(origin.x , origin.y);

        if (text_centred)
        {
            /*
            Убический костыль центровки текста на обьекте
            */
            entry.text.setOrigin(
                (int)(entry.text.getLocalBounds().width * 0.5f + origin.x),
                (int)(entry.text.getLocalBounds().height * 0.5f + origin.y)
            );

            entry.text.setPosition(
                (int)(this->getPosition().x + dimension.x * 0.5f),
                (int)((this->getPosition().y + dimension.y * 0.45f))
            );
        }


        if (mto_enable)
        {
            entry.mto.setOrigin(origin);
            entry.mto.setSize(dimension);
            entry.mto.setPosition(sf::Vector2f(
                this->getPosition().x,
                this->getPosition().y));
        }
        entry.shape.setPosition(this->getPosition());

        if (this->horizontal) _offset.x += this->dimension.x + offset;
        else _offset.y += this->dimension.y + offset;
    }
    return;
}

void Gui::hide()
{
    this->visible = false;

    return;
}

void Gui::highlight(const int entry)
{
    for (int i = 0; i < entries.size(); ++i)
    {
        if (i == entry)
        {
            entries[i].shape.setFillColor(style.bodyHighlight);
            entries[i].shape.setOutlineColor(style.borderHighlight);
            entries[i].text.setFillColor(style.textHighlight);
        }
        else
        {
            entries[i].shape.setFillColor(style.bodyColor);
            entries[i].shape.setOutlineColor(style.borderColor);
            entries[i].text.setFillColor(style.textColor);
        }
    }

    return;
}

void Gui::highlight(const sf::Vector2f mousePos)
{
    int entry = this->getEntry(mousePos);
    highlight(entry);
}


std::string Gui::activate(const int entry)
{
    if (entry == -1) return "null";
    return entries[entry].message;
}

std::string Gui::activate(const sf::Vector2f mousePos)
{
    int entry = this->getEntry(mousePos);
    return this->activate(entry);
}