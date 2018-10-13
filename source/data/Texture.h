#ifndef _RENDERER_TEXTURE_H
#define _RENDERER_TEXTURE_H

#include <GL/glew.h>

namespace pgl
{
    /**
    * Структура предназначена для использования, в случае если
    * пользователю при создании текстуры нужно указать настройки
    * для её создания.
    *
    * @property minFilter используется для определения того каким
    *   способом накладывать текстуру на поверхность которая больше
    *   самой текстуры. Для определения того какой цвет выдать пикселю
    *   необходимо указать какой алгоритм использовать (к примеру GL_NEAREST)
    * @property magFilter используется для определения того каким
    *   способом накладывать текстуру на поверхность меньшую или равную
    *   самой текстуре. Для определения того какой цвет выдать пикселю
    *   необходимо указать какой алгоритм использовать (к примеру GL_NEAREST)
    * @property wrapS необходим для определения того каким образом нужно
    *   отрисовывать текстуру по оси s в случе если текстурные координаты выйдут
    *   за пределы 0 или 1 (к примеру GL_REPEAT)
    * @property wrapT необходим для поределения того каким образом нужно
    *   отрисовывать текстуру по оси t в случе если текстурные координаты выйдут
    *   за пределы 0 или 1 (к примеру GL_REPEAT)
    */
    struct TextureParameter
    {
        GLenum minFilter;
        GLenum magFilter;
        GLenum wrapS;
        GLenum wrapT;

        TextureParameter(GLenum MinFilter = GL_LINEAR, GLenum MagFilter = GL_LINEAR, GLenum WrapS = GL_REPEAT, GLenum WrapT = GL_REPEAT);
    };

    /**
    * Объединеие определяющее тип текстуры.
    */
    enum class PixelFormat : GLenum
    {
        RGB = GL_RGB8,
        RGBA = GL_RGBA8,
        BLACK_WHITE = GL_R8
    };

    class Texture
    {
    public:
        /**
        * Конструктор по умолчанию.
        */
        Texture();

        /**
        * Конструктор.
        *
        * @param width ширина текстуры
        * @param height высота текстуры
        * @param storFrom тип текстуры которая хранится в массиве data
        * @param dataForm тип текструры которуя хочет создать пользователь
        * @param texParam параметры настройки необходимые для создания текструы
        * @param data массив в котором находится текстура
        */
        Texture(GLuint width, GLuint height, PixelFormat storFrom, PixelFormat dataForm, TextureParameter texParam, GLenum dataType,const void* data);
        //Texture(const Texture&) = delete;
        Texture(Texture&& texture);

        /**
        * Статическая функция необходимая для создания текструы.
        *
        * @param width ширина текстуры
        * @param height высота текстуры
        * @param storFrom тип текстуры которая хранится в массиве data
        * @param dataForm тип текструры которуя хочет создать пользователь
        * @param texParam параметры настройки необходимые для создания текструы
        * @param data массив в котором находится текстура
        */
        static Texture create (GLuint width, GLuint height, PixelFormat storFrom, PixelFormat dataForm, TextureParameter texParam, GLenum dataType, const void* data);

        /**
        * Метод который делает текстуру активной и задаёт ей текструный слот.
        * По умолчанию слот 0-ой.
        */
        void bind(GLint slot = 0) const noexcept;

        /**
        * Метод который делает текстуру не активной.
        */
        void unbind() const noexcept;

        GLuint width() const noexcept;
        GLuint height() const noexcept;

    protected:
        void* _data;
        GLuint _width;
        GLuint _height;
        PixelFormat _srotageFormat;
        PixelFormat _dataFormat;
        GLuint _handle;
    };
}

#endif // !_RENDERER_TEXTURE_H
