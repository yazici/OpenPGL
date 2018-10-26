//
//  ArrayView.inl
//  project
//
//  Created by Асиф Мамедов on 24.10.2018.
//  Copyright © 2018 PCG. All rights reserved.
//

#include <stdexcept>

namespace pgl
{
    using std::invalid_argument;
    
    template<class T>
    class ArrayView
    {
    public:
        
        /**
         * Конструктор.
         *
         * @param begin указатель на начало срезки
         * @param end указатель на конец срезки
         * @throw возникает в случае если end в
         *  памяти располагается дальше чем begin
         */
        ArrayView(T* begin, T* end)
        {
            if (begin > end) {
                throw invalid_argument("Incorrect range");
            }
            
            _begin = begin;
            _end = end;
        }
        
        /**
         * Метод необходим для чтения/записи элементов матрицы.
         *
         * @param i индекс в массиве
         * @throw возникает в случе если произошёл выход за границы массива
         * @return ссылка на i-й элемент массива
         */
        T& at(size_t i)
        {
            if (_begin + i > _end) {
                throw invalid_argument("Crossing the array");
            }
            
            return _begin[i];
        }
        
        /**
         * Метод необходим для чтения элементов матрицы.
         *
         * @param i индекс в массиве
         * @throw возникает в случе если произошёл выход за границы массива
         * @return константную ссылку на i-й элемент массива
         */
        const T& at(size_t i) const
        {
            if (_begin + i > _end) {
                throw invalid_argument("Crossing the array");
            }
            
            return _begin[i];
        }
        
        /**
         * Перегруженный оператор [].
         *
         * @param i индекс в массиве
         * @throw возникает в случе если произошёл выход за границы массива
         * @return ссылка на i-й элемент массива
         */
        T& operator[] (size_t i)
        {
            return at(i);
        }
        
        /**
         * Перегруженный оператор [].
         *
         * @param i индекс в массиве
         * @throw возникает в случе если произошёл выход за границы массива
         * @return константную ссылку на i-й элемент массива
         */
        const T& operator[] (size_t i) const
        {
            return at(i);
        }
        
        /**
         * Метод, необходимый для выявления размера срезки.
         *
         * @return размер срезки
         */
        size_t size() const noexcept
        {
            return (_end - _begin);
        }
        
    protected:
        T* _begin;
        T* _end;
    };
}

