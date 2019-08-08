#include "Snake.h"

// Creates the initial Snake state
Snake::Snake()
{
	grow = false;
	body.insert(body.begin(), sf::Vector2f(0,0));

	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(SIZE_SQUARE, SIZE_SQUARE));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(sf::Vector2f(body[0].x, body[0].y));
	shapes.insert(shapes.begin(), shape);

	direction = Direction::Right;
}

Snake::~Snake()
{
}

// Manages the movement of the snake and the creation of shapes
void Snake::update()
{
	// Generate movement from direction
	switch (direction) {
	case (Direction::Up):
		body.insert(body.begin(), sf::Vector2f(body[0].x, body[0].y - 50));
		break;
	case (Direction::Down):
		body.insert(body.begin(), sf::Vector2f(body[0].x, body[0].y + 50));
		break;
	case (Direction::Left):
		body.insert(body.begin(), sf::Vector2f(body[0].x - 50, body[0].y));
		break;
	case (Direction::Right):
		body.insert(body.begin(), sf::Vector2f(body[0].x + 50, body[0].y));
		break;
	}

	// If the head goes out of the window, wrap around 
	if (body[0].x < 0)
		body[0].x = (SIZE_WINDOW - SIZE_SQUARE);
	if (body[0].x > (SIZE_WINDOW - SIZE_SQUARE))
		body[0].x = 0;
	if (body[0].y < 0)
		body[0].y = (SIZE_WINDOW - SIZE_SQUARE);
	if (body[0].y > (SIZE_WINDOW - SIZE_SQUARE))
		body[0].y = 0;
	
	// Set body color
	shapes[0].setFillColor(sf::Color::Green);

	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(SIZE_SQUARE, SIZE_SQUARE));
	shape.setFillColor(sf::Color::Yellow);					// Changes the color to distinguish the head
	shape.setPosition(sf::Vector2f(body[0].x, body[0].y));	// Uses head position to define new shape
	shapes.insert(shapes.begin(), shape);

	// If the grow attribute is true, it means we want the Snake to grow so we do not pop the last element
	if (!grow) {
		body.pop_back();
		shapes.pop_back();
	}
	else {
		grow = false;
	}

}

// Renders the shapes of the Snake
void Snake::render(sf::RenderWindow& window)
{
	for (int i(0); i < shapes.size(); i++) {
		window.draw(shapes[i]);
	}
}

// Required to detect collision with the fruit in main
sf::Vector2f Snake::get_head()
{
	return body[0];
}

// Required to manage particles apparition in main
std::vector<sf::Vector2f> Snake::get_body()
{
	return body;
}

void Snake::grow_snake()
{
	grow = true;
}

// Puts the Snake back to its original shape and position
void Snake::refresh()
{
	body.clear();
	shapes.clear();
	grow = false;
	direction = Direction::Right;

	body.insert(body.begin(), sf::Vector2f(0, 0));

	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(SIZE_SQUARE, SIZE_SQUARE));
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(sf::Vector2f(body[0].x, body[0].y));
	shapes.insert(shapes.begin(), shape);
}
