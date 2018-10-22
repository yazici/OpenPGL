//
//  NoiseGenerator2D.cpp
//  project
//
//  Created by Асиф Мамедов on 21.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#include "NoiseGenerator2D.h"

#include <glm/gtc/noise.hpp>

namespace pgl
{
    using glm::vec2;
    
    NoiseGenerator2D::NoiseGenerator2D(int seed, float lacunarity, float persistence, float surfaceDepth, uint8_t octave, vec2 shift) :
        MapGenerator(seed),
        _lacunarity(lacunarity),
        _persistence(persistence),
        _surfaceDepth(surfaceDepth),
        _octave(octave),
        _shift(shift)
    {
    }
    
    HeightMap NoiseGenerator2D::generate(int w, int h) const
    {
        HeightMap map (w, h);
        
        for (size_t i = 0; i < w; i++) {
            for (size_t j = 0; j < h; j++) {
                float x = (1.0f / (w - 1)) * i;
                float y = (1.0f / (h - 1)) * j;
                float sum = 0.0f;
                float freq = _lacunarity;
                float amplitude = _persistence;
                
                for (uint8_t oct = 0; oct < _octave; oct++) {
                    vec2 p (x * freq, y * freq);
                    p += _shift;
                    
                    sum += glm::simplex(p + vec2(_seed)) * amplitude;
                    
                    // Полученное значение приводится от 0 до 1
                    float result = (sum + _surfaceDepth) / 2.0f;
                    result = (result > 1.0f ? 1.0f : (result < 0.0 ? 0.0 : result));
                    
                    map.depth(x, y, (GLubyte) ( result * 255 ));
                    
                    freq *= _lacunarity;
                    amplitude *= _persistence;
                }
            }
        }
        
        return map;
    }
}
