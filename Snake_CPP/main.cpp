//////////////////////////////////////////////////////////
//														//
//				Snake game written in C++				//
//				Using the SFML Library					//
//														//
//////////////////////////////////////////////////////////


#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "Fruit.h"
#include "Snake.h"
#include "Particle.h"
#include "utils.h"



int main()
{
	// AA is useless, just in case at some point I add circles or whatever...
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	// Create the window
	sf::RenderWindow window(sf::VideoMode(SIZE_WINDOW, SIZE_WINDOW), "Snake Game", sf::Style::Default, settings);
	window.setFramerateLimit(60);	// Set 60 FPS

	// Create Snake, Fruit and Particles container
	Snake snake = Snake();
	snake.update();
	std::vector<sf::Vector2f> snake_body;

	Fruit fruit = Fruit();
	fruit.update();

	std::vector<Particle> particles;

	bool direction_updated = false;	// Avoid changing direction multiple times between 2 Snake updates
	int frame_count = 0;			// Sync the update of the snake on 1/5 frame rendering
	int clean_count = 0;			// Index for the particles to clean

	// Run the program as long as the window is open
	while (window.isOpen())
	{
		auto start = std::chrono::steady_clock::now();
		frame_count++;	// Update frame sync (for snake update)

		// Check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			// Arrow keys detection
			if (direction_updated == false) {	// Used to avoid multiple directional changes
				if (event.type == sf::Event::KeyPressed)
				{
					// For each key, if the direction is not the opposite to the pressed key:
					// Update the direction of the snake to the corresponding key
					// Lock the update possibility until the snake is updated
					switch (event.key.code)
					{
					case(sf::Keyboard::Up):
						if (snake.direction != Direction::Down) {
							snake.direction = Direction::Up;
							direction_updated = true;
						}
						break;
					case(sf::Keyboard::Down):
						if (snake.direction != Direction::Up) {
							snake.direction = Direction::Down;
							direction_updated = true;
						}
						break;
					case(sf::Keyboard::Left):
						if (snake.direction != Direction::Right) {
							snake.direction = Direction::Left;
							direction_updated = true;
						}
						break;
					case(sf::Keyboard::Right):
						if (snake.direction != Direction::Left) {
							snake.direction = Direction::Right;
							direction_updated = true;
						}
						break;
					}
				}
			}
		}

		// Clear the window with black color
		window.clear(sf::Color::Black);

		// Every 6 frames the Snake is updated ; this could be a global parameter...
		if (frame_count == 5) {
			snake.update();					// Updating the Snake state (position...)
			direction_updated = false;		// Unlock the direction change possibility
			snake_body = snake.get_body();	// We get a copy of the body in order to calculate collisions and particles emission

			for (int i(0); i < snake_body.size(); i++) {					// This loop is to check the collision of the head with the body
				if (i != 0) {
					if (snake.get_head() == snake_body[i]) {
						for (int k(0); k < PARTICLES_NUMBER; k++) {			// This loop generates the amount of particles fixed in utils.h
							for (int l(0); l < snake_body.size(); l++) {	// And this loops generate these particles for each part of the body
								particles.insert(particles.begin(), Particle(snake_body[l], sf::Color::Green));
							}
						}
						snake.refresh();
						break;
					}
				}
			}

			if (snake.get_head() == fruit.get_pos()) {			// If the position of the head and the fruit are equals, then the snake eats the fruit
				for (int k(0); k < PARTICLES_NUMBER; k++) {		// Generate fruit particles
					particles.insert(particles.begin(), Particle(fruit.get_pos(), sf::Color::Red));
				}
				fruit.update();									// Changes the fruit position
				snake.grow_snake();								// Tells the Snake to not pop its last element on the next update
			}

			frame_count = 0;									// We can reset the counter to wait another 6 frames
		}

		// Draw the Snake, the Fruit and the eventual Particles
		snake.render(window);
		fruit.render(window);

		for (int i(0); i < particles.size(); i++) {
			particles[i].update();
			particles[i].render(window);
		}

		clean_count = particles.size() - 1;	// Set clean count to last (oldest) particle in the array

		// Deletes all the elements that are older than 15 ticks
		// The Particle vector is a FIFO array
		if (particles.size() > 0) {
			while (particles[clean_count].get_timer() > 15) {
				clean_count--;
				particles.pop_back();
				if (particles.size() == 0)
					break;
			}
		}


		// end the current frame
		window.display();
	}

	return 0;
}