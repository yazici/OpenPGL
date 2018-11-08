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

		return HeightMap(1, 1);
        //return generate(w);
    }

    HeightMap DiamondSquare::generate(int size) const
    {
		float **map = new float *[size];
		for (int i = 0; i < size; ++i) {
			map[i] = new float[size] {0.0f};
		}
		
		auto gen = std::mt19937(_seed);
		int step = size - 1;
		int hStep = step / 2;
		float r = _roughness;
		map[0][0]	    = 0.0f;
		map[step][step] = 0.0f;
		map[step][0]    = 0.0f;
		map[0][step]    = 0.0f;

		while (1 < step) {
			auto dist = std::normal_distribution<float>(0.0f, r);

			for (int y = hStep; y < size; y += step) {
				for (int x = hStep; x < size; x += step) {
					map[y][x] = square(x, y, hStep, size, map) + dist(gen);
				}
			}

			for (int y = hStep; y < size; y += step) {
				for (int x = hStep; x < size; x += step) {
					map[y][x - hStep] = diamond(x - hStep, y, hStep, size, map) + dist(gen);
					map[y][x + hStep] = diamond(x + hStep, y, hStep, size, map) + dist(gen);
					map[y - hStep][x] = diamond(x, y - hStep, hStep, size, map) + dist(gen);
					map[y + hStep][x] = diamond(x, y + hStep, hStep, size, map) + dist(gen);
				}
			}

			r /= 2.0f;
			step = hStep;
			hStep /= 2;
		}

		return HeightMap(size, size, (const float **)map);
    }

	float DiamondSquare::square(int x, int y, int hStep, int size, float **map) const
	{
		float h = 0.0f;
		h += (map[y - hStep][x - hStep] + map[y - hStep][x + hStep]  +
			  map[y + hStep][x - hStep] + map[y + hStep][x + hStep]) / 4.0f;
		return h;
	}

	float DiamondSquare::diamond(int x, int y, int hStep, int size, float **map) const
	{
		float h = 0.0f;
		int points = 0;

		if (0 != x) {
			h += map[y][x - hStep];
			++points;
		}

		if (size - 1 != x) {
			h += map[y][x + hStep];
			++points;
		}

		if (0 != y) {
			h += map[y - hStep][x];
			++points;
		}

		if (size - 1 != y) {
			h += map[y + hStep][x];
			++points;
		}

		h = h / points;
		return h;
	}
}
