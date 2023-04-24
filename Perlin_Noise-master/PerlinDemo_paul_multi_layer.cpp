#include <cmath>
#include "ppm.h"
#include "PerlinNoise.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	unsigned int width = 600, height = 450;
	unsigned int seed = (argc >= 5)? atoi(argv[4]) : 237;
	PerlinNoise pn(seed);

	unsigned int lucanarity = atoi(argv[1]);
	unsigned int persistance = atoi(argv[2]);
	unsigned int octave = atoi(argv[3]);

	const unsigned int threshold = 127;

	ppm * images[octave];
	for (unsigned int i = 0; i < octave; ++i) {
		images[i] =  new ppm(width, height);
	}

	for (unsigned int k = 0; k < octave; ++k) {
		unsigned int kk = 0;

		unsigned int freq = pow(lucanarity, k);
		unsigned int amplitude = pow(persistance, k);

		cout << "1/freq = " << freq << " amplitude = " << 1/(double)amplitude << endl;

		for(unsigned int i = 0; i < height; ++i) {
			for(unsigned int j = 0; j < width; ++j) {
				double x = (double)j/((double)width);
				double y = (double)i/((double)height);

				double n = pn.noise(freq * x, freq * y, 255 / (double)amplitude);
				// cout << "n = " << n << endl;
				images[k]->r[kk] = floor(255 / (double)amplitude * n);
				images[k]->g[kk] = floor(255 / (double)amplitude * n);
				images[k]->b[kk] = floor(255 / (double)amplitude * n);
				kk++;
			}
		}
	}

	ppm image(width, height);
	for (unsigned int i = 0; i < octave; ++i) {
		for(unsigned int j = 0; j < height * width; ++j) {
			image.r[j] += images[i]->r[j];
			image.g[j] += images[i]->g[j];
			image.b[j] += images[i]->b[j];
		}
	}
	for(unsigned int j = 0; j < height * width; ++j) {
		if (image.r[j] < threshold) image.r[j] = 0;
		if (image.g[j] < threshold) image.g[j] = 0;
	}
	image.write("figure_paul.ppm");

	return 0;
}
