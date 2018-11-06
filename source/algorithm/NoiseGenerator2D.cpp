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

#include <glm/gtc/random.hpp>

#include <iostream>

namespace pgl
{
    using glm::vec2;
    using glm::tvec2;
    using glm::smoothstep;
    using glm::mix;
    using glm::fract;

    float NoiseGenerator2D::PerlineNoise(vec2 st, const vector<uint32_t>& permutation, const vector<vec2>& gradient) const
    {
        tvec2<int> b0, b1;
        vec2 r0, r1, s;
        
        /**
         * Находим координаты левой верхней вершины квадрата,
         * затем находим локальные координаты точки внутри квадрата.
         */
        b0 = floor(st);
        r0 = fract(st);
        
        b1 = b0 + 1;
        r1 = r0 - vec2(1.0);
        
        // Будем интерполировать локальну координату с помощью криаой Гунтиса.
        s = r0 * r0 * (vec2(3.0) - vec2(2.0) * r0);
        
        /**
         * Далее будем извлекать градиент для всех вершин квадрата.
         */
        size_t i = permutation[b0.x], j = permutation[b1.x];
        size_t  b00 = permutation[i + b0.y], b01 = permutation[i + b1.y], b10 = permutation[j + b0.y], b11 = permutation[j + b1.y];
        
        float a, b, u, v;
        
        /**
         * Вычисляем скалаярное произведение между которыми будем итерполировать,
         * а затем производим линейную интерполяцию
         */
        
        u = r0.x * gradient[b00].x + r0.y * gradient[b00].y;
        v = r1.x * gradient[b10].x + r0.y * gradient[b10].y;
        
        a = mix(u, v, s.x);
        
        u = r0.x * gradient[b01].x + r1.y * gradient[b01].y;
        v = r1.x * gradient[b11].x + r1.y * gradient[b11].y;
        
        b = mix(u, v, s.x);
        
        return mix(a, b, s.y);
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
        
        // TODO: Данная функция расспределения здесь временна т. к. мы еще не о
        // пределили механизм передачи разных функций распределения
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::normal_distribution<> dis(-1.0, 1.0);
        
        vector<uint32_t> permutation(w * h * 2);
        vector<vec2> gradient(w * h * 2);
        
        for (size_t i = 0; i < gradient.size(); i++) {
            permutation[i] = rand() % (w * h);
            gradient[i].x = dis(gen);
            gradient[i].y = dis(gen);
        }
        
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
                    sum += PerlineNoise(p, permutation, gradient) * amplitude;
                    
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
