#include "Game.h"

void Game::initWindow()
{
	sf::ContextSettings setting;
	setting.antialiasingLevel = 8;
	this->window.create(sf::VideoMode(set::WindowSize.x, set::WindowSize.y), "Hello", sf::Style::Default, setting);
	this->window.setFramerateLimit(60);

	this->font.loadFromFile("Font/ClearSans.ttf");

	this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(0, 0);
	this->shape.setSize(sf::Vector2f(set::BlockWidth, set::BlockHeight));
	this->shape.setScale(0.95, 0.95);

	// init map
	for (size_t y = 0; y < set::SquaresNum_Y; y++)
	{
		for (size_t x = 0; x < set::SquaresNum_X; x++)
		{
			this->map[y][x] = 0;
		}
	}
	/*this->map[0][0] = 2;
	this->map[0][1] = 4;
	this->map[0][2] = 8;
	this->map[0][3] = 16;
	this->map[1][0] = 32;
	this->map[1][1] = 64;
	this->map[1][2] = 128;
	this->map[1][3] = 256;
	this->map[2][0] = 512;
	this->map[2][1] = 1024;
	this->map[2][2] = 2048;*/
	this->createBlack();
	this->display(UP);
}

void Game::updataSFMLEvent()
{
	while (this->window.pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
		{
			this->window.close();
		}break;
		case sf::Event::KeyPressed:
		{
			sf::Keyboard::Key kc = this->event.key.code;

			if (kc == sf::Keyboard::Left || kc == sf::Keyboard::A)
				this->move(LEFT);
			else if (kc == sf::Keyboard::Right || kc == sf::Keyboard::D)
				this->move(RIGHT);
			else if (kc == sf::Keyboard::Up || kc == sf::Keyboard::W)
				this->move(UP);
			else if (kc == sf::Keyboard::Down || kc == sf::Keyboard::S)
				this->move(DOWN);
		}break;

		default:
			break;
		}
	}
}

void Game::render()
{
	this->window.clear(sf::Color(187, 173, 160, 255));

	for (size_t y = 0; y < set::SquaresNum_Y; y++)
	{
		for (size_t x = 0; x < set::SquaresNum_X; x++)
		{
			this->shape.setFillColor(this->getTileColor(this->map[y][x]));
			this->shape.setPosition(x * set::BlockWidth, y * set::BlockHeight);
			sf::Text text;
			text.setFont(this->font);
			text.setCharacterSize(this->getTextSize(this->map[y][x]));
			text.setFillColor(this->getTextColor(this->map[y][x]));
			if (this->map[y][x] == 0)
				text.setString(" ");
			else
				text.setString(std::to_string(this->map[y][x]));

			text.setOrigin(text.getGlobalBounds().left, text.getGlobalBounds().top);
			text.setPosition
			(
				(this->shape.getGlobalBounds().width - text.getGlobalBounds().width) / 2.f + this->shape.getGlobalBounds().left,
				(this->shape.getGlobalBounds().height - text.getGlobalBounds().height) / 2.f + this->shape.getGlobalBounds().top
			);
			this->window.draw(this->shape);
			this->window.draw(text);
		}
	}

	this->window.display();
}

void Game::updata()
{
	this->dt = this->clock.restart().asSeconds();
	this->updataSFMLEvent();
}

void Game::display(Dir dir)
{
	std::cout << "\n";
	for (size_t y = 0; y < set::SquaresNum_Y; y++)
	{
		std::cout << "|";
		for (size_t x = 0; x < set::SquaresNum_X; x++)
		{
			std::cout << this->map[y][x] << "\t";
		}
		if (y != set::SquaresNum_X - 1)
		{
			std::cout << "|\n";
		}
		else
		{
			switch (dir)
			{
			case UP:
				std::cout << "¡ü";
				break;
			case DOWN:
				std::cout << "¡ý";
				break;
			case LEFT:
				std::cout << "¡û";
				break;
			case RIGHT:
				std::cout << "¡ú";
				break;
			default:
				break;
			}
			std::cout << "\n";
		}
	}
}

