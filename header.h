#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
using namespace sf;
using namespace std;

const int WIDTH = 23;
const int HEIGHT = 23;
const int CELL_SIZE = 35; // Size of each cell in pixels
const int topSpace = 2;
const int bottomSpace = 2;
const int mazeLayout[HEIGHT][WIDTH] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
	{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
	{0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, //
	{0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void drawMaze(RenderWindow &window)
{
	// Create shapes for cells
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));

	// Draw maze
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			cell.setPosition(j * CELL_SIZE, (i + topSpace) * CELL_SIZE);
			if (mazeLayout[i][j] == 1)
			{
				cell.setFillColor(sf::Color::Black); // Wall
				window.draw(cell);
				if (j > 0 && mazeLayout[i][j - 1] == 0)
				{
					// Draw left outline
					sf::Vertex leftOutline[] = {
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, ((i + topSpace) + 1) * CELL_SIZE), sf::Color::Blue)};
					window.draw(leftOutline, 2, sf::Lines);
				}
				if (j < (WIDTH - 1) && mazeLayout[i][j + 1] == 0)
				{
					// Draw right outline
					sf::Vertex rightOutline[] = {
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, ((i + topSpace) + 1) * CELL_SIZE), sf::Color::Blue)};
					window.draw(rightOutline, 2, sf::Lines);
				}
				if (i > 0 && mazeLayout[i - 1][j] == 0)
				{
					// Draw top outline
					sf::Vertex topOutline[] = {
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue)};
					window.draw(topOutline, 2, sf::Lines);
				}
				if (i < (HEIGHT - 1) && mazeLayout[i + 1][j] == 0)
				{
					// Draw bottom outline
					sf::Vertex bottomOutline[] = {
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, ((i + topSpace) + 1) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, ((i + topSpace) + 1) * CELL_SIZE), sf::Color::Blue)};
					window.draw(bottomOutline, 2, sf::Lines);
				}
			}
			else
			{
				cell.setFillColor(sf::Color{16, 16, 16}); // Empty space
				window.draw(cell);
			}
		}
	}
    //cout<<mazeLayout[8][21];
}

class Score
{
public:
	long long int val;
	string type;
	sf::Text text;
	sf::Font font;
	Score()
	{
		val = 0;
		if (!font.loadFromFile("arial.ttf"))
		{ // Load a font file for displaying text
			std::cerr << "Failed to load font!" << std::endl;
			return;
		}
		text.setFont(font);					 // Set the font for the text
		text.setCharacterSize(24);			 // Set the character size
		text.setFillColor(sf::Color::White); // Set the text color
		text.setPosition(10, 10);			 // Set the position of the text
		updateText();						 // Update the text initially
	}
	void update(int v)
	{
		val += v;
		updateText(); // Update the text whenever the score changes
	}

	void draw(sf::RenderWindow &window)
	{
		window.draw(text);
	}

private:
	void updateText()
	{
		text.setString("Score: " + std::to_string(val)); // Set the text content
	}
};


class Ghost
{
public:
	int x;
	int y;
	int current_path;
	Texture spriteTexture;
	Texture blueTexture;
	Sprite sprite;
	Clock clock;
	float moveInterval;
	float delay; // New member variable for delay
	bool left = true;
	bool hasKey;
	bool hasPermit;
	int ghostnum;
	bool dead;
	string OrigSprite;
	bool isBlue;

