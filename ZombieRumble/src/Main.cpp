#include "Arena.h"
#include "Drawings.h"
#include "Gameplay.h"
#include "Horde.h"
#include "Score.h"
#include "TextureHolder.h"

using namespace game;
using KB = Keyboard;

void control_motion(Window&, Player&);
void control_upgrades(Game&, Event&);
void prepare_level(Game&, Player&, GameTime&);
void draw_horde(GameScreen&, ZombieHorde const&);
void draw_bullets(GameScreen&, arms::Gun const&);
void draw_supplies(GameScreen&, Game const&);
void draw_HUD(GameScreen&, View const&);

int main()
{
	const Vector2f resolution{
		static_cast<float>(VideoMode::getDesktopMode().width),
		static_cast<float>(VideoMode::getDesktopMode().height) };
	
	GameScreen screen{ resolution, "ZombieRumble", Style::Fullscreen };
	Game theGame{ 500,500 };
	Player player;
	GameTime time;
	Background bg;
	ZombieHorde horde{ 10 }; // ctor argument defines the amount zombies to spawn
	arms::Gun gun;

	// HUD sprites & View
	View hudView({0, 0, screen.sResolution.x, screen.sResolution.y});


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
					if (event.key.code == KB::R)
						gun.reload();
				}
			}
		} // event poll

		if (KB::isKeyPressed(KB::Escape))
			screen.sWindow.close();

		if (theGame.playing()) {
			control_motion(screen.sWindow, player);
			if (Mouse::isButtonPressed(Mouse::Left))
				gun.shot(time.get_total_game_time(),
					player.getCenter(), theGame.get_mouse_world_pos());
		}

		if (theGame.leveling()) {
			control_upgrades(theGame, event);

			if (theGame.playing()) {
				theGame.set_arena(500,500); // left, top, width, height
				bg.create(theGame.get_arena());
				player.spawn(theGame.get_arena(), resolution, game::TILE_SIZE);

				horde.release_mem();
				horde.prepare_horde(theGame.get_arena());

				time.clock_restart();
			}
		} // end theGame.leveling()

		// update each frame
		if (theGame.playing())
			theGame.update(time, screen, player, horde, gun);

		switch (theGame.get_state()) {
		case game_state::PLAYING:
			screen.sWindow.clear();
			screen.set_main_view();
			screen.sWindow.draw(bg.get_background_VA(), &bg());
			draw_horde(screen, horde);
			screen.sWindow.draw(player.getSprite());
			draw_supplies(screen, theGame);
			draw_bullets(screen, gun);
			screen.sWindow.draw(theGame.get_cursor_sprite());

			draw_HUD(screen, hudView);
			break;
		case game_state::LEVELING:
			screen.sWindow.draw(hud::HUD::get_instance().get_drawings().gameOver.sprite());
			screen.sWindow.draw(hud::HUD::get_instance().get_drawings().levelText.text());
			break;
		case game_state::PAUSED:
			screen.sWindow.draw(hud::HUD::get_instance().get_drawings().pauseText.text());
			break;
		case game_state::GAME_OVER:
			screen.sWindow.draw(hud::HUD::get_instance().get_drawings().gameOver.sprite());
			screen.sWindow.draw(hud::HUD::get_instance().get_drawings().goverText.text());
			break;
		};
		screen.sWindow.display();
	}

	horde.release_mem();
	return 0;
}

void control_motion(Window& window, Player& player)
{
	if (KB::isKeyPressed(KB::A))
		player.move(DIRS::LEFT, true);
	else
		player.move(DIRS::LEFT, false);
	if (KB::isKeyPressed(KB::D))
		player.move(DIRS::RIGHT, true);
	else
		player.move(DIRS::RIGHT, false);
	if (KB::isKeyPressed(KB::W))
		player.move(DIRS::UP, true);
	else
		player.move(DIRS::UP, false);
	if (KB::isKeyPressed(KB::S))
		player.move(DIRS::DOWN, true);
	else
		player.move(DIRS::DOWN, false);
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

void draw_horde(GameScreen& screen, ZombieHorde const& horde)
{
	for (int i = 0; i < horde.zombie_counter(); ++i)
		screen.sWindow.draw(horde[i]->get_sprite());
}

void draw_bullets(GameScreen& screen, arms::Gun const& gun)
{
	for (int i = gun.bullets().front(),
		j = gun.bullets().current_length();
		j > 0; i = ++i % gun.bullets().size(), --j)
		screen.sWindow.draw(gun[i]->get_shape());
}

void draw_supplies(GameScreen& screen, Game const& theGame)
{
	if (theGame.get_supplies().ammo_pack.is_spawned())
		screen.sWindow.draw(theGame.get_ammo_sprite());
	if (theGame.get_supplies().health_pack.is_spawned())
		screen.sWindow.draw(theGame.get_health_sprite());
}

void draw_HUD(GameScreen& screen, View const& view)
{
	hud::HUD const& h = hud::HUD::get_instance();
	screen.sWindow.setView(view);

	screen.sWindow.draw(h.get_drawings().ammoIcon.sprite());
	screen.sWindow.draw(h.get_drawings().ammoText.text());
	screen.sWindow.draw(h.get_drawings().scoreText.text());
	screen.sWindow.draw(h.get_drawings().hiscrText.text());
	screen.sWindow.draw(h.get_drawings().hpBar.bar());
	screen.sWindow.draw(h.get_drawings().waveremainText.text());
	screen.sWindow.draw(h.get_drawings().zmbiermainText.text());
}
