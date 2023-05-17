#include "Navigation/Coord.hpp"
#include "Navigation/GameMap.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

#if !defined(NAVIGATOR_HPP)
#define NAVIGATOR_HPP

class Navigator
{
private:
    Coord * player;
    GameMap * gameMap;
    std::vector<int> layer_capacity;
public:
    Navigator(Coord  *player, GameMap * gameMap, std::vector<int> layer_capacity)
    : player(player), gameMap(gameMap), layer_capacity(layer_capacity) {
        for (auto &i : layer_capacity) std::cout << i << std::endl;
    }

    void handle(char input) {
        Coord cpy = *player;
		switch (input) {
		case 'z':
			cpy.y--;
            break;
		case 's':
			cpy.y++;
            break;
		case 'q':
			cpy.x--;
            break;
		case 'd':
			cpy.x++;
            break;
		}
        int targeted_place = gameMap->get(cpy.x, cpy.y);
        if (std::find(layer_capacity.begin(), layer_capacity.end(), targeted_place) != layer_capacity.end()) {
            *player = cpy;
        }
    }

    ~Navigator() {}
};

#endif // NAVIGATOR_HPP
