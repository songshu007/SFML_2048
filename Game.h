#pragma once
#include "Settings.h"

enum Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Game
{
private:
	void initWindow();
	void updataSFMLEvent();
	void render();
	void updata();
	void display(Dir dir);
	void move(Dir dir);
	void createBlack();
	void starkLeft(int array[], const int size);
	void rotateMap();
	sf::Color getTileColor(int tile);
	sf::Color getTextColor(int tile);
	int getTextSize(int tile);

	// ±‰¡ø
	sf::RenderWindow window;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Event event;
	sf::Clock clock;
	float dt;

	int map[set::SquaresNum_Y][set::SquaresNum_X];

public:
	Game();
	~Game();
	void run();
};

