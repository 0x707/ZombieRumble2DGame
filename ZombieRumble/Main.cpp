#include "pch.h"
#include "Gameplay.h"
#include "Arena.h"
using namespace game;
using KB = Keyboard;

void control_motion(Window&, Player&);
void control_upgrades(Game&, Event&);
void prepare_level(Game&, Player&, GameTime&);

int main()
{
	const Vector2f resolution{
		static_cast<float>(VideoMode::getDesktopMode().width),
		static_cast<float>(VideoMode::getDesktopMode().height) };
	
	GameScreen screen{ resolution, "ZombieRumble", Style::Fullscreen };
	Game theGame;
	Player player;
	GameTime time;
	Background bg{"graphics/background_sheet.png"};
	

	while (screen.sWindow.isOpen()) {

		Event event;
		while (screen.sWindow.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				if (event.key.code == KB::Return && theGame.playing())
					theGame.set_paused();
				else if (event.key.code == KB::Return && theGame.paused()) {
					theGame.set_playing();
					time.clock_restart();
				}
				else if (event.key.code == KB::Return && theGame.game_over())
					theGame.set_leveling();

				if (theGame.playing()) {

				}
			}
		} // event poll

		if (KB::isKeyPressed(KB::Escape))
			screen.sWindow.close();

		if (theGame.playing())
			control_motion(screen.sWindow, player);

		if (theGame.leveling()) {
			control_upgrades(theGame, event);

			if (theGame.playing()) {
				theGame.set_arena({ 0,0,500,500 }); // left, top, width, height
				bg.create(theGame.get_arena());
				player.spawn(theGame.get_arena(), resolution, game::TILE_SIZE);
				time.clock_restart();
			}
		} // end theGame.leveling()

		if (theGame.playing())
			theGame.update(time, screen, player);

		switch (theGame.get_state()) {
		case game_state::PLAYING:
			screen.sWindow.clear();
			screen.set_main_view();
			screen.sWindow.draw(bg.get_background_VA(), &bg());
			screen.sWindow.draw(player.getSprite());
			break;
		case game_state::LEVELING:
		case game_state::PAUSED:
		case game_state::GAME_OVER:
			break;
		};
		screen.sWindow.display();
	}

	return 0;
}

void control_motion(Window& window, Player& player)
{
	if (KB::isKeyPressed(KB::A))
		player.moveLeft();
	else
		player.stopLeft();
	if (KB::isKeyPressed(KB::D))
		player.moveRight();
	else
		player.stopRight();
	if (KB::isKeyPressed(KB::W))
		player.moveUp();
	else
		player.stopUp();
	if (KB::isKeyPressed(KB::S))
		player.moveDown();
	else
		player.stopDown();
}

void control_upgrades(Game& game, Event& event)
{
	switch (event.key.code) {
	case KB::Num1: game.set_playing();
		break;
	case KB::Num2: game.set_playing();
		break;
	case KB::Num3: game.set_playing();
		break;
	case KB::Num4: game.set_playing();
		break;
	case KB::Num5: game.set_playing();
		break;
	case KB::Num6: game.set_playing();
		break;
	}
}