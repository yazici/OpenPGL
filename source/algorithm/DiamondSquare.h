#ifndef _ALGORITHM_DIAMONDSQUARE_H
#define _ALGORITHM_DIAMONDSQUARE_H

#include <random>
#include "algorithm/MapGenerator.h"
#include "data/HeightMap.h"

namespace pgl
{
	class DiamondSquare : public MapGenerator
	{
	public:

		DiamondSquare(float roughness, float maxHeight, unsigned int seed = 0);

		HeightMap generate(int w, int h) const override;

		HeightMap generate(int size) const;

	private:

		float square(int x, int y, int hStep, int size, float **map) const;

		float diamond(int x, int y, int hStep, int size, float **map) const;

	private:
		float _roughness;
		float _maxHeight;
	};
}

#endif // !_ALGORITHM_DIAMONDSQUARE_H
