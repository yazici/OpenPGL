set(OPENPGL_VERSION 0.2)

include(algorithm/CMakeLists.txt)
include(data/CMakeLists.txt)
include(renderer/CMakeLists.txt)
include(sys/CMakeLists.txt)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(OPENPGL_SOURCE
    Main.cpp
    ${ALGORITHM_SOURCE}
    ${DATA_SOURCE}
    ${RENDERER_SOURCE}
    ${SYS_SOURCE}
    )

set(OPENPGL_HEADER 
    ${ALGORITHM_HEADER}
    ${DATA_HEADER}
    ${RENDERER_HEADER}
    ${SYS_HEADER}
    )

# Группировка файлов по папкам.
source_group("renderer"   FILES ${RENDERER_SOURCE}   ${RENDERER_HEADER})
source_group("data"       FILES ${DATA_SOURCE}       ${DATA_HEADER})
source_group("algorithm"  FILES ${ALGORITHM_SOURCE}  ${ALGORITHM_HEADER})
source_group("sys"		  FILES ${SYS_SOURCE}		 ${SYS_HEADER})

add_executable(OpenPGL ${OPENPGL_SOURCE} ${OPENPGL_HEADER})

if (WIN32)
    set_target_properties(OpenPGL 
        PROPERTIES
        WIN32_EXECUTABLE ON
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Debug
        )
endif()

target_link_libraries(OpenPGL ${LIBRARY_SDL2} ${LIBRARY_GLEW} ${LIBRARY_OPENGL})
set_target_properties(OpenPGL
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    VERSION "${OPENPGL_VERSION}"
)
