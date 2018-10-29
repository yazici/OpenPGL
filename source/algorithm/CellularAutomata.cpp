#include <random>
#include <iostream>

#include "CellularAutomata.h"


namespace pgl
{

	CellularAutomata::CellularAutomata(unsigned int seed, unsigned int chance, unsigned int birth,
		unsigned int death, unsigned int epoch, COUNT_NEIGHBOURS)
	{
		_seed = seed;
		_chance = chance;
		_birth = birth;
		_death = death;
		_epoch = epoch;
	}

	//рандомное заполнение карты
	void CellularAutomata::randomFillMap()
	{
		srand(time(NULL));

		for (size_t y = 0; y < _height; y++) {
			size_t line = y * _width;

			for (size_t x = 0; x < _width; x++) {
				if (x == 0 || x == _height - 1 || y == 0 || y == _width - 1) {
					_map[line + x] = 0;
				}
				int PseudoRandom = rand() % 100;

				_randomFillPercent = rand() % 100;

				_map[line + x] = _randomFillPercent > PseudoRandom;

			}
		}
	}

	//считаем количество соседей у клетки
	int CellularAutomata::calculateNeighbours(int x, int y)
	{
		int wallCount = 0;
		
		for (size_t neighbourY = y - 1; neighbourY <= y + 1; neighbourY++) {
			for (size_t neighbourX = x - 1; neighbourX <= x + 1; neighbourX++) {
				if (neighbourX >= 0 && neighbourX < _width && neighbourY >= 0 && neighbourY < _height) {
					if (neighbourX != x || neighbourY != y) {
						wallCount += _map[y * _width + x];
					}
				}
			}
		}

		return wallCount;
	}

	//функция, чтобы сгладить карту
	void CellularAutomata::smoothMap(int count)
	{
		for (size_t i = 0; i < count; i++){
			for (size_t y = 0; y < _height; y++) {
				for (size_t x = 0; x < _width; x++) {
					int neighbours = calculateNeighbours(x, y);

					if (neighbours > 4) {
						_map[y * _width + x] = 1;
					} else if (neighbours < 4) {
						_map[y * _width + x] = 0;
					}
				}
			}
		}
	}

}
