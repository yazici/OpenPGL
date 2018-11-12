
set(RENDERER_SOURCE
    renderer/IndexBuffer.cpp
    renderer/Shader.cpp
    renderer/ShaderProgram.cpp
    renderer/TextureRender.cpp
    renderer/VertexBuffer.cpp
    renderer/VertexObject.cpp
    renderer/Window.cpp
    )

set(RENDERER_HEADER
    renderer/IndexBuffer.h
    renderer/Shader.h
    renderer/ShaderProgram.h
    renderer/TextureRender.h
    renderer/VertexBuffer.h
    renderer/VertexObject.h
    renderer/Window.h
    renderer/Window.inl
    )

set(SHADERS
    ${CMAKE_SOURCE_DIR}/shaders/outputHeightMap.frag
    ${CMAKE_SOURCE_DIR}/shaders/outputHeightMap.vert
    ${CMAKE_SOURCE_DIR}/shaders/ADS.frag
    ${CMAKE_SOURCE_DIR}/shaders/halfWayADS.frag
    ${CMAKE_SOURCE_DIR}/shaders/ADS.vert
    ${CMAKE_SOURCE_DIR}/shaders/rednerTexture.frag
    ${CMAKE_SOURCE_DIR}/shaders/rednerTexture.vert
    )