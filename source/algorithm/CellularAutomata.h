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
		* Метод, который генерирует карту высот с помощью клеточного автомата.
		*
		* @param w ширина карты
		* @param h высота карты
		*
		* @return карта высот.
		*/
		HeightMap generate(int w, int h) const override;

		/**
		* Метод, который считает количество соседей по окрестности фон Неймана.
		*
		* @param x координата по оси абсцисс
		* @param y координата по оси ординат
		* @param map карта высот
		*
		* @return количество соседей точки по окрестности фон Неймана.
		*/
		static int FonNeymanNeighbourhood(int x, int y, HeightMap &map);
        
        static int TraTaTa(int x, int y, HeightMap &m)
        {
            int neighbour = 0;
            
            for (int lx = -1; lx < 2; ++lx) {
                for (int ly = -1; ly < 2; ++ly) {
                    if (lx != 0 || ly != 0) {
                        if (x + lx >= 0 && ly + y >= 0 && ly + y < m.height() && lx + x < m.width()) {
                            neighbour += m.depth(x + lx, y + ly);
                        }
                    }
                }
            }
            
            return neighbour;
        }

	private:
		CountNeighbours _func;
		float _chance;
		unsigned int _birth;
		unsigned int _death;
		unsigned int _epoch;
	};
}
#endif // !_ALGORITHM_CELLULARAUTOMATA_H
