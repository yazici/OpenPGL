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
		* �����, ������� ���������� ����� ����� � ������� ���������� ��������.
		*
		* @param w ������ �����
		* @param h ������ �����
		*
		* @return ����� �����.
		*/
		HeightMap generate(int w, int h);

		/**
		* �����, ������� ������� ���������� ������� �� ����������� ��� �������.
		*
		* @param x ���������� �� ��� �������
		* @param y ���������� �� ��� �������
		* @param map ����� �����
		*
		* @return ���������� ������� ����� �� ����������� ��� �������.
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