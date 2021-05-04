#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct _MTO_texture_indexes
{
    std::vector<sf::Vector2i> indexes;

    _MTO_texture_indexes(std::vector<sf::Vector2i> indexes)
    {
        this->indexes = indexes;
    }
    _MTO_texture_indexes() {}
};

struct _MTO_texture_info
{
    sf::Texture* texture;
    sf::Vector2f texture_element_size;
    sf::Vector2f texture_element_padding;
    sf::Vector2f texture_element_offset;
    sf::Vector2i texture_array_size;

    _MTO_texture_info() {}
    _MTO_texture_info(sf::Texture* texture,
        sf::Vector2f _size,
        sf::Vector2f _padding,
        sf::Vector2f _offset,
        sf::Vector2i _arr_size
    )
    {
        this->texture = texture;
        this->texture_element_size = _size;
        this->texture_element_padding = _padding;
        this->texture_element_offset = _offset;
        this->texture_array_size = _arr_size;
    }
};

struct _MTO_sprite_info
{
    sf::Vector2f sprite_position;
    sf::Vector2f sprite_size;
    sf::Vector2f sprite_scale;
    sf::Vector2f sprite_origin;
    sf::Vector2f sprite_add_scale;

    _MTO_sprite_info(
        sf::Vector2f _position,
        sf::Vector2f _size
    )
    {
        this->sprite_position = _position;
        this->sprite_size = _size;
        this->sprite_scale = sf::Vector2f(1.0f, 1.0f);
        this->sprite_origin = sf::Vector2f(0.0f, 0.0f);
        this->sprite_add_scale = sf::Vector2f(1.0f, 1.0f);
    }
    _MTO_sprite_info(
        sf::Vector2f _position,
        sf::Vector2f _size,
        sf::Vector2f _scale,
        sf::Vector2f _origin
    )
    {
        this->sprite_position = _position;
        this->sprite_size = _size;
        this->sprite_scale = _scale;
        this->sprite_origin = _origin;
        this->sprite_add_scale = sf::Vector2f(1.0f, 1.0f);
    }
    _MTO_sprite_info(
        sf::Vector2f _position,
        sf::Vector2f _size,
        sf::Vector2f _scale,
        sf::Vector2f _origin,
        sf::Vector2f _add_scale
    )
    {
        this->sprite_position = _position;
        this->sprite_size = _size;
        this->sprite_scale = _scale;
        this->sprite_origin = _origin;
        this->sprite_add_scale = _add_scale;
    }
    _MTO_sprite_info() {}
};

class MultiTileObject : public sf::Drawable, public sf::Transformable
{
private:
    _MTO_texture_info* tex_s;
    _MTO_sprite_info* spr_s;
    _MTO_texture_indexes* tex_ind_s;
    std::vector<sf::Sprite> sprites;
    sf::Vector2i arr_size;
    sf::Vector2f origin;

    void shater();

    void buildDepends();

    void setAddscale(sf::Vector2f addscale);


public:

    MultiTileObject(_MTO_texture_info* texture_struct,
        _MTO_sprite_info* sprite_structure,
        _MTO_texture_indexes* ti_s)
    {
        this->tex_s = texture_struct;
        this->spr_s = sprite_structure;
        this->tex_ind_s = ti_s;

        arr_size = sf::Vector2i(3, 3);

        shater();
        setSize(spr_s->sprite_size);
        setOrigin(spr_s->sprite_origin);
        setPosition(spr_s->sprite_position);
    }
    MultiTileObject() {}

    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setOrigin(sf::Vector2f origin);
    void setScale(sf::Vector2f scale);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
   
};

