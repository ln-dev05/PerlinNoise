#include <iostream>
#include <unistd.h>


#include "Navigation/GameMap.hpp"
#include "Navigation/Navigator.hpp"
#include "PerlinNoiseGenerator.hpp"
enum {WATER, NORMAL, MOUTAIN};

using namespace std;
extern unsigned int seuil1, seuil2;

int main(int argc, char **argv) {
	seuil1 = atoi(argv[1]);
	seuil2 = atoi(argv[2]);
	srand(getpid());
	Coord player(1, 2, 0);
	GameMap map(20, 20, &player, new PerlinNoiseGenerator(20, 20));
	Navigator navigator(&player, &map, std::vector<int>({NORMAL}));
	char c;
	while (1) {
		map.out();
		cin >> c;
		navigator.handle(c);
	};
}
