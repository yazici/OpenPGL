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

namespace pgl
{
    using glm::vec2;
    
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
        NoiseGenerator2D(float lacunarity = 2.0f, float persistence = 0.5f, float surfaceDepth = 0.0f, uint8_t octave = 1, vec2 shift = {0.0f, 0.0f}, int seed = 0);
        
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
        
        float PerlineNoise (vec2 st, const vector<uint32_t>& permutation, const vector<vec2>& gradient) const;
        
        float _lacunarity;
        float _persistence;
        float _surfaceDepth;
        uint8_t _octave;
        vec2 _shift;
    };
}


#endif // !_ALGORITHM_NOISE_GENERATOR_2D_H
