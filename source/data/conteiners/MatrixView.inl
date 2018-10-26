//
//  MatrixView.inl
//  project
//
//  Created by Асиф Мамедов on 24.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#include <stdexcept>

#include <cassert>

namespace pgl
{
    using std::invalid_argument;
    
    template<class T>
    class MatrixView
    {
    public:
        
        /**
         * Конструктор.
         *
         * @param begin указатель на начало срезки
         * @param width ширина матрицы
         * @param height высота матрицы
         */
        MatrixView(T* begin, size_t width, size_t height) :
            _width(width),
            _height(height)
        {
            assert(begin);
            _begin = begin;
        }
        
        /**
         * Метод необходим для чтения/записи элементов матрицы.
         *
         * Желательнее использовать этот метод вместо перегруженных
         * опреторов классов matrixView и range (ь. к. метод at работает быстрее).
         *
         * @param i индекс строки матрицы
         * @aparm j индекс высоты матрицы
         * @throw возникает в случае выхода за границы матрицы
         * @return ссылка на элемент матрицы
         *
         */
        T& at(size_t i, size_t j)
        {
            if (i >= _width || j >= _height) {
                throw invalid_argument("Crossing the matrix");
            }
            
            return _begin[i * _width + j];
        }
        
        /**
         * Метод необходим для чтения элементов матрицы.
         *
         * Желательнее использовать этот метод вместо перегруженных
         * опреторов классов matrixView и range (ь. к. метод at работает быстрее).
         *
         * @param i индекс строки матрицы
         * @aparm j индекс высоты матрицы
         * @throw возникает в случае выхода за границы матрицы
         * @return константную ссылку на элемент матрицы
         *
         */
        const T& at(size_t i, size_t j) const
        {
            if (i >= _width || j >= _height) {
                throw invalid_argument("Crossing the matrix");
            }
            
            return _begin[i * _width + j];
        }
        
    private:
        
        /**
         * Класс необходимый для проверки гранцы.
         */
        class range
        {
        public:
            /**
             * Конструктор.
             *
             * @param ptr указатель на строку
             * @param height ширина матрицы
             */
            range(T* ptr, size_t height) :
                _ptr(ptr),
                _height(height)
            {
            }
            
            /**
             * Перегруженный опреатор [].
             *
             * @param i индекс столбца в матрице
             * @throw возникает в случае выхода за границы матрицы (за границы столбца)
             * @return ссылка на элемент матрицы
             */
            T& operator[] (size_t i)
            {
                if (i >= _height) {
                    throw invalid_argument("Crossing the matrix");
                }
                
                return _ptr[i];
            }
            
            /**
             * Перегруженный опреатор [].
             *
             * @param i индекс столбца в матрице
             * @throw возникает в случае выхода за границы матрицы (за границы столбца)
             * @return констрантную ссылку на элемент матрицы
             */
            const T& operator[] (size_t i) const
            {
                if (i >= _height) {
                    throw invalid_argument("Crossing the matrix");
                }
                
                return _ptr[i];
            }
            
        private:
            T* _ptr;
            size_t _height;
        };
        
    public:
        
        /**
         * Перегруженный оператор [].
         *
         * @param i индекс строки матрицы
         * @throw возникает в случае выхода за границы матрицы (за границы строки)
         * @return копию объекта типа range
         */
        range operator[](size_t i)
        {
            if (i > _width) {
                throw invalid_argument("Crossing the matrix");
            }
            
            return range(_begin + (_width * i), _height);
        }
        
        /**
         * Перегруженный оператор [].
         *
         * @param i индекс строки матрицы
         * @throw возникает в случае выхода за границы матрицы (за границы строки)
         * @return константну копию объекта типа range
         */
        const range operator[](size_t i) const
        {
            if (i > _width) {
                throw invalid_argument("Crossing the matrix");
            }
            
            return range(_begin + (_width * i), _height);
        }
        
        size_t width() const noexcept
        {
            return _width;
        }
        
        size_t height() const noexcept
        {
            return _height;
        }
        
    protected:
        T* _begin;
        size_t _width;
        size_t _height;
        
    };
}
