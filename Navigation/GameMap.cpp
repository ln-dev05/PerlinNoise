#include "Navigation/GameMap.hpp"

enum {WATER, NORMAL, MOUTAIN};
std::string SYMBOLS[] = {"\033[44m~", "\033[42m_", "\033[47m#"};
unsigned int seuil1, seuil2;
#define SORT(a, SEUIL1, SEUIL2) (a < SEUIL1) ? WATER : ((a > SEUIL2) ? MOUTAIN : NORMAL)

GameMap::GameMap(int h, int w, Coord * player, Generator * generator): h(h), w(w), player(player) {
    map = new int[h*w];
    Map temp = Map(w, h, rand(), 3, 2, 5);
    for (int i = 0; i < h * w; ++i) {
        map[i] = generator->get(i);
    }
}

int GameMap::get(const int i, const int j) const {
    return SORT(map[j * w + i], seuil1, seuil2);
}

void GameMap::out() const {
    std::cout << "" << std::endl;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (j == player->x && i == player->y) std::cout << "\033[41m* \033[0m";
            else std::cout << SYMBOLS[SORT(map[i * w + j], seuil1, seuil2)] << " \033[0m";
        }
        std::cout << "" << std::endl;
    }
}


