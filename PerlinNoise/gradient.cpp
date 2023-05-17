#include "Gradient.hpp"
#include "ppm.h"

int main(int argc, char const *argv[])
{
	const ppm img = ppm(argv[1]);
    unsigned int seuil = atoi(argv[2]);
	Gradient(&img, (double) seuil).write("figure_paul.ppm");
    return 0;
}
