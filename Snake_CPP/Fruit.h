#pragma once
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <time.h>

class Fruit
{
public:
	Fruit();								// Creates the Fruit
	~Fruit();								// Not used: destroys the Fruit

	void update();							// Update the state of the Fruit
	void render(sf::RenderWindow &window);	// Renders the Fruit visual representation to the frame buffer
	sf::Vector2f get_pos();					// Returns the position of the Fruit

private:
	sf::Vector2f pos;						// Position of the Fruit using Vector2f
	sf::RectangleShape shape;				// Shape equivalent to pos for the frame rendering
};

