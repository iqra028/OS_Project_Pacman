#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include<queue>
using namespace sf;
using namespace std;

const int WIDTH = 23;
const int HEIGHT = 23;
const int CELL_SIZE = 35; // Size of each cell in pixels
const int topSpace = 2;
const int bottomSpace = 2;
int mazeLayout[HEIGHT][WIDTH] = {
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
			if (mazeLayout[i][j] !=0)
			{
				cell.setFillColor(sf::Color::Black); // Wall
				window.draw(cell);
				if (j > 0 && mazeLayout[i][j - 1] ==0)
				{
					// Draw left outline
					sf::Vertex leftOutline[] = {
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, ((i + topSpace) + 1) * CELL_SIZE), sf::Color::Blue)};
					window.draw(leftOutline, 2, sf::Lines);
				}
				if (j < (WIDTH - 1) && mazeLayout[i][j + 1] ==0)
				{
					// Draw right outline
					sf::Vertex rightOutline[] = {
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, ((i + topSpace) + 1) * CELL_SIZE), sf::Color::Blue)};
					window.draw(rightOutline, 2, sf::Lines);
				}
				if (i > 0 && mazeLayout[i - 1][j] ==0)
				{
					// Draw top outline
					sf::Vertex topOutline[] = {
						sf::Vertex(sf::Vector2f(j * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue),
						sf::Vertex(sf::Vector2f((j + 1) * CELL_SIZE, (i + topSpace) * CELL_SIZE), sf::Color::Blue)};
					window.draw(topOutline, 2, sf::Lines);
				}
				if (i < (HEIGHT - 1) && mazeLayout[i + 1][j] ==0)
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
	float speed=0.3;
	bool stop_moving=0;
	Ghost(string path, float delay,int ghostnum,float s) : delay(delay),ghostnum(ghostnum),speed(s)
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

	// void Path()
	// {
	// 	// Add delay before moving
	// 	cout<<"Path "<<x<<" "<<y<<endl;
	// 	if (clock.getElapsedTime().asSeconds() < delay)
	// 	{
	// 		return; // Skip movement if delay hasn't elapsed yet
	// 	}

	// 	if (clock.getElapsedTime().asSeconds() >= moveInterval + delay)
	// 	{

	// 		if ((x == 11 && y == 11) || (x == 11 && y == 10))
	// 		{
	// 			y--;
	// 		}
	// 		else if(y==11 ){
	// 			if(x==9)
	// 			x++;
	// 			else if(x==10)
	// 			x++;
	// 		}
	// 		else
	// 		{
	// 			if (x == 7)
	// 				left = false;
	// 			if (x == 15 && y == 9)
	// 			{
	// 				left = true;
	// 			}
	// 			if (left)
	// 			{
	// 				x--;
	// 			}
	// 			else if (!left)
	// 				x++;
	// 		}

	// 		updatePosition();
	// 		clock.restart();
	// 	}
	// }
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
				sem_wait(&reader);
    			readercount++;
    			if (readercount == 1)
        			sem_wait(&writer);
    			sem_post(&reader);
				if(mazeLayout[newY][newX] != 0){
                	q.push({newX, newY});
                	visited[newY][newX] = true;
                	parent[newY][newX] = {curX, curY};
				}
				sem_wait(&reader);
    			readercount--;
    			if (readercount == 0) {
        			sem_post(&writer);
   	 			}
    			sem_post(&reader);
            }
        }
    }
    return {};
}

