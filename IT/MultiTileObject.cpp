#include "MultiTileObject.h"

void MultiTileObject::shater()
{
    for (auto spr : this->tex_ind_s->indexes)
    {
        this->sprites.push_back(
            sf::Sprite(*this->tex_s->texture,
                sf::IntRect(
                    int(tex_s->texture_element_offset.x + (tex_s->texture_element_padding.x + tex_s->texture_element_size.x) * spr.x),
                    int(tex_s->texture_element_offset.y + (tex_s->texture_element_padding.y + tex_s->texture_element_size.y) * spr.y),
                    int(tex_s->texture_element_size.x),
                    int(tex_s->texture_element_size.y))));
    }
}

void MultiTileObject::buildDepends()
{
    int index = 0;

    sf::Vector2f position = sf::Vector2f(spr_s->sprite_position.x - spr_s->sprite_origin.x, spr_s->sprite_position.y - spr_s->sprite_origin.y);
    sf::Vector2f scale = spr_s->sprite_scale;
    sf::Vector2f addscale = spr_s->sprite_add_scale;
    sf::Vector2f size = tex_s->texture_element_size;


    for (int i = 0; i < this->arr_size.y; i++)
    {
        for (int j = 0; j < this->arr_size.x; j++)
        {
            this->sprites[index].setScale(scale);
            this->sprites[index].setPosition(int(position.x + (j * (size.x * scale.x))), int(position.y + (i * (size.y * scale.y))));

            // XY dependices
            if (index == 8)
            {
                this->sprites[index].setPosition(
                    int(position.x + ((j - 1) * (size.x * scale.x)) + (size.x * (scale.x * addscale.x))),
                    int(position.y + ((i - 1) * (size.y * scale.y)) + (size.y * (scale.y * addscale.y))));
            }
            // Y dependices
            if (index == 6 || index == 7)
            {
                this->sprites[index].setPosition(
                    int(position.x + (j * size.x * scale.x)),
                    int(position.y + ((i - 1) * (size.y * scale.y)) + (size.y * (scale.y * addscale.y))));
            }
            // X dependices
            if (index == 2 || index == 5)
            {
                this->sprites[index].setPosition(
                    int(position.x + (((j - 1) * (size.x * scale.x)) + (size.x * (scale.x * addscale.x)))),
                    int(position.y + (i * size.y * scale.y)));
            }


            // XY scale dependices
            if (index == 4)
            {
                this->sprites[index].setScale(int(scale.x * addscale.x), int(scale.y * addscale.y));
            }
            // Y scale dependices
            if (index == 3 || index == 5)
            {
                this->sprites[index].setScale(int(scale.x), int(scale.y * addscale.y));
            }
            // X scale dependices
            if (index == 1 || index == 7)
            {
                this->sprites[index].setScale(int(scale.x * addscale.x), int(scale.y));
            }

            ++index;
        }
    }
}

void MultiTileObject::setPosition(sf::Vector2f position)
{
    spr_s->sprite_position = position;
    buildDepends();
    //calcBounds();
}

void MultiTileObject::setAddscale(sf::Vector2f addscale)
{
    spr_s->sprite_add_scale = addscale;
    buildDepends();
    //calcBounds();
}

void MultiTileObject::setOrigin(sf::Vector2f origin)
{
    spr_s->sprite_origin = origin;
    buildDepends();
    //calcBounds();
}

void MultiTileObject::setScale(sf::Vector2f scale)
{
    spr_s->sprite_scale = scale;
    buildDepends();
    //calcBounds();
}

void MultiTileObject::setSize(sf::Vector2f size)
{
    setAddscale(sf::Vector2f(
        ((size.x - (tex_s->texture_element_size.x * 2)) / tex_s->texture_element_size.x),
        ((size.y - (tex_s->texture_element_size.y * 2)) / tex_s->texture_element_size.y)
    ));
}

void MultiTileObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto spr : this->sprites)
    {
        target.draw(spr);
    }
}
