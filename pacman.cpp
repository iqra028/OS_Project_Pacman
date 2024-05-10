#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>
#include <queue>
#include <utility>
using namespace std;
using namespace sf;
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
	{0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},//
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
void drawMaze(RenderWindow& window) {
	// Create shapes for cells
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));


	// Draw maze
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			cell.setPosition(j * CELL_SIZE, (i + topSpace) * CELL_SIZE);
			if (mazeLayout[i][j] == 1) {
				cell.setFillColor(sf::Color::Black); // Wall
				window.draw(cell);
				if (j > 0 && mazeLayout[i][j - 1] == 0) {
					// Draw left outline
					sf::Vertex leftOutline[] = {
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, ((i + topSpace) + 1) * CELL_SIZE), sf::Color::Blue)
					};
					window.draw(leftOutline, 2, sf::Lines);
				}
				if (j < (WIDTH - 1) && mazeLayout[i][j + 1] == 0) {
					// Draw right outline
					sf::Vertex rightOutline[] = {
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, ((i + topSpace) + 1) * CELL_SIZE), sf::Color::Blue)
					};
					window.draw(rightOutline, 2, sf::Lines);
				}
				if (i > 0 && mazeLayout[i - 1][j] == 0) {
					// Draw top outline
					sf::Vertex topOutline[] = {
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue)
					};
					window.draw(topOutline, 2, sf::Lines);
				}
				if (i < (HEIGHT - 1) && mazeLayout[i + 1][j] == 0) {
					// Draw bottom outline
					sf::Vertex bottomOutline[] = {
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, ((i + topSpace) + 1) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, ((i + topSpace) + 1) * CELL_SIZE), sf::Color::Blue)
					};
					window.draw(bottomOutline, 2, sf::Lines);
				}
			}
			else {
				cell.setFillColor(sf::Color{ 16,16,16 }); // Empty space
				window.draw(cell);
			}
		}
	}

}

class Ghost {
public:
	int x;
	int y;
	int current_path;
	Texture spriteTexture;
	Sprite sprite;
	Clock clock;
	float moveInterval;
	Ghost(string path) {
		if (!spriteTexture.loadFromFile(path)) {
			std::cerr << "Failed to load sprite texture!" << std::endl;
			return;
		}

		sprite.setTexture(spriteTexture);
		x = 13;
		y = 13;
		sprite.setScale(2.0f, 2.0f);
		updatePosition();
		current_path = 0;
		moveInterval = 0.2f;
	}

	void updatePosition() {
		float xPos = CELL_SIZE * x + CELL_SIZE / 2 - sprite.getGlobalBounds().width / 2;
		float yPos = CELL_SIZE * (y + topSpace) + CELL_SIZE / 2 - sprite.getGlobalBounds().height / 2;
		sprite.setPosition(xPos, yPos);
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}
vector<vector<int>> bfs(int PacmanX, int PacmanY) {
    vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
    vector<vector<vector<int>>> parent(HEIGHT, vector<vector<int>>(WIDTH, vector<int>(2, -1)));
    queue<vector<int>> q;
    q.push({x, y});
    visited[y][x] = true;

    while (!q.empty()) {
        vector<int> current = q.front();
        int curX = current[0];
        int curY = current[1];
        q.pop();
        if (curX == PacmanX && curY == PacmanY) {
            vector<vector<int>> path;
            while (curX != x || curY != y) {
                path.push_back({curX, curY});
                current = parent[curY][curX];
                curX = current[0];
                curY = current[1];
            }
            path.push_back({x, y});
            reverse(path.begin(), path.end());

            return path;
        }
        for (int i = 0; i < directions.size(); ++i) {
            int newX = curX + directions[i][0];
            int newY = curY + directions[i][1];

            if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && !visited[newY][newX]) {
                q.push({newX, newY});
                visited[newY][newX] = true;
                parent[newY][newX] = {curX, curY};
            }
        }
    }
    return {};
}

	void moveGhost(int PacmanX, int PacmanY) {
		vector<vector<int>> path;
		
		path= bfs(PacmanX, PacmanY);
            cout << "Next positions of the ghost: ";
            for (const auto& pos : path) {
                cout << "(" << pos[0] << ", " << pos[1] << ") ";
            }
            cout << endl;
    if (path.empty()) {
        return;
    }

    int nextX = path[1][0];
    int nextY = path[1][1];
    x = nextX;
    y = nextY;
    updatePosition();
}



	

};