void Game::move(Dir dir)
{
	int temp_map[set::SquaresNum_Y][set::SquaresNum_X] = { 0 };

	// copy map
	for (int y = 0; y < set::SquaresNum_Y; y++)
	{
		for (int x = 0; x < set::SquaresNum_X; x++)
		{
			temp_map[y][x] = this->map[y][x];
		}
	}

	switch (dir)
	{
	case UP:
	{
		this->rotateMap();
		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			this->starkLeft(this->map[y], set::SquaresNum_X);
		}

		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			for (int x = 0; x < set::SquaresNum_X; x++)
			{
				if (this->map[y][x] == 0) continue;
				if (x != set::SquaresNum_X - 1)
				{
					if (this->map[y][x + 1] == this->map[y][x])
					{
						this->map[y][x] *= 2;
						this->map[y][x + 1] = 0;
					}
				}
			}
		}

		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			this->starkLeft(this->map[y], set::SquaresNum_X);
		}
		this->rotateMap();
		this->rotateMap();
		this->rotateMap();
	}break;
	case DOWN:
	{
		this->rotateMap();
		this->rotateMap();
		this->rotateMap();
		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			this->starkLeft(this->map[y], set::SquaresNum_X);
		}
		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			for (int x = 0; x < set::SquaresNum_X; x++)
			{
				if (this->map[y][x] == 0) continue;
				if (x != set::SquaresNum_X - 1)
				{
					if (this->map[y][x + 1] == this->map[y][x])
					{
						this->map[y][x] *= 2;
						this->map[y][x + 1] = 0;
					}
				}
			}
		}
		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			this->starkLeft(this->map[y], set::SquaresNum_X);
		}
		this->rotateMap();
	}break;
	case LEFT:
	{
		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			this->starkLeft(this->map[y], set::SquaresNum_X);
		}
		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			for (int x = 0; x < set::SquaresNum_X; x++)
			{
				if (this->map[y][x] == 0) continue;
				if (x != set::SquaresNum_X - 1)
				{
					if (this->map[y][x + 1] == this->map[y][x])
					{
						this->map[y][x] *= 2;
						this->map[y][x + 1] = 0;
					}
				}
			}
		}
		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			this->starkLeft(this->map[y], set::SquaresNum_X);
		}
	}break;
	case RIGHT:
	{
		this->rotateMap();
		this->rotateMap();
		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			this->starkLeft(this->map[y], set::SquaresNum_X);
		}
		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			for (int x = 0; x < set::SquaresNum_X; x++)
			{
				if (this->map[y][x] == 0) continue;
				if (x != set::SquaresNum_X - 1)
				{
					if (this->map[y][x + 1] == this->map[y][x])
					{
						this->map[y][x] *= 2;
						this->map[y][x + 1] = 0;
					}
				}
			}
		}
		for (int y = 0; y < set::SquaresNum_Y; y++)
		{
			this->starkLeft(this->map[y], set::SquaresNum_X);
		}
		this->rotateMap();
		this->rotateMap();
	}break;

	default:
		break;
	}

	bool isSame = true;

	for (int y = 0; y < set::SquaresNum_Y; y++)
	{
		for (int x = 0; x < set::SquaresNum_X; x++)
		{
			if (temp_map[y][x] != this->map[y][x])
				isSame = false;
		}
	}

	if(isSame == false)
		this->createBlack();
	this->display(dir);
}

Game::Game()
{
	this->initWindow();
	
}

void Game::createBlack()
{
	bool count = true;
	while (count)
	{
		int tempX = rand() % set::SquaresNum_X;
		int tempY = rand() % set::SquaresNum_Y;
		if (this->map[tempY][tempX] != 0) continue;
		count = false;
		int temp = rand() % 10;
		if (temp == 0)
			this->map[tempY][tempX] = 4;
		else 
			this->map[tempY][tempX] = 2;
	}
}

Game::~Game()
{
}

void Game::starkLeft(int array[], const int size)
{
	int* temp_map = new int[size]();
	int count = 0;
	for (int x = 0; x < size; x++)
	{
		if (array[x] != 0)
		{
			temp_map[count++] = array[x];
		}
	}
	count = 0;
	for (int x = 0; x < size; x++)
	{
		array[x] = temp_map[count++];
	}
	delete[] temp_map;
}

// ÄæÊ±ÕëÐý×ª90¶È
void Game::rotateMap()
{
	int temp_map[set::SquaresNum_Y][set::SquaresNum_X];
	for (size_t y = 0; y < set::SquaresNum_Y; y++)
	{
		for (size_t x = 0; x < set::SquaresNum_X; x++)
		{
			temp_map[y][x] = this->map[x][set::SquaresNum_Y - y - 1];
		}
	}
	// copy map
	for (size_t y = 0; y < set::SquaresNum_Y; y++)
		for (size_t x = 0; x < set::SquaresNum_X; x++)
			this->map[y][x] = temp_map[y][x];
}

int Game::getTextSize(int tile)
{
	if (tile >= 1024)
		return 50;
	else if (tile >= 128)
		return 60;
	else
		return 80;
}

sf::Color Game::getTileColor(int tile)
{
	static const sf::Color colors[] = {
		sf::Color(214, 205, 196, 255),		// empty
		sf::Color(238, 228, 218),			// 2^1 == 2
		sf::Color(236, 224, 200),			// 2^2 == 4
		sf::Color(242, 177, 121),			// 2^3 == 8
		sf::Color(245, 149, 99),			// 2^4 == 16
		sf::Color(246, 124, 95),			// 2^5 == 32
		sf::Color(246, 94, 59),				// 2^6 == 64
		sf::Color(237, 207, 114),			// 2^7 == 128
		sf::Color(237, 204, 97),			// 2^8 == 256
		sf::Color(237, 200, 80),			// 2^9 == 512
		sf::Color(237, 197, 63),			// 2^10 == 1024
		sf::Color(237, 194, 46),			// 2^11 == 2048
	};
	int temp = 0;
	if (tile != 0)
		temp = (int)log2((float)tile);
	else
		temp = 0;
	return colors[temp];
}

sf::Color Game::getTextColor(int tile)
{
	if (tile >= 8) // tile >= 8 (cuz 2^3 == 8)
		return sf::Color(249, 246, 242);
	return sf::Color(119, 110, 101);
}

void Game::run()
{
	while (this->window.isOpen())
	{
		this->updata();
		this->render();
	}
}

