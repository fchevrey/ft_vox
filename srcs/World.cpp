#include "World.hpp"
#include <iostream>
World		*World::instance = nullptr;

World::World()
{
	if (World::instance == nullptr)
		instance = this;
	_noise.SetNoiseType(FastNoise::SimplexFractal);
	_noise.SetFrequency(40.0f);
	_noise.SetFractalOctaves(120);
}

World::~World() {}
