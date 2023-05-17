#include <cmath>
#include "ppm.h"
#include "PerlinNoise.h"
#include <iostream>
#include "Gradient.hpp"
#include "Map.hpp"

using namespace std;

int main(int argc, char **argv) {

	unsigned int width = 600, height = 450;
	unsigned int seed = (argc >= 5)? atoi(argv[4]) : 237;
	PerlinNoise pn(seed);

	unsigned int lucanarity = atoi(argv[1]);
	unsigned int persistance = atoi(argv[2]);
	unsigned int octave = atoi(argv[3]);

	const unsigned int threshold = 127;
	Map map = Map::Builder()
	.setHeight(height)
	.setWidth(width)
	.setSeed(seed)
	.setLucanarity(lucanarity)
	.setOctave(octave)
	.setPersistance(persistance)
	.build();

	const ppm img = ppm("elsa_gray.ppm");

	Gradient(&img, 1.f).write("figure_paul.ppm");

	return 0;
}
