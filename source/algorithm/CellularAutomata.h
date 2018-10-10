#ifndef _ALGORITHM_CELLULARAUTOMATA_H
#define _ALGORITHM_CELLULARAUTOMATA_H

namespace pgl
{
	using namespace std;

	class CellularAutomata
	{
	private:
		int *_map;
		size_t _width;
		size_t _height;
		int _randomFillPercent;

	public:

		CellularAutomata();
		CellularAutomata(size_t width, size_t height);
		~CellularAutomata();

		size_t width();
		size_t height();

		void randomFillMap();
		void smoothMap(int count);
		int calculateNeighbours(int x, int y);
	};
}
#endif // !_ALGORITHM_CELLULARAUTOMATA_H