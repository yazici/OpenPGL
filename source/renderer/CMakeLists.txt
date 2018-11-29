
set(RENDERER_SOURCE
    renderer/Window.cpp
    renderer/Shader.cpp
    renderer/VertexBuffer.cpp
    renderer/VertexObject.cpp
    renderer/ElementBuffer.cpp
    renderer/AttributeInfo.cpp
    renderer/ShaderProgram.cpp
    renderer/TextureRender.cpp
    )

set(RENDERER_HEADER
    renderer/Window.h
    renderer/Shader.h
    renderer/Window.inl
    renderer/VertexBuffer.h
    renderer/VertexObject.h
    renderer/ElementBuffer.h
    renderer/AttributeInfo.h
    renderer/ShaderProgram.h
    renderer/TextureRender.h
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