#ifndef _RENDERER_VAO_H
#define _RENDERER_VAO_H

#include <stdint.h>
#include <vector>

#include "IndexBuffer.h"

namespace pgl
{
    using std::vector;

    class Mesh;
    class VertexBuffer;

    class VertexObject
    {
    public:

        /**
        * Создает OpenGL объект, который описывает данные вершин и используется для рендера этих 
        * данных.
        * 
        * @param mesh загружаемый для рендера меш.
        */
        VertexObject(const Mesh &mesh);

        /**
        * Освобождает выделенные ресурсы в том числе и загруженные при помощи функций OpenGL 
        * данные вершин.
        */
        ~VertexObject();

        /**
        * Отображает примитивы из связанных буферов (VBO). Отображение будет проводиться, если 
        * VAO находится в активном состоянии (т.е. IsEnable() возвращает true).
        */
        void Draw() const;
        //void Draw(const Shader &shader);

        /**
        * Активирует текущий VAO.
        */
        void Enable() const;

        /**
        * Отключает текущий VAO.
        */
        void Disable() const;

        /** 
        * Проверяет активирован ли VAO.
        * 
        * @return true, если VAO активирован, false в противном случае.
        */
        bool IsEnable() const;

    private:
        vector<VertexBuffer> _vbos;
        IndexBuffer _indices;
        uint32_t _vao;
        bool _enable;
    };
}

#endif // !_RENDERER_VAO_H
