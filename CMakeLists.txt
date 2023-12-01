cmake_minimum_required(VERSION 3.4...3.20)
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
  src/
  PUBLIC
  src/vendor/
  PUBLIC glad
  )
# find_package(glfw REQUIRED)
target_link_directories(${PROJECT_NAME}
  PUBLIC external/glfw/include
  PUBLIC external/glm
  PUBLIC src/
  PUBLIC src/vendor/
  PUBLIC glad
  )
target_link_libraries(${PROJECT_NAME} glfw )
file(GLOB_RECURSE GLSL_SOURCE_FILES
  "${PROJECT_SOURCE_DIR}/shaders/*.frag"
  "${PROJECT_SOURCE_DIR}/shaders/*.vert"
  ) 
add_custom_target(
  shaders
  )
