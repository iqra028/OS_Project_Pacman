#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <mutex>
#include <unistd.h>
#include "header.h"
const int total = 4;
sem_t keys;
sem_t permits;
mutex lock1;

using namespace std;
using namespace sf;

bool exit_window = false;
int score = 0;
bool running = 1;

struct arguments
{
	// Food food;
	Pacman *pacman;
	arguments(Pacman *pac) : pacman(pac)
	{
	}
};

void *userInterfaceThread(void *args)
{
	arguments *arg = *(arguments **)args;
	// Score score;

	// cout<<arg->pacman->x<<" "<<arg->pacman->y<<endl;
	while (running)
	{
		// arg->pacman->handleEvent(arg->event);
	}
	return nullptr;
}
// DINING PHILOSOPHER TECHNIQUE FOR 2 GHOST APPEARANCE AT A TIME

struct ghost_arg
{
	Ghost *ghost;

	ghost_arg(Ghost *ghost) : ghost(ghost)
	{
	}
};

void eat(Ghost *ghost)
{
	lock1.lock();
	//cout << "Ghost " << ghost->ghostnum << " begins to eat" << endl;
	lock1.unlock();
}

// Dining philosopher function
void DP(Ghost *ghost)
{
	while (running)
	{

		// Try to acquire both key and permit
		sem_wait(&keys);
		sem_wait(&permits);

		lock1.lock();
		ghost->hasKey = true;
		ghost->hasPermit = true;
		//cout << "Ghost " << ghost->ghostnum << " has acquired key and permit, starts eating\n";
		lock1.unlock();

		eat(ghost);
		sleep(10); // Simulate eating time

		lock1.lock();
		//cout << "Ghost " << ghost->ghostnum << " has finished eating\n";
		// if (ghost->dead == true)
		// {
			ghost->hasKey = false;
			ghost->hasPermit = false;
			
			ghost->defaultPos();
			ghost->updatePosition();
		// }
		lock1.unlock();

		// Release both key and permit
		sem_post(&keys);
		sem_post(&permits);

		sleep(5); // Wait for a while before attempting to eat again
	}
}

void *ghostControllerThread(void *args)
{
	ghost_arg *arg = (ghost_arg *)args;
	//cout << "Ghost x and y: " << arg->ghost->x << " " << arg->ghost->y << endl;

	while (true)
	{
		DP(arg->ghost);
	}

	return nullptr;
}

void *gameEngineThread(void *args)
{
	pthread_t t[4];
	Score score;
	Pacman pacman;
	RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, (HEIGHT + bottomSpace + topSpace) * CELL_SIZE), "Pac-Man Maze");
	Ghost ghosts[4] = {
		Ghost("pacman-art/ghosts/blinky.png", 0.0f, 1), // No delay
		Ghost("pacman-art/ghosts/clyde.png", 0.5f, 2),	// Delay of 0.5 seconds
		Ghost("pacman-art/ghosts/inky.png", 1.0f, 3),	// Delay of 1 second
		Ghost("pacman-art/ghosts/pinky.png", 1.5f, 4)	// Delay of 1.5 seconds
	};
	Food food(score);

	Dots Dot(pacman, ghosts, score);
	// Main loop
	Event event;
	bool pressed = false;
	// cout<<pacman.x<<" "<<pacman.y<<endl;
	arguments *args1 = new arguments(&pacman);

	pthread_create(&t[0], nullptr, userInterfaceThread, &args1);
	int n[total];
	for (int i = 0; i < 4; ++i)
	{
		ghost_arg *arg = new ghost_arg(&ghosts[i]);
		pthread_create(&t[i], nullptr, ghostControllerThread, arg);
	}
	bool makeGhostsBlue = false;
	while (window.isOpen())
	{
		// static auto lastTime = std::chrono::steady_clock::now();
		// auto currentTime = std::chrono::steady_clock::now();
		// auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime).count();

		// if (elapsedTime >= 5) // Change state every 5 seconds
		// {
		// 	// Toggle the state
		// 	makeGhostsBlue = !makeGhostsBlue;

		// 	// Update the last time
		// 	lastTime = currentTime;
		// }
		// for (int i = 0; i < 4; i++)
        // {
        //     // Change ghost sprites to blue if makeGhostsBlue is true
        //     if (makeGhostsBlue)
        //     {
        //         ghosts[i].changeSprite("blue");
        //     }
        //     else // Revert back to original sprites
        //     {
        //         ghosts[i].changeSprite("revert");
        //     }
        //     ghosts[i].draw(window);
        // }

		// Handle events

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// pthread_mutex_lock(&lock1);
				running = false;
				window.close();
				exit(0);
				// pthread_mutex_unlock(&lock1);
			}
			pacman.handleEvent(event);
		}

		pacman.move_in_same_Direction();

		for (int i = 0; i < 4; i++)
		{
			if (ghosts[i].hasKey && ghosts[i].hasPermit)
				ghosts[i].Path();
		}

		pacman.GhostCollision(ghosts);

		food.Eat(pacman);

		window.clear();

		// Draw the maze
		drawMaze(window);

		// Draw Pacman
		pacman.draw(window);

		// Draw Ghost
		for (int i = 0; i < 4; i++)
		{
			ghosts[i].draw(window);
		}

		// Check for power pellets
		bool erased = Dot.collisionDots();

		// Draw Dots
		Dot.draw(window);

		// Draw Scores
		score.draw(window);

		// Draw food
		food.draw(window);
		// Display the window
		window.display();
	}

	for (int i = 0; i < 4; i++)
	{
		pthread_join(t[i], nullptr);
	}
	return nullptr;
}

int main()
{
	pthread_t t;
	pthread_create(&t, nullptr, gameEngineThread, nullptr);
	sem_init(&keys, 0, 2);	  // Initialize the keys semaphore with 2 keys
	sem_init(&permits, 0, 2); // Initialize the permits semaphore with 2 permits

	pthread_join(t, nullptr);

	sem_destroy(&keys);
	sem_destroy(&permits);
	return 0;
}
