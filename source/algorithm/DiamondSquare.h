#ifndef _ALGORITHM_DIAMONDSQUARE_H
#define _ALGORITHM_DIAMONDSQUARE_H

#include "MapGenerator.h"

namespace pgl
{
	class DiamondSquare : public MapGenerator
	{
	public:

		DiamondSquare(float roughnes, int seed = 0);

		HeightMap generate(int w, int h) const override;

	private:
		float _roughness;
	};
}

#endif // !_ALGORITHM_DIAMONDSQUARE_H
