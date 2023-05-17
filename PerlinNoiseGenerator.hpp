#include "PerlinNoise/Map.hpp"
#include "Navigation/Generator.hpp"

#if !defined(PERLIN_NOISE_GENERATOR_HPP)
#define PERLIN_NOISE_GENERATOR_HPP

#define MOY(a, b, c) (a + b + c)/3

class PerlinNoiseGenerator : public Generator
{
private:
    Map temp;
public:
    PerlinNoiseGenerator(const int w, const int h);
    virtual int get(const int i) const override;
    ~PerlinNoiseGenerator() = default;

};

PerlinNoiseGenerator::PerlinNoiseGenerator(const int w, const int h)
: Generator(), temp(w, h, rand(), 3, 2, 5) {

}

int PerlinNoiseGenerator::get(const int i) const {
    return static_cast<int>(MOY(temp.getImage().r[i], temp.getImage().b[i], temp.getImage().g[i]));
}

#endif // PERLIN_NOISE_GENERATOR_HPP
