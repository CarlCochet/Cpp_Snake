#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "utils.h"

class Particle
{
public:
	Particle(sf::Vector2f pos_square, sf::Color color);	// Creates a Particle
	~Particle();										// Not used: destroys the Particle

	void update();										// Update the state of the Particle
	void render(sf::RenderWindow& window);				// Renders the Particle visual representation to the frame buffer
	int get_timer();									// Returns the timer attribute 

private:
	sf::Vector2f pos;									// Position of the Particle
	sf::Vector2f speed;									// Speed of the Particle
	sf::Vector2f acceleration;							// Acceleration of the Particle

	sf::RectangleShape shape;							// Shape of the Particle
	int timer;											// timer defines the lifetime of a Particle
};

