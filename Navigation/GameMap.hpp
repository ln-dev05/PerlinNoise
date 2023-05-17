#include "PerlinNoise/Map.hpp"
#include "Navigation/Generator.hpp"
#include "Navigation/Coord.hpp"
#include <iostream>

#if !defined(GAME_MAP_HPP)
#define GAME_MAP_HPP

struct GameMap {
	Coord * player;
	int * map;
	int h, w;

	GameMap(int h, int w, Coord * player, Generator * generator);
	int get(const int i, const int j) const;
	void out() const;
};

#endif // GAME_MAP_HPP
