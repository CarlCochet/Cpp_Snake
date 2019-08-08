#include "Particle.h"

// Creates the initial Particle state
Particle::Particle(sf::Vector2f pos_square, sf::Color color)
{
	timer = 0;

	// Position is deduced from the origin of the event passed by parameter
	pos.x = pos_square.x + 25;
	pos.y = pos_square.y + 25;

	// randint() takes unsigned_int so we have to substract to get possible negative values
	// Also we want float values but randint sends an int so we take big values and divide
	speed.x = (float(randint(0, SPEED_RANGE) - (SPEED_RANGE / 2)) / 1000);
	speed.y = (float(randint(0, SPEED_RANGE) - (SPEED_RANGE / 2)) / 1000);

	// Acceleration is constant but needs to be defined first based on the sign of speed (x and y)
	// Here the acceleration makes Particles slow down
	acceleration.x = speed.x < 0 ? 0.05 : -0.05;
	acceleration.y = speed.y < 0 ? 0.05 : -0.05;

	shape.setPosition(pos);
	shape.setSize(sf::Vector2f(10, 10));
	shape.setFillColor(color);
}

Particle::~Particle()
{
}

// Manages the movement of the Particle
void Particle::update()
{
	// Simple physics: position(t+1) = position(t) + speed(t)
	pos.x += speed.x;
	pos.y += speed.y;

	// Simple physics: speed(t+1) = speed(t) + acceleration(t)
	speed.x += acceleration.x;
	speed.y += acceleration.y;

	shape.setPosition(pos);

	// Timer sets the lifetime: when it reaches 15, the Particle is deleted
	timer++;
}

void Particle::render(sf::RenderWindow& window)
{
	window.draw(shape);
}

int Particle::get_timer()
{
	return timer;
}
