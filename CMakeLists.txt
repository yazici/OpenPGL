cmake_minimum_required(VERSION 3.10)

project(OpenPGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Поиск библиотек
if(WIN32)
    set(LIBRARY_SDL2_DIR ${CMAKE_SOURCE_DIR}/library/sdl2/lib)
    set(LIBRARY_GLEW_DIR ${CMAKE_SOURCE_DIR}/library/glew/lib)

    set(LIBRARY_OPENGL opengl32.lib)
    set(LIBRARY_GLEW ${LIBRARY_GLEW_DIR}/x86/glew32.lib)
    set(LIBRARY_SDL2 "${LIBRARY_SDL2_DIR}/x86/SDL2main.lib"
                     "${LIBRARY_SDL2_DIR}/x86/SDL2.lib")

    file(COPY ${LIBRARY_SDL2_DIR}/x86/sdl2.dll 
              ${LIBRARY_GLEW_DIR}/x86/glew32.dll
			  DESTINATION ${CMAKE_BINARY_DIR}/Debug/)
elseif(APPLE)
    find_library(LIBRARY_SDL2 SDL2)
    find_library(LIBRARY_GLEW GLEW)
    find_library(LIBRARY_OPENGL opengl)
endif()

# Указываем путь к заголовочным файлам.
include_directories(source)

if(WIN32)
    set(HEADER_GLEW_DIR ${CMAKE_SOURCE_DIR}/library/glew/include)
    set(HEADER_SDL2_DIR ${CMAKE_SOURCE_DIR}/library/sdl2/include)
    set(HEADER_GLM_DIR  ${CMAKE_SOURCE_DIR}/library/glm/include)
    include_directories(${HEADER_GLEW_DIR}
                        ${HEADER_SDL2_DIR}
                        ${HEADER_GLM_DIR})
elseif(APPLE)
    include_directories("/usr/local/include")
endif()

# Копирование вспомогательных файлов (шейдеры и т.п.) в папки с проектом.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/source/renderer/shaders
		  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/)

add_subdirectory(source)
