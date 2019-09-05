#include "World.hpp"
#include <iostream>
World		*World::instance = nullptr;

World::World()
{
	if (World::instance == nullptr)
		instance = this;
	_out.SetNoiseType(FastNoise::PerlinFractal);
	_in.SetNoiseType(FastNoise::SimplexFractal);
	_in.SetFractalType(FastNoise::Billow);
}

World::~World() {}
