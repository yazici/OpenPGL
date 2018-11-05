//
//  NoiseGenerator2D.cpp
//  project
//
//  Created by Асиф Мамедов on 21.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#include "NoiseGenerator2D.h"

#include <glm/gtc/noise.hpp>

#include <random>

namespace pgl
{
    using glm::vec2;
    using glm::smoothstep;
    using glm::mix;
    using glm::fract;
    
    float NoiseGenerator2D::PerlineNoise(vec2 st)
    {
        // Координата точки в клетке
        vec2 f = fract(st);
        
        // Вычисляем координаты четырёх углов.
        // Каждому углу присваевается рандомное значение.
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(f.x, f.y);
        
        float a = dis(gen);
        float b = dis(gen);
        float c = dis(gen);
        float d = dis(gen);
        
        // Производим интерполяцию Эрмита.
        vec2 u = smoothstep(vec2(0.0), vec2(1.0) , f);
        
        // Вычисляем значение интерполяции между 4-я случайными значениями в углах
        float res = mix(a, b, u.x) + (c - a)* u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
        
        return res * 2.f - 1.f;
    }
    
    NoiseGenerator2D::NoiseGenerator2D(float lacunarity, float persistence, float surfaceDepth, uint8_t octave, vec2 shift, int seed) :
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
        HeightMap map(w, h);
        
        for(int i = 0; i < w; i++) {
            for(int j = 0; j < h; j++) {
                float x = (1.0f / (w - 1)) * i;
                float y = (1.0f / (h - 1)) * j;
                float sum = 0.0f;
                float freq = _lacunarity;
                float amplitude = _persistence;
                
                for(int oct = 0; oct < _octave; oct++ ) {
                    glm::vec2 p (x * freq, y * freq);
                    p += _shift;
                    sum += PerlineNoise(p) * amplitude;
                    
                    // Полученное значение приводится от 0 до 1
                    float result = (sum + _surfaceDepth) / 2.0f;
                    result = (result > 1.0f ? 1.0f : (result < 0.0 ? 0.0 : result));
                    map.depth(i, j, result);
                    
                    freq *= _lacunarity;
                    amplitude *= _persistence;
                }
            }
        }
        
        return map;
    }
}
