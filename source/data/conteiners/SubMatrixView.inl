//
//  subMatrixView.inl
//  OpenPGL
//
//  Created by Асиф Мамедов on 29.10.2018.
//

#include <vector>

#include <stdexcept>

#include "data/conteiners/ArrayView.h"

using std::vector;
using std::runtime_error;
using std::invalid_argument;

namespace pgl
{
    template<class T>
    class SubMatrixView
    {
    public:
        
        /**
         * Конструктор.
         *
         * @param ptr указатель на начало срезки
         * @param w количество строк в срезке
         * @param р количество столбцов в срезке
         * @param sourseMatrixW количество строк у исходной матрицы
         * @param sourseMatrixH количество столбцов у исходной матрицы
         */
        SubMatrixView(T* ptr, size_t w, size_t h, size_t sourseMatrixW, size_t sourceMatrixH)
        {
            for (size_t i = 0, j = 0; i < w; i++, j += sourseMatrixW) {
                _view.push_back(ArrayView<T>(ptr + j, ptr + j + (h - 1)));
            }
        }
        
        /**
         * Метод позволяющий итерироваться по матрице.
         *
         * @param i индекс строки
         * @param j индекс столба
         * @throw в случае если срезка пустая или выхода за границы срезки
         * @return ссылку на значение по координатам (i, j)
         */
        T& at(size_t i, size_t j)
        {
            if (_view.empty()) {
                throw runtime_error("Matrix is ​​empty");
            }
            
            if (i >= _view.size() || j >= _view[0].size()) {
                throw invalid_argument("Crossing the matrix");
            }
            
            return _view[i][j];
        }
        
        /**
         * Метод позволяющий итерироваться по матрице.
         *
         * @param i индекс строки
         * @param j индекс столба
         * @throw в случае если срезка пустая или выхода за границы срезки
         * @return константная ссылку на значение по координатам (i, j)
         */
        const T& at(size_t i, size_t j) const
        {
            return at(i, j);
        }
        
        /**
         * Перегруженный оператор [] для итерирования по
         * матричной срезке.
         *
         * @param i индекс строки
         * @throw в случае если срезка пустая или выхода за гранцу строки
         * @return ссылка на i-ю срезку строки
         */
        ArrayView<T>& operator[](size_t i)
        {
            if (_view.empty()) {
                throw runtime_error("Matrix is ​​empty");
            }
            
            if (i > _view.size()) {
                throw invalid_argument("out of line");
            }
            
            return _view[i];
        }
        
        /**
         * Перегруженный оператор [] для итерирования по
         * матричной срезке.
         *
         * @param i индекс строки
         * @throw в случае если срезка пустая или выхода за гранцу строки
         * @return константная ссылка на i-ю срезку строки
         */
        const ArrayView<T>& operator[](size_t i) const
        {
            return operator[](i);
        }
        
    private:
        vector<ArrayView<T>> _view;
    };
}
