#include <random>
#include <cassert>

#include "../algorithm/MapGenerator.h"

namespace pgl
{
	MapGenerator::MapGenerator() :
		MapGenerator(0)
	{
	}

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
