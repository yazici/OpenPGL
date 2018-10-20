#ifndef _DATA_HEIGHTMAP_H
#define _DATA_HEIGHTMAP_H

#include <string>
#include <cstdint>

#include "Texture.h"

using namespace std;

namespace pgl
{
	class HeightMap
	{
	public:

		HeightMap(int w, int h, const uint8_t *data = nullptr);

		HeightMap(const HeightMap &hm);

		int width() const noexcept;

		int height() const noexcept;

		uint8_t depth(int x, int y) const;

		void depth(int x, int y, uint8_t v);

		const Texture &texture() const;

	private:
		Texture _map;
		int _width;
		int _height;
	};
}

#endif // !_DATA_HEIGHTMAP_H
