cmake_minimum_required(VERSION 3.10)

set(OPENPGL_VERSION 0.2)
project(OpenPGL VERSION ${OPENPGL_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Подключение библиотек
if(WIN32)
    set(WIN32_EXECUTABLE true)
    set(LIBRARY_OPENGL opengl32.lib)
    set(LIBRARY_SDL2_DIR ${CMAKE_SOURCE_DIR}/library/sdl2/lib)
    set(LIBRARY_GLEW_DIR ${CMAKE_SOURCE_DIR}/library/glew/lib)
    set(LIBRARY_GLEW ${LIBRARY_GLEW_DIR}/x86/glew32.lib)
    set(LIBRARY_SDL2 "${LIBRARY_SDL2_DIR}/x86/SDL2main.lib"
                     "${LIBRARY_SDL2_DIR}/x86/SDL2.lib")

    link_libraries(${LIBRARY_OPENGL})
    link_libraries(${LIBRARY_GLEW})
    link_libraries(${LIBRARY_SDL2})

    file(COPY ${LIBRARY_SDL2_DIR}/x86/sdl2.dll 
              ${LIBRARY_GLEW_DIR}/x86/glew32.dll
			  DESTINATION ${CMAKE_BINARY_DIR}/Debug/)
elseif(APPLE)
    find_library(LIBRARY_SDL2 SDL2)
    find_library(LIBRARY_GLEW GLEW)
    find_library(LIBRARY_OPENGL opengl)
endif()

# Указываем путь к заголовочным файлам.
set(HEADER_OPENPGL_DIR ${CMAKE_SOURCE_DIR}/source)
include_directories(${HEADER_OPENPGL_DIR})

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

# Поиск заголовочных файлов и файлов с исходным кодом.
file(GLOB SOURCE_RENDERER   RELATIVE ${CMAKE_BINARY_DIR} ./source/renderer/*.cpp)
file(GLOB HEADER_RENDERER   RELATIVE ${CMAKE_BINARY_DIR} ./source/renderer/*.h)
file(GLOB SOURCE_DATA       RELATIVE ${CMAKE_BINARY_DIR} ./source/data/*.cpp)
file(GLOB HEADER_DATA       RELATIVE ${CMAKE_BINARY_DIR} ./source/data/*.h)
file(GLOB SOURCE_ALGORITHM  RELATIVE ${CMAKE_BINARY_DIR} ./source/algorithm/*.cpp)
file(GLOB HEADER_ALGORITHM  RELATIVE ${CMAKE_BINARY_DIR} ./source/algorithm/*.h)
file(GLOB SOURCE_CONTEINERS RELATIVE ${CMAKE_BINARY_DIR} ./source/data/conteiners/*.inl)
file(GLOB HEADER_CONTEINERS RELATIVE ${CMAKE_BINARY_DIR} ./source/data/conteiners/*.h)
file(GLOB SOURCE_SYS		RELATIVE ${CMAKE_BINARY_DIR} ./source/sys/*.cpp)
file(GLOB HEADER_SYS		RELATIVE ${CMAKE_BINARY_DIR} ./source/sys/*.h)
file(GLOB SOURCE_MAIN       RELATIVE ${CMAKE_BINARY_DIR} ./source/Main.cpp)

# Группировка файлов по папкам.
source_group("renderer"   FILES ${SOURCE_RENDERER}   ${HEADER_RENDERER})
source_group("data"       FILES ${SOURCE_DATA}       ${HEADER_DATA})
source_group("algorithm"  FILES ${SOURCE_ALGORITHM}  ${HEADER_ALGORITHM})
source_group("conteiners" FILES ${SOURCE_CONTEINERS} ${HEADER_CONTEINERS})
source_group("sys"		  FILES ${SOURCE_SYS}		 ${HEADER_SYS})

# Копирование вспомогательных файлов (шейдеры и т.п.) в папки с проектом.
file(COPY ${CMAKE_SOURCE_DIR}/source/renderer/shaders
		  DESTINATION ${CMAKE_BINARY_DIR}/Debug/)

# Сборка решения.
add_executable(${PROJECT_NAME}
    # Файлы исходного кода
    ${SOURCE_MAIN}      
	${SOURCE_RENDERER}   
	${SOURCE_DATA}
    ${SOURCE_ALGORITHM} 
	${SOURCE_CONTEINERS} 
	${SOURCE_SYS}
    # Заголовочные файлы
    ${HEADER_RENDERER}   
	${HEADER_DATA}
	${HEADER_ALGORITHM}
	${HEADER_CONTEINERS}
	${HEADER_SYS})

if (WIN32)
	set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} ${LIBRARY_SDL2} ${LIBRARY_GLEW} ${LIBRARY_OPENGL})
endif()