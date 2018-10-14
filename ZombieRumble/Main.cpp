#include "pch.h"
#include "Player.h"
using namespace sf;

int main()
{
	VideoMode vm{ 300,400 };
	Window window{ vm, "Pupka", Style::Default };

	game::Player p;
	p.spawn({ 10,20,30,40 }, { 100,200 }, 5);
	//p.getSprite().setPosition(301, 304);

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		window.display();
	}
	return 0;
}