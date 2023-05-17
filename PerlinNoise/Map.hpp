#include "ppm.h"
#include "PerlinNoise.h"


#if !defined(MAP_HPP)
#define MAP_HPP

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
				Builder & setWidth(unsigned int width);
				Builder & setHeight(unsigned int height);
				Builder & setSeed(unsigned int seed);
				Builder & setLucanarity (unsigned int lucanarity);
				Builder & setPersistance(unsigned int persistance);
				Builder & setOctave(unsigned int octave);
				Map build() const;
		};

		Map(unsigned int width, unsigned int height, unsigned int seed, unsigned int lucanarity, unsigned int persistance, unsigned int octave);
		const ppm & getImage() const;
		const ppm getStableImage(int threshold);
};


#endif // MAP_HPP
