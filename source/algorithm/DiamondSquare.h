#ifndef _ALGORITHM_DIAMONDSQUARE_H
#define _ALGORITHM_DIAMONDSQUARE_H

#include "../algorithm/MapGenerator.h"
#include "../data/HeightMap.h"

namespace pgl
{
	class DiamondSquare : public MapGenerator
	{
	public:

		DiamondSquare(float roughness, unsigned int seed = 0);

		HeightMap generate(int w, int h) const override;

		HeightMap generate(int size) const;

	private:

		void square(int x, int y, float *map);

		void diamond(int x, int y, float *map);

	private:
		float _roughness;
	};
}

#endif // !_ALGORITHM_DIAMONDSQUARE_H