class Food {
public:
	vector<Sprite> sprites;
	Texture texture;
	int x;
	int y;
	int total;
	Food() {
		total = 5;
		if (!texture.loadFromFile("sprites/cherry.png")) {
			std::cerr << "Failed to load sprite texture!" << std::endl;
			return;
		}
		Sprite sprite;
		sprite.setTexture(texture);
		sprite.setScale(0.0625, 0.0625);
		//sprite.setScale(0.03125, 0.03125);
		int i = 0;
		while(i<total) {
			x = rand() % 21 + 1;
			y = rand() % 21 + 1;
			
			if (mazeLayout[x][y] == 1) {
				cout << x << " " << y << endl;
				float xPos = CELL_SIZE * x + CELL_SIZE / 2 - sprite.getGlobalBounds().width / 2;
				float yPos = CELL_SIZE * (y + topSpace) + CELL_SIZE / 2 - sprite.getGlobalBounds().height / 2;
				sprite.setPosition(xPos, yPos);

				sprites.push_back(sprite);
				i++;
			}
		
		}

	}
	
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < sprites.size(); i++)
			window.draw(sprites[i]);
	}

};
class Pacman {
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
	Food food;

	Pacman(Food& food):food(food)  {

		if (!spriteTextureUp.loadFromFile("pacman-art/pacman-up/up.png") ||
			!spriteTextureDown.loadFromFile("pacman-art/pacman-down/down.png") ||
			!spriteTextureLeft.loadFromFile("pacman-art/pacman-left/left.png") ||
			!spriteTextureRight.loadFromFile("pacman-art/pacman-right/right.png")) {
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

	bool handleEvent(sf::Event& event) {
		bool pressed = false;
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
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
	void move_in_same_Direction() {
		if (clock.getElapsedTime().asSeconds() >= moveInterval) {

			if (direction == sf::Keyboard::Up && mazeLayout[y - 1][x] != 0) {
				y -= 1;
			}
			else if (direction == sf::Keyboard::Down && mazeLayout[y + 1][x] != 0) {
				y += 1;
			}
			else if (direction == sf::Keyboard::Left) {
				if (x == 0 && y == 11) {
					x = 22; //teleportation
				}
				else if (mazeLayout[y][x - 1] != 0) {
					x -= 1;
				}
			}
			else if (direction == sf::Keyboard::Right) {
				if (y == 11 && x == 22) {
					x = 0; //teleportation
				}
				else if (mazeLayout[y][x + 1] != 0) {
					x += 1;
				}
			}
			updatePosition();
			clock.restart();
		}
	}

	void updatePosition() {

		float xPos = CELL_SIZE * x + CELL_SIZE / 2 - sprite.getGlobalBounds().width / 2;
		float yPos = CELL_SIZE * (y + topSpace) + CELL_SIZE / 2 - sprite.getGlobalBounds().height / 2;
		sprite.setPosition(xPos, yPos);
	}

	void GhostCollision(Ghost ghosts[4]) {
		for (int i = 0; i < 4; i++) {
			if (x == ghosts[i].x && y == ghosts[i].y) {
				x = 1; y = 3;
				updatePosition();
			}
		}
	}
	/// <summary>
	/// 
	/// </summary>
	void Collision() {
    for (int i = food.sprites.size() - 1; i >= 0; --i) {
        if (x == food.sprites[i].getPosition().x && y == food.sprites[i].getPosition().y) {
            food.sprites.erase(food.sprites.begin() + i);
            updatePosition();
        }
    }
}
	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
};

//class Path {
//public:
//	int x;
//	int y;
//	Path(int xpos = 0, int ypos = 0) {
//		x = xpos;
//		y = ypos;
//	}
//};
//
//




class Score {
public:
	long long int val;
	string type;
	sf::Text text;
	sf::Font font;
	Score() {
		val = 0;
		if (!font.loadFromFile("arial.ttf")) { // Load a font file for displaying text
			std::cerr << "Failed to load font!" << std::endl;
			return;
		}
		text.setFont(font); // Set the font for the text
		text.setCharacterSize(24); // Set the character size
		text.setFillColor(sf::Color::White); // Set the text color
		text.setPosition(10, 10); // Set the position of the text
		updateText(); // Update the text initially
	}
	void update() {
		val += 5;
		updateText(); // Update the text whenever the score changes
	}

	void draw(sf::RenderWindow& window) {
		window.draw(text);
	}
private:
	void updateText() {
		text.setString("Score: " + std::to_string(val)); // Set the text content
	}
};

class Dots {
public:
	int** dots;
	vector<Sprite> sprites;
	Texture texture;
	Score& score;
	Pacman& pacman;
	int x;
	int y;
	Dots(Pacman& pacman, Ghost ghosts[], Score& score) : score(score), pacman(pacman) {
		if (!texture.loadFromFile("sprites/food.png")) {
			std::cerr << "Failed to load sprite texture!" << std::endl;
			return;
		}

		dots = new int* [WIDTH];
		int count = 0;
		for (int i = 0; i < WIDTH; i++) {
			dots[i] = new int[HEIGHT];
			for (int j = 0; j < HEIGHT; j++) {
				if ((i == pacman.y && j == pacman.x) || mazeLayout[i][j] == 0) {
					dots[i][j] = 0;
					continue;
				}
				bool ghost_check = false;
				for (int k = 0; k < 4; k++) {
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
	bool PowerPellets() {
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				if (pacman.x == j && pacman.y == i) {
					if (dots[i][j] == 1) {
						score.update();
						dots[i][j] = 0;
						// Find and erase the corresponding sprite
						for (auto it = sprites.begin(); it != sprites.end(); ++it) {
							sf::Vector2f spritePos = it->getPosition();
							int spriteX = spritePos.x / CELL_SIZE; // Assuming CELL_SIZE is the size of each cell
							int spriteY = ((spritePos.y) / CELL_SIZE); //row number

							if (spriteX == j && spriteY == i + topSpace) {
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

	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < sprites.size(); i++)
			window.draw(sprites[i]);
	}
};

class Lives {
public:
	int lives;
	Sprite sprite;
	Texture texture;
	Lives() {
		lives = 5;

	}
};


int main() {
	RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, (HEIGHT + bottomSpace + topSpace) * CELL_SIZE), "Pac-Man Maze");
	Ghost ghosts[4] = {Ghost("pacman-art/ghosts/blinky.png"),Ghost("pacman-art/ghosts/blinky.png"),Ghost("pacman-art/ghosts/blinky.png"),Ghost("pacman-art/ghosts/blinky.png")};
	Food food;

	Pacman pacman(food);
	Score score;
	Dots Dot(pacman, ghosts, score);
	// Main loop
	bool pressed = false;;

	while (window.isOpen()) {
		// Handle events
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			pressed = pacman.handleEvent(event); 
		}
		pacman.move_in_same_Direction();

		ghosts[0].moveGhost(pacman.x,pacman.y);

		pacman.GhostCollision(ghosts);

		window.clear();


		// Draw the maze
		drawMaze(window);

		// Draw Pacman
		pacman.draw(window);

		//Draw Ghost
		ghosts[0].draw(window);

		//Check for power pellets
		bool erased = Dot.PowerPellets();

		//Draw Dots
		Dot.draw(window);

		//Draw Scores
		score.draw(window);

		//Draw food
		food.draw(window);
		// Display the window
		window.display();
	}

	return 0;
}