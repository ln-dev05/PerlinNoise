#include <iostream>

using namespace std;

enum {WATER, NORMAL, MOUTAIN};
char SYMBOLS = {"_', '#', 'n'};

struct Coord {
	int x, y, z;
	Coord(int x, int y, int z) : x(x), y(y), z(z) {}
};

struct Map {
	Coord player;
	int * map;
	int h, w;
	Map(int h, int w, Coord player): h(h), w(w), player(player) {
		map = new int[h*w];
	}
	void out() {
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {	
				if (j == player.x && i == player.y) cout << "* ";
				else cout << map[i * w + j] << " ";
			}
			cout << "" << endl;
		}
	}
};

int main(int argc, char **argv) {
	Coord player(1, 2, 0);
	Map map(10, 10, player);
	map.out();
}
