#ifndef _RENDERER_SHADER_H
#define _RENDERER_SHADER_H

#include <GL/glew.h>

namespace pgl
{
    enum class ShaderType : GLenum
    {
        VERTEX   = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };

    class Shader
    {

    };
}

#endif //!_RENDERER_SHADER_H
