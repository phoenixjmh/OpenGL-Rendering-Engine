#include "ShapeFactory.h"

#include <iostream>

std::vector<float> ShapeFactory::create_circle(float size) {
  const int num_segments = 30; // Number of segments in the circle
  std::vector<float> vertices;

  const double pi = 3.14159265358979323846;

  for (int i = 0; i < num_segments; ++i) {
    float theta = 2 * pi * float(i) / float(num_segments);
    float x = cos(theta) / 100; // X coordinate
    float y = sin(theta) / 100; // Y coordinate

    // Add the vertex (x, y, 0) to the vertices array
    vertices.push_back(x * size);
    vertices.push_back(y * size);
    vertices.push_back(0.0f); // Z coordinate (assuming 2D, so set to 0)
  }

  return vertices;
}

std::vector<unsigned int> ShapeFactory::index_circle(int num_segments) {
  std::vector<unsigned int> indices;

  for (int i = 0; i < num_segments - 1; ++i) {
    indices.push_back(0);     // Center point
    indices.push_back(i + 1); // Current point
    indices.push_back(i + 2); // Next point

    // Close the circle by connecting the last point to the first point
    if (i == num_segments - 2) {
      indices.push_back(0);                // Center point
      indices.push_back(num_segments - 1); // Last point
      indices.push_back(1);                // First point
    }
  }

  return indices;
}

std::vector<float> ShapeFactory::create_cube() {

  std::vector<float> vertices = {
      // Vertices for a cube
      // Position        // Normal
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // 0
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // 1
      0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // 2
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // 3
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 4
      0.5f,  -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 5
      0.5f,  0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, // 6
      -0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, 1.0f  // 7
  };
  // positions // normals // texture coords

  return vertices;
}
std::vector<Vertex> ShapeFactory::create_cube_no_index() {
  std::vector<Vertex> Vertices;

  std::vector<std::vector<float>> raw_vertices = {

      {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
      {0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f},
      {0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
      {0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
      {-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f},
      {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},

      {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
      {0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},
      {0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
      {0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
      {-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
      {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

      {-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
      {-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
      {-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
      {-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
      {-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
      {-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f},

      {0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
      {0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
      {0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
      {0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
      {0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
      {0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},

      {-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f},
      {0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f},
      {0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f},
      {0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f},
      {-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f},
      {-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f},

      {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
      {0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
      {0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
      {0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
      {-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
      {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f}};

  for (auto i = 0; i < raw_vertices.size(); i++) {
    glm::vec3 pos = {raw_vertices[i][0], raw_vertices[i][1],
                     raw_vertices[i][2]};
    glm::vec3 norm = {raw_vertices[i][3], raw_vertices[i][4],
                      raw_vertices[i][5]};
    glm::vec2 texCoord = {raw_vertices[i][6], raw_vertices[i][7]};

    Vertex vert(pos, norm, texCoord);
    Vertices.push_back(vert);
  }
  // positions // normals // texture coords

  return Vertices;
}

std::vector<unsigned> ShapeFactory::index_cube() {
  std::vector<unsigned int> indices = {
      0, 1, 2, 2, 3, 0, // Front face
      1, 5, 6, 6, 2, 1, // Right face
      5, 4, 7, 7, 6, 5, // Back face
      4, 0, 3, 3, 7, 4, // Left face
      3, 2, 6, 6, 7, 3, // Top face
      4, 5, 1, 1, 0, 4  // Bottom face
  };
  return indices;
}
std::vector<float> ShapeFactory::create_plane() {
  std::vector<float> vertices = {
      -0.5, 0.0, 0.5,  0, 1, 0, 0.5,  0.0, 0.5,  0, 1, 0,
      0.5,  0.0, -0.5, 0, 1, 0, -0.5, 0.0, 0.5,  0, 1, 0,
      0.5,  0.0, -0.5, 0, 1, 0, -0.5, 0.0, -0.5, 0, 1, 0,
  };
  std::cout << "HMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n";
  return vertices;
}
