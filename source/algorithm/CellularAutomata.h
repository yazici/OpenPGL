#ifndef _ALGORITHM_CELLULARAUTOMATA_H
#define _ALGORITHM_CELLULARAUTOMATA_H

#include "MapGenerator.h"
#include <functional>


namespace pgl
{
	class CellularAutomata : public MapGenerator
	{
	public:
		typedef std::function<int(int, int, HeightMap &)> CountNeighbours;

		CellularAutomata(float chance, unsigned int birth, unsigned int death,
			unsigned int epoch, CountNeighbours &funcunsigned, unsigned int seed = 0);

		/**
		* ћетод, который генерирует карту высот с помощью клеточного автомата.
		*
		* @param w ширина карты
		* @param h высота карты
		*
		* @return карта высот.
		*/
		HeightMap generate(int w, int h);

		/**
		* ћетод, который считает количество соседей по окрестности фон Ќеймана.
		*
		* @param x координата по оси абсцисс
		* @param y координата по оси ординат
		* @param map карта высот
		*
		* @return количество соседей точки по окрестности фон Ќеймана.
		*/
		static int FonNeymanNeighbourhood(int x, int y, HeightMap &map);

	private:
		CountNeighbours _func;
		float _chance;
		unsigned int _birth;
		unsigned int _death;
		unsigned int _epoch;
	};
}
#endif // !_ALGORITHM_CELLULARAUTOMATA_H