cmake_minimum_required(VERSION 3.4...3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(StagR)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(ASSIMP_BUILD_OBJ_IMPORTER ON)
add_subdirectory(external/glfw)
add_subdirectory(external/assimp)

set(SOURCES 
  ${PROJECT_SOURCE_DIR}/src/Editor.cpp
  ${PROJECT_SOURCE_DIR}/src/IndexBuffer.cpp
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/Model.cpp
  ${PROJECT_SOURCE_DIR}/src/Physics.cpp
  ${PROJECT_SOURCE_DIR}/src/PhysicsObject.cpp
  ${PROJECT_SOURCE_DIR}/src/Renderer.cpp
  ${PROJECT_SOURCE_DIR}/src/Shader.cpp
  ${PROJECT_SOURCE_DIR}/src/ShapeFactory.cpp
  ${PROJECT_SOURCE_DIR}/src/VertexArray.cpp
  ${PROJECT_SOURCE_DIR}/src/VertexBuffer.cpp
  ${PROJECT_SOURCE_DIR}/src/Mesh.cpp
  ${PROJECT_SOURCE_DIR}/src/Logger.cpp
  ${PROJECT_SOURCE_DIR}/src/Application.cpp
  ${PROJECT_SOURCE_DIR}/src/ResourceManager.cpp



  )


set(HEADERS 
  ${PROJECT_SOURCE_DIR}/src/Editor.h
  ${PROJECT_SOURCE_DIR}/src/IndexBuffer.h
  ${PROJECT_SOURCE_DIR}/src/Model.h
  ${PROJECT_SOURCE_DIR}/src/Physics.h
  ${PROJECT_SOURCE_DIR}/src/PhysicsObject.h
  ${PROJECT_SOURCE_DIR}/src/Renderer.h
  ${PROJECT_SOURCE_DIR}/src/Shader.h
  ${PROJECT_SOURCE_DIR}/src/ShapeFactory.h
  ${PROJECT_SOURCE_DIR}/src/VertexArray.h
  ${PROJECT_SOURCE_DIR}/src/VertexBuffer.h
  ${PROJECT_SOURCE_DIR}/src/Mesh.h
  ${PROJECT_SOURCE_DIR}/src/Logger.h
  ${PROJECT_SOURCE_DIR}/src/Application.h
  ${PROJECT_SOURCE_DIR}/src/ResourceManager.h


  )
# file( GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# file( GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.h)
file( GLOB_RECURSE SHADERS ${PROJECT_SOURCE_DIR}/shaders/*.vert ${PROJECT_SOURCE_DIR}/shaders/*.frag)
file(GLOB_RECURSE VENDOR
  ${PROJECT_SOURCE_DIR}/src/vendor/*.c 
  ${PROJECT_SOURCE_DIR}/src/vendor/*.cpp
)

source_group("Vendor" FILES ${VENDOR})
source_group("Sources" FILES ${SOURCES})
source_group("Headers" FILES ${HEADERS})
source_group("Shaders" FILES ${SHADERS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${SHADERS} ${VENDOR})
target_include_directories(${PROJECT_NAME}
  PUBLIC
  external/glfw/include
  PUBLIC
  external/assimp/include
  PUBLIC
  external/glm
  PUBLIC
  external/
  PUBLIC
  src/
  PUBLIC
  src/vendor/
  #PUBLIC /shaders
  )
target_link_directories(${PROJECT_NAME}
  PUBLIC external/glfw/include
  PUBLIC external/glm
  PUBLIC external/assimp/include
  PUBLIC src/
  PUBLIC src/vendor/
  PUBLIC external/
 # PUBLIC /shaders
  )
target_link_libraries(${PROJECT_NAME} glfw assimp )

