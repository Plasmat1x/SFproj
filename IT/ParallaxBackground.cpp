#include "ParallaxBackground.h"

void ParallaxBackground::add_layer(parallax_layer pBackground, bool tiled = false, bool bottom = false)
{
   pBackground.texture->setRepeated(tiled);
   pBackground.size = sf::Vector2f(pBackground.texture->getSize().x, pBackground.texture->getSize().y);

   if (pBackground.size.y > maxSize.y)
   {
       maxSize.y = pBackground.size.y;
   }
   if (pBackground.size.x > maxSize.x)
   {
       maxSize.x = pBackground.size.x;
   }
   if (bottom)
   {
       pBackground.position.y += maxSize.y - pBackground.size.y;
   }
   pBackground.sprite.setTexture(*pBackground.texture);
   pBackground.sprite.setPosition(pBackground.position);
   if (tiled)
   {
       pBackground.sprite.setTextureRect(sf::IntRect(0, 0, pBackground.width, pBackground.size.y));
       pBackground.size.x = pBackground.width;
   }

   layers.push_back(pBackground);
}

void ParallaxBackground::setTarget(sf::Vector2f cur_targ)
{
    current_target = cur_targ;
}

void ParallaxBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto bg : layers)
    {
        sf::View v;
        v.zoom(0.5f);
        v.setCenter(bg.parallax * current_target.x, current_target.y);
        target.setView(v);
        target.draw(bg.sprite);
    }
}
