#ifndef _TEXTURE_H
#define _TEXTURE_H

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
    
    class TextureRender;
    
    class Texture
    {
        friend class TextureRender;
        
    public:
        
        /**
         * Объединение определяющее формат данных пикселя.
         */
        enum PixelFormat : GLenum
        {
            RGB = GL_RGB,
            RGBA = GL_RGBA,
            BLACK_WHITE = GL_RED,
            BGR = GL_BGR,
            BGRA = GL_BGRA
        };
        
        /**
         * Объединение определяющее тип данных в массиве.
         */
        enum DataType : GLenum
        {
            UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
            UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
            UNSIGNED_INT = GL_UNSIGNED_INT,
            BYTE = GL_BYTE,
            SHORT = GL_SHORT,
            INT = GL_INT,
            FLOAT = GL_FLOAT
        };
        
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
        Texture(const string_view& name, uint32_t width, uint32_t height, PixelFormat format, TextureParameter parametr, DataType dataType, const uint8_t* data);
        
        /**
         * Конструктор.
         *
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        Texture(uint32_t width, uint32_t height, PixelFormat format, TextureParameter parametr, DataType dataType, const uint8_t* data);
        
        Texture(Texture&& texture);
        
        Texture(const Texture&);
        
        ~Texture();
        
        /**
         * Функция предназначенная для создания текструы.
         *
         * @param name имя текстуры
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        static Texture create(const string_view& name, uint32_t width, uint32_t height, PixelFormat format, TextureParameter parametr, DataType dataType, const uint8_t* data);
        
        /**
         * Функция предназначенная для создания текструы.
         *
         * @param width ширина текстуры
         * @param height высота текстуры
         * @param format формат в котором представляется пиксель в массиве
         * @param data указатель на массив данных
         */
        static Texture create(uint32_t width, uint32_t height, PixelFormat format, TextureParameter parametr, DataType dataType, const uint8_t* data);
        
        uint32_t width() const noexcept;
        uint32_t height() const noexcept;
        
        string_view name() const noexcept;
        void name(string_view name);
        
    protected:
        GLubyte* _data;
        GLenum _dataType;
        GLuint _width;
        GLuint _height;
        string _name;
        PixelFormat _format;
        TextureParameter _parametr;
    };
}

#endif // !_RENDERER_TEXTURE_H
