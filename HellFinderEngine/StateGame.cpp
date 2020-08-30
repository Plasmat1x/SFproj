#include "System.h"
#include "StateGame.h"
#include "StateMenu.h"
StateGame StateGame::m_StateGame;

void StateGame::Init(System* game)
{
	game->isGame = true;
	Player.Init("spiral_anim.png", 0, 0,32,64);
	camera.Init(Player.getPosition().x, Player.getPosition().y, game->GetWindowSize().x/2, game->GetWindowSize().y/2);
	map.Init("res/img/map.png");
}

void StateGame::Cleanup()
{

}

void StateGame::Pause()
{

}

void StateGame::Resume()
{

}

void StateGame::HandleEvents(System* game)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { game->PushState(StateMenu::Instance()); }
	Player.HandleEvents(game);
}

void StateGame::Update(System* game, float Time)
{
	Player.Update(game, Time);
	playerPosition = Player.getPosition();
	playerSize = Player.getSize();
	camera.Update(Time, sf::FloatRect(playerPosition.x, playerPosition.y, playerSize.x, playerSize.y));
	game->GetWindow().setView(camera.getView());
}

void StateGame::Render(System* game)
{
	game->GetWindow().clear(sf::Color(70, 70, 120));
	map.Render(game);
	Player.Draw(game);
	game->GetWindow().display();
}
