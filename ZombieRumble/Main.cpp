#include "pch.h"
#include "Gameplay.h"
using namespace game;

int main()
{
	Vector2f resolution{
		static_cast<float>(VideoMode::getDesktopMode().width),
		static_cast<float>(VideoMode::getDesktopMode().height) };

	RenderWindow window{ VideoMode { static_cast<unsigned>(resolution.x),
		static_cast<unsigned>(resolution.y) }, "ZombieRumble", Style::Fullscreen };

	View mainView{ FloatRect{0, 0, resolution.x, resolution.y} };

	Game theGame;
	Player player;
	GameTime time;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Return && theGame.playing())
					theGame.set_paused();
				else if (event.key.code == Keyboard::Return && theGame.paused()) {
					theGame.set_playing();
					time.clock_restart();
				}
				else if (event.key.code == Keyboard::Return && theGame.game_over())
					theGame.set_leveling();

				if (theGame.playing()) {

				}
			}
		} // event poll

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		if (Keyboard::isKeyPressed(Keyboard::A))
			player.moveLeft();
		else
			player.stopLeft();
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.moveRight();
		else
			player.stopRight();
		if (Keyboard::isKeyPressed(Keyboard::W))
			player.moveUp();
		else
			player.stopUp();
		if (Keyboard::isKeyPressed(Keyboard::S))
			player.moveDown();
		else
			player.stopDown();

	}

	return 0;
}
