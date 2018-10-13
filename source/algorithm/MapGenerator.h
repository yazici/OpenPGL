#ifndef _ALGORITHM_MAPGENERATOR_H
#define _ALGORITHM_MAPGENERATOR_H

#include <tuple>

namespace pgl
{
    //typedef std::tuple<size_t, size_t, void *> HeightMap;
    class HeightMap;

    class MapGenerator
    {
    public:
        virtual HeightMap Generate(int w, int h) const = 0; 
    };
}

#endif //!_ALGORITHM_MAPGENERATOR_H
