cmake_minimum_required(VERSION 3.4...3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(Phoesics)

add_subdirectory(external/glfw)
file( GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES}  ${PROJECT_SOURCE_DIR}/src/vendor/glad.c )
target_include_directories(${PROJECT_NAME}
  PUBLIC
  external/glfw/include
  PUBLIC
  external/glm
  PUBLIC
  external/
  PUBLIC
  src/
  PUBLIC
  src/vendor/
  PUBLIC /shaders
  )
target_link_directories(${PROJECT_NAME}
  PUBLIC external/glfw/include
  PUBLIC external/glm
  PUBLIC src/
  PUBLIC src/vendor/
  PUBLIC external/
  PUBLIC /shaders
  )
target_link_libraries(${PROJECT_NAME} glfw )

