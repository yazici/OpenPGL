#include <random>
#include <cassert>

#include "MapGenerator.h"

namespace pgl
{
	MapGenerator::MapGenerator(unsigned int seed) :
		_seed(seed)
	{
		if (0 == _seed) {
			std::random_device rd;
			_seed = rd();
		}
	}

	unsigned int MapGenerator::seed() const noexcept
	{
		assert(_seed);
		return _seed;
	}
}