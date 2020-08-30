#include "System.h"
#include "StateIntro.h"
#include "StateGame.h"
#include "StateMenu.h"

StateIntro StateIntro::m_StateIntro;

void StateIntro::Init(System* game)
{
	img.load("res/img/icon.png");
	img.setPosition(game->GetWindowSize().x / 2, game->GetWindowSize().y / 2);
	img.scale(10);
}

void StateIntro::Cleanup()
{

}

void StateIntro::Pause()
{

}

void StateIntro::Resume()
{

}

void StateIntro::HandleEvents(System* game)
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { game->GetWindow().close(); }
	if (game->keyboard.getEventButton(sf::Keyboard::Space) || Timer >= 5000) { game->ChangeState(StateMenu::Instance()); }
}

void StateIntro::Update(System* game,float Time) 
{
	Timer += Time;
	img.setDAlpha(Timer-2000);
}

void StateIntro::Render(System* game) 
{
	game->GetWindow().clear(sf::Color(70, 70, 120));
	img.draw(&game->GetWindow());
	game->GetWindow().display();
}
