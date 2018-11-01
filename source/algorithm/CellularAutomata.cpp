#include <random>
#include <iostream>

#include "CellularAutomata.h"


namespace pgl
{
	CellularAutomata::CellularAutomata(float chance, unsigned int birth, unsigned int death,
		unsigned int epoch, CountNeighbours &func, unsigned int seed)
	{
		_func = func;
		_seed = seed;
		_chance = chance;
		_birth = birth;
		_death = death;
		_epoch = epoch;
	}


	int CellularAutomata::FonNeymanNeighbourhood(int x, int y, HeightMap &map)
	{
		int wallCount = 0;

		for (int neighbourY = y - 1; neighbourY <= y + 1; neighbourY++) {
			if (x >= 0 && x < map.width() && neighbourY >= 0 && neighbourY < map.height()) {
				if (neighbourY != y) {
					wallCount += map.depth(x, neighbourY);
				}
			}
		}

		for (int neighbourX = x - 1; neighbourX <= x + 1; neighbourX++) {
			if (neighbourX >= 0 && neighbourX < map.width() && y >= 0 && y < map.height()) {
				if (neighbourX != x) {
					wallCount += map.depth(neighbourX, y);
				}
			}
		}

		return wallCount;
	}

	HeightMap CellularAutomata::generate(int w, int h)
	{
		HeightMap map(w, h);

		std::default_random_engine engine(_seed);
		std::normal_distribution<float> distr(0.0, 1.0);

		for (int y = 0; y < map.height(); y++) {
			for (int x = 0; x < map.width(); x++) {
				if (x == 0 || x == map.height() - 1 || y == 0 || y == map.width() - 1) {
					map.depth(x, y, 0.0);
				}

				distr(engine);

				if (distr(engine) >= _chance) {
					map.depth(x, y, 1.0);
				}

				else {
					map.depth(x, y, 0.0);
				}
			}
		}

		int neighbours;
		HeightMap newMap(map);
		for (int i = 0; i < _epoch; i++) {

			for (int y = 0; y < map.height(); y++) {

				for (int x = 0; x < map.width(); x++) {

					neighbours = 0;
					neighbours = _func(x, y, map);

					if (neighbours >= _birth) {
						newMap.depth(x, y, 1.0);
					}

					else if (neighbours <= _death) {
						newMap.depth(x, y, 0.0);
					}
				}
			}

			map = newMap;
		}

		return map;
	}

}