#include "World.hpp"
#include <iostream>
//World		World::instance = World();
FastNoise World::out = FastNoise();
FastNoise World::in = FastNoise();
//World		World::instance = World();

World::World() {}

void World::initWorld(int seed)
{
	out.SetSeed(seed);
	in.SetSeed(seed);
	out.SetNoiseType(FastNoise::PerlinFractal);
	in.SetNoiseType(FastNoise::SimplexFractal);
	in.SetFractalType(FastNoise::Billow);
}
World::~World() {}
