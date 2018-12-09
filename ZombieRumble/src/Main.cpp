#include "Arena.h"
#include "Audio.h"
#include "Drawings.h"
#include "Gameplay.h"
#include "Horde.h"
#include "Score.h"
#include "TextureHolder.h"

using namespace game;
using namespace arms;
using namespace hud;
using KB = Keyboard;

void control_motion(Window&, Player&);
void control_upgrades(Event&, Game&, Player&, Gun&);
void reset_game(Game&, Player&, Gun&);
void prepare_level(Game&, GameTime&, ZombieHorde&, Background&);
void draw_horde(GameScreen&, ZombieHorde const&);
void draw_bullets(GameScreen&, Gun const&);
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
	ZombieHorde horde{ 5 }; // ctor argument defines the amount zombies to spawn
	Gun gun;

	// HUD sprites & View
	View hudView({0, 0, screen.sResolution.x, screen.sResolution.y});

	Score::get_instance().load_high_score();

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
					reset_game(theGame, player, gun);

				if (theGame.playing()) {
					if (event.key.code == KB::R)
						gun.reload(time.get_total_game_time());
					if (horde.zombies_alive() < 1)
						theGame.set_leveling();
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
			control_upgrades(event, theGame, player, gun);

			if (theGame.playing()) {
				prepare_level(theGame, time, horde, bg);
				player.spawn(theGame.get_arena(), resolution, game::TILE_SIZE);
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

	Score::get_instance().save_high_score();
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

void control_upgrades(Event& event, Game& game, Player& player, Gun& gun)
{
	switch (event.key.code) {
	case KB::Num1:
		gun.increase_fire_rate(1.0f);
		game.set_playing();
		break;
	case KB::Num2:
		gun.increase_clip_size();
		game.set_playing();
		break;
	case KB::Num3:
		player.upgradeHealth();
		game.set_playing();
		break;
	case KB::Num4:
		player.upgradeSpeed();
		game.set_playing();
		break;
	case KB::Num5:
		game.upgrade_health_supply();
		game.set_playing();
		break;
	case KB::Num6:
		game.upgrade_ammo_supply();
		game.set_playing();
		break;
	}
}

void reset_game(Game& game, Player& player, Gun& gun)
{
	game.set_leveling();

	HUD::get_instance().reset_wave();
	Score::get_instance().reset_score();

	gun.reset_gun_stats();
	player.resetPlayerStats();
}

void prepare_level(Game& game, GameTime& time,
	ZombieHorde& horde, Background& bg)
{
	HUD::get_instance().increase_wave();
	int current_wave = HUD::get_instance().get_wave();

	int new_width = 500 + 100 * current_wave;
	int new_height = 400 + 50 * current_wave;

	game.set_arena(new_width, new_height);
	bg.create(game.get_arena());

	horde.release_mem();
	horde.increase_zombie_wave(current_wave * 5);
	horde.prepare_horde(game.get_arena());

	Sounds::get_instance()[AUDIO_BUFFER::POWERUP].play();

	time.clock_restart();	
}

void draw_horde(GameScreen& screen, ZombieHorde const& horde)
{
	for (int i = 0; i < horde.zombie_counter(); ++i)
		screen.sWindow.draw(horde[i]->get_sprite());
}

void draw_bullets(GameScreen& screen, Gun const& gun)
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
