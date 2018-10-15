#ifndef _RENDERER_TEXTURE_H
#define _RENDERER_TEXTURE_H

#include <GL/glew.h>

#include <string>

using namespace std;

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
         * @param name имя текстуры
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        Texture(string name, uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data);
        
        /**
         * Конструктор.
         *
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        Texture(uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data);
        
        Texture(Texture&& texture);
        
        /**
         * Функция предназначенная для создания текструы.
         *
         * @param name имя текстуры
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        static Texture create(string name, uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data);
        
        /**
         * Функция предназначенная для создания текструы.
         *
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        static Texture create(uint32_t width, uint32_t height, PixelFormat format, const uint8_t* data);
        
        uint32_t width() const noexcept;
        uint32_t height() const noexcept;
        
        string_view name() const noexcept;
        void name(string_view name);
        
    protected:
        GLubyte* _data;
        GLuint _width;
        GLuint _height;
        string _name;
        PixelFormat _format;
    };
}

#endif // !_RENDERER_TEXTURE_H
