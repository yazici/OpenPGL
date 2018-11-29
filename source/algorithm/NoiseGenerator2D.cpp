//
//  NoiseGenerator2D.cpp
//  project
//
//  Created by Асиф Мамедов on 21.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#include "NoiseGenerator2D.h"

#include <glm/detail/_noise.hpp>

#include <random>

namespace pgl
{
    using glm::vec2;
    using glm::tvec2;
    using glm::smoothstep;
    using glm::mix;
    using glm::fract;
    using glm::floor;
    using glm::detail::permute;

    float NoiseGenerator2D::PerlineNoise(vec2 st) const
    {
        tvec2<size_t> b0, b1;
        vec2 r0, r1, s;
        
        //Находим координаты левой верхней вершины квадрата,
        //затем находим локальные координаты точки внутри квадрата.
        b0 = floor(st);
        r0 = fract(st);
        
        b1 = b0 + tvec2<size_t>(1);
        r1 = r0 - vec2(1.0);
        
        // Будем интерполировать локальну координату с помощью криаой Гунтиса.
        s = r0 * r0 * (vec2(3.0) - vec2(2.0) * r0);
        
         // Далее будем извлекать градиент для всех вершин квадрата.
        size_t i = permute<size_t>(b0.x) % _gradient.size(), j = permute<size_t>(b1.x) % _gradient.size();
        
        size_t  b00 , b01, b10, b11;
        
        b00 = permute<size_t>(i + b0.y) % _gradient.size();
        b01 = permute<size_t>(i + b1.y) % _gradient.size();
        b10 = permute<size_t>(j + b0.y) % _gradient.size();
        b11 = permute<size_t>(j + b1.y) % _gradient.size();
        
        float a, b, u, v;
        
        // Вычисляем скалаярное произведение между которыми будем итерполировать,
        //а затем производим линейную интерполяцию
        u = r0.x * _gradient[b00].x + r0.y * _gradient[b00].y;
        v = r1.x * _gradient[b10].x + r0.y * _gradient[b10].y;
        
        a = mix(u, v, s.x);
        
        u = r0.x * _gradient[b01].x + r1.y * _gradient[b01].y;
        v = r1.x * _gradient[b11].x + r1.y * _gradient[b11].y;
        
        b = mix(u, v, s.x);
        
        return mix(a, b, s.y);
    }
    
    double convert(double value,double From1,double From2,double To1,double To2)
    {
        return (value-From1)/(From2-From1)*(To2-To1)+To1;
    }
    
    NoiseGenerator2D::NoiseGenerator2D(function<float (size_t)> lacunarity, function<float (size_t)> persistence, float surfaceDepth, uint8_t octave, vec2 shift, int seed) :
        MapGenerator(seed),
        _lacunarity(lacunarity),
        _persistence(persistence),
        _surfaceDepth(surfaceDepth),
        _octave(octave),
        _shift(shift)
    {
        // TODO: Данная функция расспределения здесь временна т. к. мы еще не о
        // пределили механизм передачи разных функций распределения
        std::mt19937 gen(_seed);
        std::uniform_int_distribution<> g(-1, 1);
        std::uniform_int_distribution<> getQuantity(500, 1500);
        
        _gradient.resize(getQuantity(gen));
        
        for (size_t i = 0; i < _gradient.size(); i++) {
            _gradient[i].x = g(gen);
            _gradient[i].y = g(gen);
        }
    }
    
    HeightMap NoiseGenerator2D::generate(int w, int h) const
    {
        HeightMap map(w, h);
        
//        for(int i = 0; i < w; i++) {
//            for(int j = 0 ; j < h; j++) {
//                float x = (1.0f / (w - 1)) * i;
//                float y = (1.0f / (h - 1)) * j;
//                float sum = 0.0f;
//                float freq = _lacunarity(0);
//                float amplitude = _persistence(0);
//
//                for(int oct = 0; oct < _octave; oct++ ) {
//                    glm::vec2 p (x * freq, y * freq);
//                    p += _shift;
//
//                    sum += PerlineNoise(p) * amplitude;
//
//                    // Полученное значение приводится от 0 до 1
//                    float result = (sum) / 2.0f;
//
//                    result = (result > 2.0f ? 2.0f : (result < -2.0 ? -2.0 : result));
//                    map.depth(i, j, convert(result, 0, 1, 0, _surfaceDepth));
//                    freq *= _lacunarity(oct);
//                    amplitude *= _persistence(oct);
//                }
//            }
//        }
        
        for(int i = 0; i < w; i++) {
            for(int j = 0 ; j < h; j++) {
                float x = (1.0f / (w - 1)) * i;
                float y = (1.0f / (h - 1)) * j;
                float sum = 0.0f;
                float freq = _lacunarity(0);
                float amplitude = _persistence(0);
                
                for(int oct = 0; oct < _octave; oct++ ) {
                    glm::vec2 p (x * freq, y * freq);
                    p += _shift;
                    sum += PerlineNoise(p) * amplitude;
                    
                    // Полученное значение приводится от 0 до 1
                    float result = (sum + _surfaceDepth) / 2.0f;
                    result = (result > 1.0f ? 1.0f : (result < 0.0 ? 0.0 : result));
                    
                    map.depth(i, j, result);
                    freq *= _lacunarity(oct);
                    amplitude *= _persistence(oct);
                }
            }
        }
        
        return map;
    }
}
