#ifndef _ALGORITHM_MAPGENERATOR_H
#define _ALGORITHM_MAPGENERATOR_H

namespace pgl
{
    class HeightMap;

    class MapGenerator
    {
    public:

		/**
		* Конструктор создает случайное семя генерации.
		*/
		MapGenerator();

		/**
		* Конструктор сохраняет семя генерации. Если seed равен 0, то семя  выбирается случайным
		* образом. Алгоритмы должны использовать семя при генерации объектов. Алгоритм инициализированный
		* одиним и тем же семенем должен выдавать такой же результат.
		*/
		MapGenerator(unsigned int seed);

		/**
		* Генерирует карту высот размером w*h.
		* 
		* @param w ширина карты.
		* @param h высота карты.
		* @return возвращает карту высот.
		*/
        virtual HeightMap generate(int w, int h) const = 0; 
	
		/**
		* Метод возвращает семя генерации.
		* @return семя генерации.
		*/
		unsigned int seed() const noexcept;

	protected:
		unsigned int _seed;
    };
}

#endif //!_ALGORITHM_MAPGENERATOR_H
