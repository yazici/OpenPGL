#ifndef _ALGORITHM_DIAMONDSQUARE_H
#define _ALGORITHM_DIAMONDSQUARE_H

#include "MapGenerator.h"

namespace pgl
{
	class DiamondSquare : public MapGenerator
	{
	public:

		DiamondSquare(float roughnes, int seed = 0);

		HeightMap Generate(int w, int h) const;

	private:
		float _roughness;
		int _seed;
	};
}

#endif // !_ALGORITHM_DIAMONDSQUARE_H
