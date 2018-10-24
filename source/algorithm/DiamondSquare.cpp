#include <stdexcept>
#include "algorithm/DiamondSquare.h"

namespace pgl
{
    DiamondSquare::DiamondSquare(float roughness, unsigned int seed) :
        _roughness(roughness),
        MapGenerator(seed)
    {
    }

    HeightMap DiamondSquare::generate(int w, int h) const
    {
        if (w != h) {
            throw std::invalid_argument("Terrain must be square.");
        }

        return generate(w);
    }

    HeightMap DiamondSquare::generate(int size) const
    {
        float *map = new float[size * size];
		return HeightMap(10, 10);
    }

    void square(int x, int y, float *map)
    {

    }

    void diamond(int x, int y, float *map)
    {

    }
}
