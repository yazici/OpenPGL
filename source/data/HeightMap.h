//
//  HeightMap.h
//
//  Created by Максим Денисенко on 22.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#ifndef _DATA_HEIGHTMAP_H
#define _DATA_HEIGHTMAP_H

#include <string>
#include <cstdint>

#include "data/Texture.h"

using namespace std;

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
		HeightMap(size_t w, size_t h, const uint8_t *data = nullptr);

        /**
        * Конструктор копирования. Полностью копирует карту высот.
        */
		HeightMap(const HeightMap &hm);

        /**
        * Возвращает ширину карты.
        * @return ширина.
        */
		size_t width() const noexcept;

        /**
        * Возвращает высоту карты.
        * @return высота.
        */
		size_t height() const noexcept;
        
        /**
        * Метод с помощью которой можно узнать высоту точки.
        *
        * @param x координата по оси абсцисс
        * @param y координата по оси ордината
        * @return высота точки на карте по координате (x, y)
        */
		uint8_t depth(size_t x, size_t y) const noexcept;
        
        /**
        * Метод с помощью которой можно указать высоту точки.
        *
        * @param x координата по оси абсцисс
        * @param y координата по оси ордината
        * @param v высота точки по координате (x, y)
        */
		void depth(size_t x, size_t y, uint8_t v) noexcept;

        /**
        * Возвращает черно-белую текстуру, которая является картой высот.
        * @return текстура с картой высот.
        */
		const Texture& texture() const;

	private:
		Texture _map;
		size_t _width;
		size_t _height;
	};
}

#endif // !_DATA_HEIGHTMAP_H
