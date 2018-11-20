//
//  NoiseGenerator2D.h
//  project
//
//  Created by Асиф Мамедов on 21.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//


#ifndef _ALGORITHM_NOISE_GENERATOR_2D_H
#define _ALGORITHM_NOISE_GENERATOR_2D_H

#include <glm/glm.hpp>

#include "data/HeightMap.h"
#include "algorithm/MapGenerator.h"

#include <vector>

#include <functional>

namespace pgl
{
    using glm::vec2;
    using std::vector;
    using std::function;
    
    class NoiseGenerator2D : public MapGenerator
    {
    public:
        
        /**
         * Конструктор.
         *
         * @param seed семя
         * @param lacunarity лакунарность (влияет на чистоту)
         * @param persistence продолжительность (влияет на амплитуду)
         * @param surfaceDepth влияет на уровень поверхности над уровнем воды
         * @param octave количество суммирований волн (чем больше octave тем реалистичней результат)
         */
        NoiseGenerator2D(function<float (size_t)> lacunarity, function<float (size_t)> persistence , float surfaceDepth = 0.0f, uint8_t octave = 1, vec2 shift = {0.0f, 0.0f}, int seed = 0);
        
        /**
         * Генерирует карту высот размером w*h.
         *
         * Данный метод реализует алгоритм ‘фрактального броуновского движения’.
         * Его суть заключается в суммирование значение функции шума (в данном
         * случае симплексного) с разной частотой и амплитудой.
         *
         * @param w ширина карты.
         * @param h высота карты.
         * @return возвращает карту высот.
         */
        HeightMap generate(int w, int h) const override;
        
        // TODO: Не решён вопрос с функциями распределения.
        
    protected:
        
        float PerlineNoise (vec2 st) const;
        
        function<float (size_t)> _lacunarity;
        function<float (size_t)> _persistence;
        float _surfaceDepth;
        uint8_t _octave;
        vec2 _shift;
        vector<vec2> _gradient;
    };
}


#endif // !_ALGORITHM_NOISE_GENERATOR_2D_H