void moveGhost(int PacmanX, int PacmanY) {
    vector<vector<int>> path;
    if (x != PacmanX || y != PacmanY) 
        path = bfs(PacmanX, PacmanY);
    if (path.empty()) {
        return;
    }
	
    int nextX = path[1][0];
    int nextY = path[1][1];
    if (clock.getElapsedTime().asSeconds() > speed) {
        x = nextX;
        y = nextY;
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
	bool GhostCollision(Ghost ghosts[4])
	{
		for (int i = 0; i < 4; i++)
		{
			if (x == ghosts[i].x && y == ghosts[i].y && ghosts[i].isBlue==false)
			{
				x = 1;
				y = 3;
				updatePosition();
				return false;
			}
			else if(ghosts[i].isBlue){
				ghosts[i].x=11;
				ghosts[i].y=11;
				ghosts[i].hasKey=false;
				ghosts[i].hasPermit=false;
			}
		}
		return true;
	}

	void draw(sf::RenderWindow &window)
{	
    // Get the bounding box of the sprite
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    
    // Create a rectangle shape to cover the area of the sprite
    sf::RectangleShape eraser(sf::Vector2f(spriteBounds.width, spriteBounds.height));
    eraser.setPosition(sprite.getPosition());
    eraser.setFillColor(sf::Color::Black); // Change to your background color
    
    // Erase the area where the sprite was previously drawn
    window.draw(eraser);

    // Draw the sprite
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
	void Eat(Pacman* pacman)
	{
		for (int i = 0; i < 4; i++)
		{

			if (pacman->x == coord[i][0] && pacman->y == coord[i][1])
			{
				score.update(10);
				sprites[i].setPosition(-500, -500);
				coord[i][0] = -500;
				coord[i][1] = -500;
			}
		}
	}
};class PowerPellets
{
public:
    sf::CircleShape circles;
    int x;
    int y;
    int total;
    int *coord;
    bool respawn = false;

    PowerPellets(int x1, int y1) 
    {
        total = 4;
        x = x1;
        y = y1;

        coord = new int[2];
        float radius = 15.0f;
        circles.setRadius(radius);
        circles.setFillColor(sf::Color(255, 165, 0)); 
        float xPos = CELL_SIZE * x + CELL_SIZE / 2 - circles.getGlobalBounds().width / 2;
        float yPos = CELL_SIZE * (y + topSpace) + CELL_SIZE / 2 - circles.getGlobalBounds().height / 2;
        circles.setPosition(xPos, yPos);
        coord[0] = x;
        coord[1] = y;
        
    }
    void Eat(Pacman* pacman)
    {
        for (int i = 0; i < 4; i++)
        {
			//sem_wait(&full_slots);
        //sem_wait(&mutex1);
            if (pacman->x == coord[0] && pacman->y == coord[1])
            {	cout<<"icamerhere"<<endl;
				
                circles.setPosition(-500, -500);
                coord[0] = -500;
                coord[1] = -500;
                respawn = true;
            }
		//	sem_post(&mutex1);
        //sem_post(&empty_slots);
        }
    }
    void setPosition(int x, int y)
    {	cout<<"hohoho"<<endl;
        circles.setPosition(x*CELL_SIZE, y*CELL_SIZE);
        //coord[0] = x;
        //coord[1] = y;
    }
    void draw(sf::RenderWindow &window)
    {	//cout<<x<<" "<<y<<endl;
        window.draw(circles);
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
	bool collisionDots(Pacman * pacman)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			for (int j = 0; j < HEIGHT; j++)
			{
				if (pacman->x == j && pacman->y == i)
				{
					if (dots[i][j] == 1)
					{
						score.update(1);
						dots[i][j] = 0;
						
						sem_wait(&writer);
						mazeLayout[i][j]=2;
						
						sem_post(&writer);
						
						// Find and erase the corresponding sprite
						for (auto it = sprites.begin(); it != sprites.end(); ++it)
						{
							sf::Vector2f spritePos = it->getPosition();
							int spriteX = spritePos.x / CELL_SIZE;	   // Assuming CELL_SIZE is the size of each cell
							int spriteY = ((spritePos.y) / CELL_SIZE); // row number

							if (spriteX == j && spriteY == i + topSpace)
							{
								it = sprites.erase(it);
								pacman->isTransitioning = true;
								pacman->transitionClock.restart();
								return true;
							}
						}
					}
				}
			}
		}
		return false;
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
