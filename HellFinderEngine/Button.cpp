#include"Button.h"

void Button::Init(std::string Path, sf::String stext, sf::Vector2f Position, sf::IntRect Size, int s, System *game) {
	
	position = Position;
	size = Size;
	scale = s;
	sText = stext; 

    signal = false;
    focus = false;

    prevState = IDLE;
    curState = IDLE;

	this->SetTexture(Path);
	this->SetText(stext);
	this->SetFont("res/fonts/MorrisRomanBlack.ttf");
	this->SetSize(25);
	this->SetPosition(Position);

	sprite.setScale(scale, scale);
	sprite.setOrigin(size.width/2,size.height/2);
	sprite.setPosition(position);

	//text.setOrigin(Vector2f(text.getLocalBounds().width / 2, text.getLocalBounds().height));
	text.setScale(scale, scale);
}

void Button::Render(System *game) {
	if (focus) {
		sprite.setTextureRect(sf::IntRect(120, 0, 120, 37));
		text.setFillColor(sf::Color::Red);
	}
	else { sprite.setTextureRect(size); }

	if (signal && focus) {
		text.setFillColor(sf::Color::Blue);
	}
	else {
		text.setFillColor(sf::Color::Yellow);
	}

	game->GetWindow().draw(sprite);
	game->GetWindow().draw(text);
}

void Button::Update(float time, System *game) {
    signal = false;
    if (focus && prevState == PRESSED && curState == RELEASED && !signal)
    {
        signal = true;
    }
}

void Button::SetTexture(std::string Path) {
	image.loadFromFile(Path);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(size);
}

void Button::SetText(sf::String stext)
{
	text.setString(stext);
}

void Button::SetSize(int tSize = 16)
{
	text.setCharacterSize(tSize);
}

void Button::SetPosition(sf::Vector2f pos)
{
	int offsetx = 15;
	int offsety = 2;
	position = pos;
	sprite.setPosition(pos);
	text.setPosition((position.x - size.width/2*scale)+offsetx*scale,(position.y - size.height / 2 * scale)-offsety);
}
void Button::SetFont(std::string path)
{
	font.loadFromFile(path);
	text.setFont(font);
}


void Button::SetColor(sf::Color color)
{
	text.setFillColor(color);
}

bool Button::AABB(sf::Vector2i pPos)
{
    if (
        position.x < pPos.x &&
        position.x + size.width * scale > pPos.x &&
        position.y < pPos.y &&
        position.y + size.height * scale > pPos.y 
        ) 
    {
        focus = true;
        return true;
    }
    else 
    { 
        changeState(IDLE);
        focus = false;
        return false;
    }
}

void Button::changeState(btState state)
{
    prevState = curState;
    curState = state;
}

void Button::action()
{
    changeState(PRESSED);
}

void Button::endAction()
{
    changeState(RELEASED);
}
