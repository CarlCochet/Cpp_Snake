#pragma once
#include <random>
#include <iostream>

// Enumeration that defines all possible directions for the Snake (not used by Particles that can go anywhere)
enum Direction {
	Right,
	Left,
	Up,
	Down
};

const int SIZE_WINDOW = 800;						// Size of the window (width = height = SIZE_WINDOW)
const int SIZE_SQUARE = 50;							// Size of a Snake body part (and Fruit size)
const int SIZE_GRID = SIZE_WINDOW / SIZE_SQUARE;	// Not used: ratio defining the size of the grid
const int PARTICLES_NUMBER = 10;					// Amount of Particles launched on particular events
const int SPEED_RANGE = 8000;						// Initial speed range of the particles (SPEED_RANGE => [-SPEED_RANGE/2000..SPEED_RANGE/2000] pixels/tick)
													// Ex: SPEED_RANGE = 8000 => [-4..4] pixels/tick

int randint(int a, int b);							// Wrapper around the mt19937 algorithm provided by the standard lib