cmake_minimum_required(VERSION 3.10)

set(OPENPGL_VERSION 0.1)
project(OpenPGL VERSION ${OPENPGL_VERSION} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Подключение библиотек
set(LIBRARY_SDL2_DIR ${CMAKE_SOURCE_DIR}/library/sdl2/lib)
set(LIBRARY_GLEW_DIR ${CMAKE_SOURCE_DIR}/library/glew/lib)
if(WIN32)
    set(WIN32_EXECUTABLE true)
    link_libraries(opengl32.lib)
    link_libraries(${LIBRARY_GLEW_DIR}/x86/glew32.lib)
    link_libraries(${LIBRARY_SDL2_DIR}/x86/SDL2main.lib 
                   ${LIBRARY_SDL2_DIR}/x86/SDL2.lib)
elseif(APPLE)
    message("MacOS is not supported.")
endif()

# Указываем путь к заголовочным файлам.
set(HEADER_GLEW_DIR    ${CMAKE_SOURCE_DIR}/library/glew/include)
set(HEADER_SDL2_DIR    ${CMAKE_SOURCE_DIR}/library/sdl2/include)
set(HEADER_GLM_DIR     ${CMAKE_SOURCE_DIR}/library/glm/include)
set(HEADER_OPENPGL_DIR ${CMAKE_SOURCE_DIR}/source)
include_directories(${HEADER_OPENPGL_DIR} 
                    ${HEADER_GLEW_DIR}
                    ${HEADER_SDL2_DIR}
                    ${HEADER_GLM_DIR})

# Поиск заголовочных файлов и файлов с исходным кодом.
file(GLOB SOURCE_RENDERER  RELATIVE ${CMAKE_CURRENT_BINARY_DIR} ./source/renderer/*.cpp)
file(GLOB HEADER_RENDERER  RELATIVE ${CMAKE_CURRENT_BINARY_DIR} ./source/renderer/*.h)
file(GLOB SOURCE_DATA      RELATIVE ${CMAKE_CURRENT_BINARY_DIR} ./source/data/*.cpp)
file(GLOB HEADER_DATA      RELATIVE ${CMAKE_CURRENT_BINARY_DIR} ./source/data/*.h)
file(GLOB SOURCE_ALGORITHM RELATIVE ${CMAKE_CURRENT_BINARY_DIR} ./source/algorithm/*.cpp)
file(GLOB HEADER_ALGORITHM RELATIVE ${CMAKE_CURRENT_BINARY_DIR} ./source/algorithm/*.h)
file(GLOB SOURCE_MAIN      RELATIVE ${CMAKE_CURRENT_BINARY_DIR} ./source/Main.cpp)

# Группировка файлов по папкам.
source_group("renderer"  FILES ${SOURCE_RENDERER}  ${HEADER_RENDERER})
source_group("data"      FILES ${SOURCE_DATA}      ${HEADER_DATA})
source_group("algorithm" FILES ${SOURCE_ALGORITHM} ${HEADER_ALGORITHM})

# Сборка решения.
add_executable(${PROJECT_NAME}
    # Файлы исходного кода
    ${SOURCE_MAIN}      ${SOURCE_RENDERER} ${SOURCE_DATA}
    ${SOURCE_ALGORITHM} 
    # Заголовочные файлы
    ${HEADER_RENDERER}  ${HEADER_DATA}     ${HEADER_ALGORITHM})
