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

char const* get_level_up_string();

int main()
{
	const Vector2f resolution{
		static_cast<float>(VideoMode::getDesktopMode().width),
		static_cast<float>(VideoMode::getDesktopMode().height) };
	
	GameScreen screen{ resolution, "ZombieRumble", Style::Resize };
	Game theGame{ 500,500 };
	Player player;
	GameTime time;
	Background bg;
	ZombieHorde horde{ 10 }; // ctor argument defines the amount zombies to spawn
	arms::Gun gun;

	// HUD sprites & View
	View hudView({0, 0, screen.sResolution.x, screen.sResolution.y});

	hud::HudSprite gameOver{"graphics/background.png", 0, 0};
	hud::HudSprite ammoIcon{"graphics/ammo_icon.png", 20, 980};

	hud::HudText pauseText{ 155, {400, 400}, Color::White, "Press Enter \n to continue" };
	hud::HudText goverText{ 128, {250,850}, Color::White, "Press Enter to play"};
	hud::HudText levelText{ 80,{150,250}, Color::White, get_level_up_string()};
	hud::HudText ammoText{ 55,{200,980}, Color::White };
	hud::HudText scoreText{ 55,{20,0},Color::White };
	hud::HudText hiscrText{ 55,{1400,0},Color::White, "High score: " };
	hud::HudText zmbiermainText{55, {1500, 980}, Color::White, "Zombies: 100" };
	hud::HudText waveremainText{55, {1250, 980}, Color::White, "Wave: 0" };

	hud::HealthBar hpBar;

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
			break;
		case game_state::LEVELING:
		case game_state::PAUSED:
		case game_state::GAME_OVER:
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

char const* get_level_up_string()
{
	return "1 - Increased fire rate\n"
		"2 - Increased clip size\n"
		"3 - Increased max health\n"
		"4 - Increased run speed\n"
		"5 - Better health supplies\n"
		"6 - Better ammo supplies";
}