	Ghost(string path, float delay,int ghostnum) : delay(delay),ghostnum(ghostnum)
	{ // Constructor updated to accept delay
		OrigSprite =path;
		hasKey=hasPermit=isBlue=false;
		dead=false;
		if (!spriteTexture.loadFromFile(path))
		{
			std::cerr << "Failed to load sprite texture!" << std::endl;
			return;
		}
		if (!blueTexture.loadFromFile("pacman-art/ghosts/blue_ghost.png"))
		{
			std::cerr << "Failed to load sprite texture!" << std::endl;
			return;
		}

		sprite.setTexture(spriteTexture);
		if(ghostnum==0){
			x=9;
		}
		else if(ghostnum==1){
			x=10;
		}
		else if(ghostnum=2){
			x=11;
		}
		else
			x=12;
		y = 11;
		sprite.setScale(2.0f, 2.0f);
		updatePosition();
		current_path = 0;
		moveInterval = 0.2f;
	}
	void defaultPos(){
		if(ghostnum==0){
			x=9;
		}
		else if(ghostnum==1){
			x=10;
		}
		else if(ghostnum=2){
			x=11;
		}
		else
			x=12;
		y = 11;
		updatePosition();
	}
	void changeSprite(string val){
		if(val=="blue"){
			sprite.setTexture(blueTexture);
			isBlue=true;
		}
		else{
			sprite.setTexture(spriteTexture);
			isBlue=false;
		}
	}
	void updatePosition()
	{
		float xPos = CELL_SIZE * x + CELL_SIZE / 2 - sprite.getGlobalBounds().width / 2;
		float yPos = CELL_SIZE * (y + topSpace) + CELL_SIZE / 2 - sprite.getGlobalBounds().height / 2;
		sprite.setPosition(xPos, yPos);
	}

	void draw(RenderWindow &window)
	{
		window.draw(sprite);
	}

	void Path()
	{
		// Add delay before moving
		if (clock.getElapsedTime().asSeconds() < delay)
		{
			return; // Skip movement if delay hasn't elapsed yet
		}

		if (clock.getElapsedTime().asSeconds() >= moveInterval + delay)
		{

			if ((x == 11 && y == 11) || (x == 11 && y == 10))
			{
				y--;
			}
			else if(y==11 ){
				if(x==9)
				x++;
				else if(x==10)
				x++;
			}
			else
			{
				if (x == 7)
					left = false;
				if (x == 15 && y == 9)
				{
					left = true;
				}
				if (left)
				{
					x--;
				}
				else if (!left)
					x++;
			}

			updatePosition();
			clock.restart();
		}
	}
};


class Pacman
{
public:
	int x;
	int y;
	sf::Sprite sprite;
	sf::Texture spriteTextureUp;
	sf::Texture spriteTextureDown;
	sf::Texture spriteTextureLeft;
	sf::Texture spriteTextureRight;
	Texture right_transition_1;
	Texture right_transition_2;
	Texture left_transition_1;
	Texture left_transition_2;
	Texture up_transition_1;
	Texture up_transition_2;
	Texture down_transition_1;
	Texture down_transition_2;
	string active;
	sf::Keyboard::Key direction; // Direction of movement
	bool isTransitioning;
	sf::Clock transitionClock;
	Clock clock;
	float moveInterval;
	int TRANSITION_DURATION;
	Pacman()
	{

		if (!spriteTextureUp.loadFromFile("pacman-art/pacman-up/up.png") ||
			!spriteTextureDown.loadFromFile("pacman-art/pacman-down/down.png") ||
			!spriteTextureLeft.loadFromFile("pacman-art/pacman-left/left.png") ||
			!spriteTextureRight.loadFromFile("pacman-art/pacman-right/right.png"))
		{
			std::cerr << "Failed to load sprite texture!" << std::endl;
			active = "";
			return;
		}
		if (!right_transition_1.loadFromFile("pacman-art/pacman-right/2.png") ||
			!right_transition_2.loadFromFile("pacman-art/pacman-right/3.png") ||
			!left_transition_1.loadFromFile("pacman-art/pacman-left/2.png") ||
			!left_transition_2.loadFromFile("pacman-art/pacman-right/3.png") ||
			!up_transition_1.loadFromFile("pacman-art/pacman-up/2.png") ||
			!up_transition_2.loadFromFile("pacman-art/pacman-up/3.png") ||
			!down_transition_1.loadFromFile("pacman-art/pacman-down/2.png") ||
			!down_transition_2.loadFromFile("pacman-art/pacman-down/3.png"))

			sprite.setTexture(spriteTextureRight);
		x = 1;
		y = 1;
		sprite.setScale(2.0f, 2.0f);

		TRANSITION_DURATION = 3;
		moveInterval = 0.1f;
		updatePosition();
	}

