#include "Fruit.h"

// Creates the initial Fruit state
Fruit::Fruit()
{
	// Position is randomized through randint()
	pos.x = 50 * (randint(0, 15));
	pos.y = 50 * (randint(0, 15));

	shape.setPosition(pos);
	shape.setSize(sf::Vector2f(SIZE_SQUARE, SIZE_SQUARE));
	shape.setFillColor(sf::Color::Red);
}

Fruit::~Fruit() {}

// Update the Fruit state
void Fruit::update()
{
	// We only change the Fruit position, no need to delete and create another Fruit
	pos.x = 50 * (randint(0, 15));
	pos.y = 50 * (randint(0, 15));

	shape.setPosition(pos);
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape);
}

sf::Vector2f Fruit::get_pos()
{
	return pos;
}
