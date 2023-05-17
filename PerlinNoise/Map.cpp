#include <cmath>
#include "Map.hpp"
#include <iostream>


using namespace std;


Map::Builder & Map::Builder::setWidth(unsigned int width) {
	this->width = width;
	return *this;
}
Map::Builder & Map::Builder::setHeight(unsigned int height) {
	this->height = height;
	return *this;
}
Map::Builder & Map::Builder::setSeed(unsigned int seed) {
	this->seed = seed;
	return *this;
}
Map::Builder & Map::Builder::setLucanarity (unsigned int lucanarity) {
	this->lucanarity = lucanarity;
	return *this;
}
Map::Builder & Map::Builder::setPersistance(unsigned int persistance) {
	this->persistance = persistance;
	return *this;
}
Map::Builder & Map::Builder::setOctave(unsigned int octave) {
	this->octave = octave;
	return *this;
}
Map Map::Builder::build() const{
	return Map(width, height, seed, lucanarity, persistance, octave);
}

Map::Map(unsigned int width, unsigned int height, unsigned int seed, unsigned int lucanarity, unsigned int persistance, unsigned int octave)
: width(width), height(height), seed(seed), lucanarity (lucanarity ), persistance(persistance), octave(octave), image(width, height), pn(seed) {
	ppm * images[octave];

	for (unsigned int i = 0; i < octave; ++i) images[i] =  new ppm(width, height);

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

				images[k]->r[kk] = floor(255 / (double)amplitude * n);
				images[k]->g[kk] = floor(255 / (double)amplitude * n);
				images[k]->b[kk] = floor(255 / (double)amplitude * n);
				kk++;
			}
		}
	}

	for (unsigned int i = 0; i < octave; ++i) {
		for(unsigned int j = 0; j < height * width; ++j) {
			image.r[j] += images[i]->r[j];
			image.g[j] += images[i]->g[j];
			image.b[j] += images[i]->b[j];
		}
	}
}

const ppm & Map::getImage() const {
	return image;
}

const ppm Map::getStableImage(int threshold) {
	ppm cpy(width, height);

	for(unsigned int j = 0; j < height * width; ++j) {
		if (image.r[j] < threshold) cpy.r[j] = 0;
		else cpy.r[j] = image.r[j];
		if (image.g[j] < threshold) image.g[j] = 0;
		else cpy.g[j] = image.g[j];
		cpy.b[j] = image.b[j];
	}

	return cpy;
}