	bool handleEvent(sf::Event &event)
	{
		// cout<<"in handle event"<<endl;
		bool pressed = false;
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				sprite.setTexture(spriteTextureUp);
				direction = sf::Keyboard::Up;
				break;
			case sf::Keyboard::Down:
				sprite.setTexture(spriteTextureDown);
				direction = sf::Keyboard::Down;
				break;
			case sf::Keyboard::Left:
				sprite.setTexture(spriteTextureLeft);
				direction = sf::Keyboard::Left;
				break;
			case sf::Keyboard::Right:
				sprite.setTexture(spriteTextureRight);
				direction = sf::Keyboard::Right;
				// cout<<"right"<<endl;
				break;
			default:
				break;
			}
		}

		if (pressed)
			return true;
		else
			return false;
	}
	//
	void move_in_same_Direction()
	{
		if (clock.getElapsedTime().asSeconds() >= moveInterval)
		{

			if (direction == sf::Keyboard::Up && mazeLayout[y - 1][x] != 0)
			{
				y -= 1;
			}
			else if (direction == sf::Keyboard::Down && mazeLayout[y + 1][x] != 0)
			{
				y += 1;
			}
			else if (direction == sf::Keyboard::Left)
			{
				if (x == 0 && y == 11)
				{
					x = 22; // teleportation
				}
				else if (mazeLayout[y][x - 1] != 0)
				{
					x -= 1;
				}
			}
			else if (direction == sf::Keyboard::Right)
			{
				if (y == 11 && x == 22)
				{
					x = 0; // teleportation
				}
				else if (mazeLayout[y][x + 1] != 0)
				{
					x += 1;
				}
			}
			updatePosition();
			clock.restart();
		}
	}

	void updatePosition()
	{

		float xPos = CELL_SIZE * x + CELL_SIZE / 2 - sprite.getGlobalBounds().width / 2;
		float yPos = CELL_SIZE * (y + topSpace) + CELL_SIZE / 2 - sprite.getGlobalBounds().height / 2;
		sprite.setPosition(xPos, yPos);
	}
	void GhostCollision(Ghost ghosts[4])
	{
		for (int i = 0; i < 4; i++)
		{
			if (x == ghosts[i].x && y == ghosts[i].y && ghosts[i].isBlue==false)
			{
				x = 1;
				y = 3;
				updatePosition();
			}
			else if(ghosts[i].isBlue){
				ghosts[i].x=11;
				ghosts[i].y=11;
				ghosts[i].hasKey=false;
				ghosts[i].hasPermit=false;
			}
		}
	}

	void draw(sf::RenderWindow &window)
	{
		window.draw(sprite);
	}
};


class Food
{
public:
	vector<Sprite> sprites;
	Texture texture;
	int x;
	int y;
	int total;
	int **coord;
	Score &score;
	Food(Score &score) : score(score)
	{
		total = 5;
		coord = new int *[total];
		for (int i = 0; i < total; i++)
		{
			coord[i] = new int[2];
		}
		if (!texture.loadFromFile("sprites/cherry.png"))
		{
			std::cerr << "Failed to load sprite texture!" << std::endl;
			return;
		}
		Sprite sprite;
		sprite.setTexture(texture);
		sprite.setScale(0.0625, 0.0625);
		// sprite.setScale(0.03125, 0.03125);
		int i = 0;
		while (i < total)
		{
			bool flag=false;
			x = rand() % 21 + 1;
			y = rand() % 21 + 1;
			if(y==11){
				if(x>=9 && x<=13){
					flag=true;
				}
				
			}
			if(y==10 && x==11)
				flag=true;
			cout<<"x = "<<x<<" , y= "<<y<<endl;
            cout <<mazeLayout[x][y]<<endl;
			if (mazeLayout[y][x] == 1 && flag==false)
			{

				float xPos = CELL_SIZE * x + CELL_SIZE / 2 - sprite.getGlobalBounds().width / 2;
				float yPos = CELL_SIZE * (y + topSpace) + CELL_SIZE / 2 - sprite.getGlobalBounds().height / 2;
				sprite.setPosition(xPos, yPos);
				coord[i][0] = x;
				coord[i][1] = y;
				sprites.push_back(sprite);
				i++;
			}
		}
		cout << "\narray" << endl;
		for (int i = 0; i < total; i++)
		{
			cout << coord[i][0] << " " << coord[i][1] << endl;
		}
	}

