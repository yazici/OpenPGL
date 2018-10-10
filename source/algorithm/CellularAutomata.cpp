#include <ctime>
#include <iostream>

#include "CellularAutomata.h"

namespace pgl
{

	CellularAutomata::CellularAutomata()
	{
	}

	CellularAutomata::CellularAutomata(size_t width, size_t height)
	{
		_width = width;
		_height = height;

		_map = new int[_width*_height];
		randomFillMap();

		smoothMap(5);
	}

	CellularAutomata::~CellularAutomata()
	{
		delete[] _map;
	}

	size_t CellularAutomata::width()
	{
		return _width;
	}

	size_t CellularAutomata::height()
	{
		return _height;
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
