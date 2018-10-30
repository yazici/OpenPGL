#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "data/Mesh.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"

using namespace std;
using namespace pgl;
GLuint vertHandle, fragHandle, progHandle;
VertexBuffer *position;
VertexBuffer *normal;
IndexBuffer *ebo;

auto createVao()
{
    tuple<GLuint, GLuint, GLuint, GLuint> data;
    GLuint& posHandle = get<0>(data);
    GLuint& colorHandle = get<1>(data);
    GLuint& normalizeHandle = get<2>(data);
    GLuint& vaoHandle = get<3>(data);
    
    glGenBuffers(1, &posHandle);
    glGenBuffers(1, &colorHandle);
    glGenBuffers(1, &normalizeHandle);
    
    if (!colorHandle || !posHandle) {
        throw runtime_error("Error create vbo");
    }
    
    Mesh m = Mesh::CreatePlane(5, 6.0f);
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    position = VertexBuffer::create(sizeof(vec3), m.vertices().size(), m.vertices().data());
//    position = VertexBuffer::create(sizeof(vec3), sizeof(posData)/sizeof(float), posData);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    normal = VertexBuffer::create(sizeof(vec3), m.normals().size(), m.normals().data());
//    normal = VertexBuffer::create(sizeof(vec3), sizeof(normalizeData)/sizeof(float), normalizeData);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    ebo = IndexBuffer::create(m.triangles().size(), m.triangles().data());
//    ebo = IndexBuffer::create(3, index);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    return data;
}

void scene(SDL_Window* window)
{
    using glm::mat4;
    using glm::mat3;
    using glm::vec3;
    using glm::vec4;
    
    glUseProgram(progHandle);
    auto data = createVao();
    
    glBindVertexArray(get<3>(data));
    
    assert(!glGetError());
    
    SDL_Event event;
    bool stay = true;
    
    mat4 matrixViewModel(1.0f);
    matrixViewModel = glm::translate(matrixViewModel, vec3(0.0, -2.0, -8.0));
//   matrixViewModel = glm::rotate(matrixViewModel, 90.0f, vec3(1.0f, 0.0f, 0.0f));
    mat3 normalizeMatrx(glm::transpose(matrixViewModel));
    mat4 perspectiveProj(glm::perspective( 45.0f, 800.0f/600.0f, 0.1f, 200.0f));
    
    vec4 lightPosition  (0.0f, 5.0f, -8.0f , 1.0f);
    vec3 ld (0.78f, 0.334f, 0.4345f);
    vec3 kd (1.0f, 1.0f, 1.0f);
    
    assert(!glGetError());
    GLint matrixViewModelLocal = glGetUniformLocation(progHandle, "ModelViewMatrix");
    assert(!glGetError());
    
    GLint normalizeMatrxLocal = glGetUniformLocation(progHandle, "NormalMatrix");
    assert(!glGetError());
    
    GLint perspectiveProjLocal = glGetUniformLocation(progHandle, "ProjectionMatrix");
    assert(!glGetError());
    
    GLint lightPositionLocal = glGetUniformLocation(progHandle, "LightPosition");
    assert(!glGetError());
    
    GLint ldLocal = glGetUniformLocation(progHandle, "Ld");
    assert(!glGetError());
    
    GLint kdLocal = glGetUniformLocation(progHandle, "Kd");
    assert(!glGetError());
    
    
    glUniformMatrix4fv(matrixViewModelLocal, 1, GL_FALSE, &matrixViewModel[0][0]);
    glUniformMatrix3fv(normalizeMatrxLocal, 1, GL_FALSE, &normalizeMatrx[0][0]);
    glUniformMatrix4fv(perspectiveProjLocal, 1, GL_FALSE, &perspectiveProj[0][0]);
    
    glUniform4fv(lightPositionLocal, 1, &lightPosition[0]);
    glUniform3fv(ldLocal, 1, &ld[0]);
    glUniform3fv(kdLocal, 1, &kd[0]);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    while(stay) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                stay = false;
            }
        }
        
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, ebo->size(), GL_UNSIGNED_INT, nullptr);
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        SDL_GL_SwapWindow(window);
        
    }
}

void createShaderProgram()
{
    progHandle = glCreateProgram();
    
    if (!progHandle) {
        throw runtime_error("Error create program");
    }
    
    glAttachShader(progHandle, vertHandle);
    glAttachShader(progHandle, fragHandle);
    
    glLinkProgram(progHandle);
    
    GLint res;
    glGetProgramiv(progHandle, GL_LINK_STATUS, &res);
    
    if (!res) {
        throw runtime_error("Error link program");
    }
}

inline void checkCompile(GLuint desc)
{
    GLint res;
    glGetShaderiv(desc, GL_COMPILE_STATUS, &res);
    
    if (!res) {
        throw runtime_error("Error compile shader");
    }
}

string readFile (const string& fileName)
{
    ifstream f (fileName);
    
    if (!f) {
        throw invalid_argument("Error open file");
    }
    
    f.seekg (0, std::ios::end);
    size_t size = f.tellg();
    std::string s (size, ' ');
    f.seekg (0);
    f.read (&s[0], size);
    return s;
}

void compileShaders()
{
    vertHandle = glCreateShader(GL_VERTEX_SHADER);
    fragHandle = glCreateShader(GL_FRAGMENT_SHADER);
    
    if (!vertHandle || !fragHandle) {
        throw runtime_error("Error create shader");
    }
    
    string vertStringCode(readFile("/Users/asifmamedov/Desktop/ambient/ambient/basic.vert"));
    string fragStringCode(readFile("/Users/asifmamedov/Desktop/ambient/ambient/basic.frag"));
    
    const char* vertCode = vertStringCode.c_str();
    const char* fragCode = fragStringCode.c_str();
    
    glShaderSource(vertHandle, 1, &vertCode, nullptr);
    glShaderSource(fragHandle, 1, &fragCode, nullptr);
    
    glCompileShader(vertHandle);
    glCompileShader(fragHandle);
    
    checkCompile(vertHandle);
    checkCompile(fragHandle);
}

inline void setOpenGLAttributes() noexcept
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

inline void error()
{
    string msg(SDL_GetError());
    SDL_ClearError();
    throw runtime_error(msg);
}

inline SDL_Window* createWindow(string_view windowName)
{
    SDL_Window* window = SDL_CreateWindow(windowName.cbegin(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    
    if (!window) {
        error();
    }
    
    return window;
}

inline void desroyWindowAndContext(SDL_Window* window, SDL_GLContext context)
{
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
}

inline void init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        error();
    }
}

inline void quit() noexcept
{
    SDL_Quit();
}


int main()
{
    try {
        init();
        SDL_Window* window = createWindow("PGL");
        setOpenGLAttributes();
        SDL_GLContext context = SDL_GL_CreateContext(window);
        glewExperimental = GL_TRUE;
        glewInit();
        compileShaders();
        createShaderProgram();
        scene(window);
        quit();
    } catch(const runtime_error& err) {
        cerr << err.what() << endl;
    }
    
    return 0;
}
