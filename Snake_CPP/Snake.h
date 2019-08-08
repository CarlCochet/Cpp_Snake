#pragma once
#include "utils.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Snake
{
public:
	Snake();								// Creates the Snake
	~Snake();								// Not used: destroys the Snake

	void update();							// Update the state of the Snake
	void render(sf::RenderWindow& window);	// Renders the Snake visual representation to the frame buffer
	sf::Vector2f get_head();				// Returns the first element of the body
	std::vector<sf::Vector2f> get_body();	// Returns the whole body
	void grow_snake();						// Sets the 'grow' attribute to 'true'
	void refresh();							// Sets back all attributes to default value (like in constructor)

	Direction direction;					// Direction is public so you can check its value and change it from main

private:
	std::vector<sf::Vector2f> body;			// Body of the snake composed of Vector2f (which are basically spatial positions)
	std::vector<sf::RectangleShape> shapes;	// Equivalent to body but stores shape for the frame rendering
	bool grow;								// Tells wether the last element must be poped or not when updating Snake position
};