	void draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			// if (i == 0)
			// 	cout << "food class: " << sprites[i].getPosition().x << " , " << sprites[i].getPosition().y << endl;
			window.draw(sprites[i]);
		}
	}
	void Eat(Pacman &pacman)
	{
		for (int i = 0; i < 4; i++)
		{

			if (pacman.x == coord[i][0] && pacman.y == coord[i][1])
			{
				score.update(10);
				// cout << "equal" << endl;
				//  food.sprites.erase(i);
				sprites[i].setPosition(-500, -500);
				coord[i][0] = -500;
				coord[i][1] = -500;
			}
		}
	}
};

class Dots
{
public:
	int **dots;
	vector<Sprite> sprites;
	Texture texture;
	Score &score;
	Pacman &pacman;
	int x;
	int y;
	Dots(Pacman &pacman, Ghost ghosts[], Score &score) : score(score), pacman(pacman)
	{
		if (!texture.loadFromFile("sprites/food.png"))
		{
			std::cerr << "Failed to load sprite texture!" << std::endl;
			return;
		}

		dots = new int *[WIDTH];
		int count = 0;
		for (int i = 0; i < WIDTH; i++)
		{
			dots[i] = new int[HEIGHT];
			for (int j = 0; j < HEIGHT; j++)
			{
				if ((i == pacman.y && j == pacman.x) || mazeLayout[i][j] == 0)
				{
					dots[i][j] = 0;
					continue;
				}
				bool ghost_check = false;
				for (int k = 0; k < 4; k++)
				{
					if (ghosts[k].y == i && ghosts[k].x == j)
						ghost_check = true;
				}
				if (ghost_check)
					continue;

				dots[i][j] = 1;
				Sprite sprite;
				sprite.setTexture(texture);
				sprite.setScale(0.03125, 0.03125);

				float xPos = CELL_SIZE * j + CELL_SIZE / 2 - sprite.getGlobalBounds().width / 2;
				float yPos = CELL_SIZE * (i + topSpace) + CELL_SIZE / 2 - sprite.getGlobalBounds().height / 2;
				sprite.setPosition(xPos, yPos);

				sprites.push_back(sprite);
				x = 0;
				y = 11;
				count++;
			}
		}
	}
	bool collisionDots()
	{
		for (int i = 0; i < WIDTH; i++)
		{
			for (int j = 0; j < HEIGHT; j++)
			{
				if (pacman.x == j && pacman.y == i)
				{
					if (dots[i][j] == 1)
					{
						score.update(1);
						dots[i][j] = 0;
						// Find and erase the corresponding sprite
						for (auto it = sprites.begin(); it != sprites.end(); ++it)
						{
							sf::Vector2f spritePos = it->getPosition();
							int spriteX = spritePos.x / CELL_SIZE;	   // Assuming CELL_SIZE is the size of each cell
							int spriteY = ((spritePos.y) / CELL_SIZE); // row number

							if (spriteX == j && spriteY == i + topSpace)
							{
								it = sprites.erase(it);
								pacman.isTransitioning = true;
								pacman.transitionClock.restart();
								return true;
							}
						}
					}
				}
			}
		}
	}

	void draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < sprites.size(); i++)
			window.draw(sprites[i]);
	}
};

class Lives
{
public:
	int lives;
	Sprite sprite;
	Texture texture;
	Lives()
	{
		lives = 5;
	}
};
