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

		CellularAutomata(unsigned int seed, unsigned int chance, unsigned int birth,
			unsigned int death, unsigned int epoch, CountNeighbours &func);

		HeightMap generate(int w, int h) const = 0;

	private:
		CountNeighbours _func;
		unsigned int _chance;
		unsigned int _birth;
		unsigned int _death;
		unsigned int _epoch;
	};
}
#endif // !_ALGORITHM_CELLULARAUTOMATA_H