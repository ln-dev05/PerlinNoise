#include <cmath>
#include "ppm.h"
#include "PerlinNoise.h"

#include <iostream>

using namespace std;

class Map {
	private:
		ppm image;
		unsigned int width, height, seed, lucanarity, persistance, octave;
		PerlinNoise pn;
	public:
		class Builder {
			private:
				unsigned int width, height, seed, lucanarity, persistance, octave;
			public:
				Builder() = default;
				Builder & setWidth(unsigned int width) {
					this->width = width;
					return *this;
				}
				Builder & setHeight(unsigned int height) {
					this->height = height;
					return *this;
				}
				Builder & setSeed(unsigned int seed) {
					this->seed = seed;
					return *this;
				}
				Builder & setLucanarity (unsigned int lucanarity) {
					this->lucanarity = lucanarity;
					return *this;
				}
				Builder & setPersistance(unsigned int persistance) {
					this->persistance = persistance;
					return *this;
				}
				Builder & setOctave(unsigned int octave) {
					this->octave = octave;
					return *this;
				}
				Map build() const{
					return Map(width, height, seed, lucanarity, persistance, octave);
				}
		};
		Map(unsigned int width, unsigned int height, unsigned int seed, unsigned int lucanarity, unsigned int persistance, unsigned int octave)
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

		const ppm & getImage() {
			return image;
		}
		const ppm getStableImage(int threshold) {
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
};

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


	map.getStableImage(threshold).write("figure_paul.ppm");

	return 0;
}
