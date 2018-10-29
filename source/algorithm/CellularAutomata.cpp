#include <random>
#include <iostream>

#include "CellularAutomata.h"


namespace pgl
{
	CellularAutomata::CellularAutomata(unsigned int seed, unsigned int chance, unsigned int birth, unsigned int death, unsigned int epoch, CountNeighbours &func)
	{
		_func = func;
		_seed = seed;
		_chance = chance;
		_birth = birth;
		_death = death;
		_epoch = epoch;
	}
}
