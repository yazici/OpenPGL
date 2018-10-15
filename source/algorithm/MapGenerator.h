#ifndef _ALGORITHM_MAPGENERATOR_H
#define _ALGORITHM_MAPGENERATOR_H

namespace pgl
{
    class HeightMap;

    class MapGenerator
    {
    public:

		/**
		* Генерирует карту высот размером w*h.
		* 
		* @param w ширина карты.
		* @param h высота карты.
		* @return возвращает карту высот.
		*/
        virtual HeightMap Generate(int w, int h) const = 0; 
	
	protected:
		int _seed;
    };
}

#endif //!_ALGORITHM_MAPGENERATOR_H
