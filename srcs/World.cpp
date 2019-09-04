#include "World.hpp"
#include <iostream>
World		*World::instance = nullptr;

World::World()
{
	if (World::instance == nullptr)
		instance = this;
	_noise.SetNoiseType(FastNoise::PerlinFractal);
}

World::~World() {}
