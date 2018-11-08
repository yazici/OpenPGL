#ifndef _DATA_HEIGHTMAP_H
#define _DATA_HEIGHTMAP_H

#include <vector>

#include "data/Mesh.h"
#include "data/Texture.h"

namespace pgl
{
	class HeightMap
	{
	public:
        
        /**
        * Конструктор.
        *
        * @param w ширина карты
        * @param h высота карты
        * @param data массив данных
        */
		HeightMap(int w, int h, const float *data = nullptr);

		HeightMap(int w, int h, const float **data);
        /**
        * Конструктор копирования. Полностью копирует карту высот.
        */
		HeightMap(const HeightMap &hm);

        /**
        * Возвращает ширину карты.
        * @return ширина.
        */
		int width() const noexcept;

        /**
        * Возвращает высоту карты.
        * @return высота.
        */
		int height() const noexcept;
        
        /**
        * Метод с помощью которой можно узнать высоту точки.
        *
        * @param x координата по оси абсцисс
        * @param y координата по оси ордината
        * @return высота точки на карте по координате (x, y)
        */
		float depth(int x, int y) const noexcept;
        
        /**
        * Метод с помощью которой можно указать высоту точки.
        *
        * @param x координата по оси абсцисс
        * @param y координата по оси ордината
        * @param v высота точки по координате (x, y)
        */
		void depth(int x, int y, float v) noexcept;

        /**
        * Возвращает черно-белую текстуру, которая является картой высот.
        * @return текстура с картой высот.
        */
		Texture texture() const;

		Mesh toMesh(float divSize = 1.0f) const;

	private:

		void _init(int w, int h, const float *data);

	private:
		std::vector<float> _map;
		int _width;
		int _height;
	};
}

#endif // !_DATA_HEIGHTMAP_H
